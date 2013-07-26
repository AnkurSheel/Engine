#include "stdafx.h"
#include "Physics.h"
#include "RigidBody.h"
#include "CollisionInfo.h"

using namespace Physics;
using namespace Base;

IPhysics * cPhysics::s_pPhysics = NULL;

// *****************************************************************************
cPhysics::cPhysics()
	: m_Gravity(0.0f)
{
}

// *****************************************************************************
cPhysics::~cPhysics()
{
}

// *****************************************************************************
void cPhysics::VInitialize(const stPhysicsDef & def)
{
	m_Gravity = def.m_Gravity;
}

// *****************************************************************************
void cPhysics::VUpdate(const float DeltaTime)
{
	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->Update(DeltaTime);
	}
	for(auto IterA = m_RigidBodyMap.begin(); IterA != m_RigidBodyMap.end(); IterA++)
	{
		cRigidBody * pRigidBodyA = dynamic_cast<cRigidBody*>(IterA->second);
		if(pRigidBodyA->GetInitialized())
		{
			auto IterB = IterA;
			IterB++;
			for(; IterB != m_RigidBodyMap.end(); IterB++)
			{
				cRigidBody * pRigidBodyB = dynamic_cast<cRigidBody*>(IterB->second);
				if(pRigidBodyB->GetInitialized())
				{
					cCollisionInfo c(pRigidBodyA, pRigidBodyB);
					c.Solve();
					if(c.m_Collided)
					{
						pRigidBodyB->VSetPosition(pRigidBodyB->VGetPosition() - c.m_Distance);
					}
				}
			}
		}
	}
}

// *****************************************************************************
IRigidBody * const cPhysics::VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef)
{
	IRigidBody * pRigidBody = IRigidBody::Create(pDef);
	m_RigidBodyMap.insert(std::make_pair(ID, pRigidBody));
	return pRigidBody;
}

// *****************************************************************************
void cPhysics::VRemoveRigidBody(const int ID)
{
	IRigidBody * pRigidBody = FindRigidBody(ID);
	if (pRigidBody != NULL)
	{
		m_RigidBodyMap.erase(ID);
		SafeDelete(&pRigidBody);
	}
}

// *****************************************************************************
IRigidBody* cPhysics::FindRigidBody(const int ID) const
{
	RigidBodyMap::const_iterator Iter = m_RigidBodyMap.find(ID);
	if(Iter != m_RigidBodyMap.end())
	{
		return Iter->second;
	}

	return NULL;
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
