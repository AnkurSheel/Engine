#include "stdafx.h"
#include "Physics.h"
#include "RigidBody.hxx"

using namespace Physics;
using namespace Base;

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
	RigidBodyMap::iterator Iter;
	for(Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		IRigidBody * pRigidBody = Iter->second;
	}
	//if(!m_LinearVelocity.IsZero())
	//{
	//	if(m_ApplyGravity)
	//	{
	//		//fy += m * 9.81;
	//		Force.y += 981; // cm/s
	//	}
	//			
	//	//fy += -1 * 0.5 * rho * C_d * A * vy * vy;
	//	cVector3 Distance = (pPhysics->m_CurrentVelocity * DeltaTime) + (0.5f * pPhysics->m_CurrentAcceleration * DeltaTime * DeltaTime);
	//	// new_ay = fy / m;
	//	cVector3 newAcceleration = Force;
	//	cVector3 avgAcceleration = 0.5f * (newAcceleration + pPhysics->m_CurrentAcceleration);
	//	pPhysics->m_CurrentVelocity += avgAcceleration;
	//	Clamp<float>(pPhysics->m_CurrentVelocity.x, -pPhysics->m_TopSpeed, pPhysics->m_TopSpeed);
	//	Clamp<float>(pPhysics->m_CurrentVelocity.y, -pPhysics->m_TopSpeed, pPhysics->m_TopSpeed);
	//	pPhysics->m_CurrentAcceleration = cVector3::Zero();
	//	pTransform->m_Position += Distance;
	//}
	//m_LinearVelocity-= m_LinearVelocity * m_LinearDamping;
}

// *****************************************************************************
void cPhysics::VAddRigidBody(const int ID, const stRigidBodyDef & def)
{
	IRigidBody * pRigidBody = IRigidBody::Create();
	pRigidBody->VInitialize(def);
	m_RigidBodyMap.insert(std::make_pair(ID, pRigidBody));
}

// *****************************************************************************
void cPhysics::VRemoveRigidBody(const int ID)
{
	IRigidBody * const pRigidBody = FindRigidBody(ID);
	if (pRigidBody != NULL)
	{
		m_RigidBodyMap.erase(ID);
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
