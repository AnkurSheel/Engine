#include "stdafx.h"
#include "XMLNode.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "Physics.h"
#include "RigidBody.h"
#include "CollisionInfo.h"
#include "Optional.h"
#include "Quadtree.h"

using namespace Physics;
using namespace Base;
using namespace Utilities;
using namespace std;

cPhysics * cPhysics::s_pPhysics = NULL;

// *****************************************************************************
cPhysics::cPhysics()
	: m_Gravity(0.0f)
	, m_TimeStep(1.0f/60.0f)
	, m_Accumalator(0.0f)
	, m_pQuadTree(NULL)
	, m_UseQuadTree(true)
{
}

// *****************************************************************************
cPhysics::~cPhysics()
{
	SafeDelete(&m_pQuadTree);
}

// *****************************************************************************
void cPhysics::VInitialize(const cString & FileName)
{
	IResource * pResource = IResource::CreateResource(cGameDirectories::GetDesignDirectory() + FileName + ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	shared_ptr<IXMLNode> pRoot;
	SafeDelete(&pResource);
	if(pXMLFile != NULL)
	{
		pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}

	if (pRoot == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not find " + FileName + ".xml");
		return;
	}

	m_Gravity = pRoot->VGetChildValueAsFloat("Gravity", 0.0f);

	float frequency = pRoot->VGetChildValueAsFloat("TimeStepFrequency", 60.0f);
	m_TimeStep = 1.0f /(frequency);

	LoadMaterialData(pRoot->VGetChild("PhysicsMaterials"));
	CreateQuadTree(pRoot->VGetChild("QuadTree"));
	
	m_Accumalator = 0.0f;
}

// *****************************************************************************
void cPhysics::VUpdate(const float DeltaTime)
{
	int numSimulationSubSteps = 0;

	// fixed timestep
	m_Accumalator += DeltaTime;

	Clamp<float>(m_Accumalator, 0.0f, 0.3f);
	while(m_Accumalator >= m_TimeStep)
	{
		InternalStep();
		m_Accumalator -= m_TimeStep;
	}

	float alpha = m_Accumalator / m_TimeStep;
	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		if(pRigidBody->Sync(alpha))
		{
			m_pQuadTree->OnBodyMoved(pRigidBody);
		}
	}
}

// *****************************************************************************
IRigidBody * const cPhysics::VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef)
{
	IRigidBody * pBody = IRigidBody::Create(pDef, ID);
	cRigidBody * const pRigidBody = dynamic_cast<cRigidBody * const>(pBody);
	m_RigidBodyMap.insert(std::make_pair(ID, pRigidBody));
	return pBody;
}

// *****************************************************************************
void cPhysics::VRemoveRigidBody(const int ID)
{
	cRigidBody * pRigidBody = FindRigidBody(ID);
	if (pRigidBody != NULL)
	{
		m_RigidBodyMap.erase(ID);
		m_pQuadTree->Remove(pRigidBody);
		SafeDelete(&pRigidBody);
	}
}

// *****************************************************************************
void cPhysics::VOnRigidBodyAdded(const int ID)
{
	cRigidBody * pRigidBody = FindRigidBody(ID);
	if (pRigidBody != NULL)
	{
		m_pQuadTree->Insert(pRigidBody);
		//m_pQuadTree->Print();
	}
}

// *****************************************************************************
cRigidBody* cPhysics::FindRigidBody(const int ID) const
{
	RigidBodyMap::const_iterator Iter = m_RigidBodyMap.find(ID);
	if(Iter != m_RigidBodyMap.end())
	{
		return Iter->second;
	}

	return NULL;
}

// *****************************************************************************
void cPhysics::InternalStep()
{
	m_CollisionPairs.clear();
	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->IntegrateForces(m_TimeStep);
	}

	vector<cCollisionInfo> collisions;

	for(auto IterA = m_RigidBodyMap.begin(); IterA != m_RigidBodyMap.end(); IterA++)
	{
		cRigidBody * pRigidBodyA = dynamic_cast<cRigidBody*>(IterA->second);
		if(pRigidBodyA->GetInitialized() && pRigidBodyA->GetKinematic() )
		{
			if(m_UseQuadTree)
			{
				m_pQuadTree->CreateCollisionPairs(pRigidBodyA, collisions);
			}
			else
			{
				for(auto IterB = m_RigidBodyMap.begin(); IterB != m_RigidBodyMap.end(); IterB++)
				{
					cRigidBody * pRigidBodyB = dynamic_cast<cRigidBody*>(IterB->second);
					if(pRigidBodyB->GetInitialized())
					{
						cCollisionInfo c(pRigidBodyA, pRigidBodyB);
						c.Solve();
						if(c.GetCollided())
						{
							collisions.emplace_back(c);
						}
					}
				}
			}
		}
	}

	for(auto Iter = collisions.begin(); Iter != collisions.end(); Iter++)
	{
		cCollisionInfo c = *Iter;
		c.ApplyImpulse();
	}

	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->IntegrateVelocity(m_TimeStep);
	}

	for(auto Iter = collisions.begin(); Iter != collisions.end(); Iter++)
	{
		cCollisionInfo c = *Iter;
		c.ApplyPositionCorrection();

		int ID1 = c.GetBodyA()->VGetID();
		int ID2 = c.GetBodyB()->VGetID();
		CollisionPair thisPair;
		if(ID1 < ID2)
		{
			thisPair = std::make_pair(ID1, ID2);
		}
		else
		{
			thisPair = std::make_pair(ID2, ID1);
		}
		m_CollisionPairs.insert(thisPair);
	}
}

// ****************************************************************************
void cPhysics::LoadMaterialData(shared_ptr<IXMLNode> pParentNode)
{
	if(pParentNode == NULL)
	{
		return;
	}

	IXMLNode::XMLNodeList List;
	pParentNode->VGetChildren(List);
	for (auto Iter = List.begin(); Iter != List.end(); Iter++)
	{
		IXMLNode * pNode = (*Iter).get();
		stMaterialData data;
        data.restitution = pNode->VGetNodeAttributeAsFloat("restitution", 1.0f);
        data.friction = pNode->VGetNodeAttributeAsFloat("friction", 0.0f);

		m_MaterialMap[cHashedString::CalculateHash(pNode->VGetName().GetInLowerCase())] = data;
	}
}

// ****************************************************************************
void cPhysics::CreateQuadTree(shared_ptr<Utilities::IXMLNode> pParentNode)
{
	if(pParentNode == NULL)
	{
		return;
	}

	shared_ptr<Physics::stQuadTreeDef> pDef = shared_ptr<Physics::stQuadTreeDef>(DEBUG_NEW stQuadTreeDef());
	m_UseQuadTree = pParentNode->VGetChildValueAsBool("UseQuadTree", true);
	pDef->m_LooseningFactor = pParentNode->VGetChildValueAsFloat("LooseningFactor", 0.0f);
	pDef->m_MaxDepth = pParentNode->VGetChildValueAsInt("MaxDepth", 6);
	pDef->m_MaxObjects = pParentNode->VGetChildValueAsInt("MaxObjects", 8);
	pDef->m_MaxBounds = cVector3(1280, 768, 0);
	m_pQuadTree = DEBUG_NEW cQuadTree();
	m_pQuadTree->Initialize(pDef);
}

// ****************************************************************************
stMaterialData cPhysics::LookUpMaterialData(const cString & materialName)
{
	if(s_pPhysics == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Physics has not been initialized");
		return stMaterialData();
	}

	auto materialIt = s_pPhysics->m_MaterialMap.find(cHashedString::CalculateHash(materialName));
    if (materialIt != s_pPhysics->m_MaterialMap.end())
        return materialIt->second;
    else
        return stMaterialData();
}

// ****************************************************************************
float cPhysics::GetGravity()
{
	if(s_pPhysics != NULL)
	{
		return s_pPhysics->m_Gravity;
	}
	return 0.0f;
}

// ****************************************************************************
IPhysics * IPhysics::GetInstance()
{
	if(cPhysics::s_pPhysics == NULL)
		cPhysics::s_pPhysics = DEBUG_NEW cPhysics();
	return cPhysics::s_pPhysics;
}

// ****************************************************************************
void IPhysics::Destroy()
{
	SafeDelete(&cPhysics::s_pPhysics);
}
