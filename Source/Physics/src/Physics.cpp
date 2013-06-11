#include "stdafx.h"
#include "Physics.h"
#include "RigidBody.h"

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
	RigidBodyMap::iterator Iter;
	for(Iter = m_RigidBodyMap.begin(); Iter != m_RigidBodyMap.end(); Iter++)
	{
		cRigidBody * pRigidBody = dynamic_cast<cRigidBody*>(Iter->second);
		pRigidBody->Update(DeltaTime);
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
IRigidBody * const cPhysics::VAddRigidBody(const int ID, const stRigidBodyDef * const pDef)
{
	IRigidBody * pRigidBody = IRigidBody::Create();
	pRigidBody->VInitialize(pDef);
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
