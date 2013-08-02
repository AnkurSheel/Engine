#include "stdafx.h"
#include "Physics.h"
#include "RigidBody.h"
#include "CollisionInfo.h"

using namespace Physics;
using namespace Base;
using namespace std;

IPhysics * cPhysics::s_pPhysics = NULL;

// *****************************************************************************
cPhysics::cPhysics()
	: m_Gravity(0.0f)
	, m_TimeStep(1.0f/60.0f)
	, m_Accumalator(0.0f)
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
	m_TimeStep = def.m_TimeStep;
	m_Accumalator = 0.0f;
}

// *****************************************************************************
void cPhysics::VUpdate(const float DeltaTime)
{
	int numSimulationSubSteps = 0;

	// fixed timestep
	m_Accumalator += DeltaTime;

	Clamp<float>(m_Accumalator, 0.0f, 0.1f);
	while(m_Accumalator >= m_TimeStep)
	{
		InternalStep();
		m_Accumalator -= m_TimeStep;
	}
	
	float alpha = m_Accumalator / m_TimeStep;
	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->Interpolate(alpha);
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

// *****************************************************************************
void cPhysics::InternalStep()
{
	for(auto Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->IntegrateForces();
	}

	vector<cCollisionInfo> collisions;

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
						collisions.emplace_back(c);
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
	}
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
