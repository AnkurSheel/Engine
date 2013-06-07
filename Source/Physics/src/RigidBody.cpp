#include "stdafx.h"
#include "RigidBody.h"

using namespace Physics;
using namespace Base;

// *****************************************************************************
cRigidBody::cRigidBody()
	: m_InverseMass(0.0f)
	, m_LinearDamping(0.0f)
{
}

// *****************************************************************************
cRigidBody::~cRigidBody()
{
}

// *****************************************************************************
void cRigidBody::VInitialize(const stRigidBodyDef & def)
{
	if(isZero(def.m_Mass))
	{	
		m_InverseMass = 0.0f;
	}
	else
	{
		m_InverseMass = 1.0f / def.m_Mass;
	}
	m_LinearDamping = def.m_LinearDamping;
	m_ApplyGravity = def.m_ApplyGravity;
	m_TopSpeed = def.m_TopSpeed;
}

// *****************************************************************************
void cRigidBody::VApplyForce(const cVector3 & Direction, const float Newtons)
{
	ApplyCentralForce(Direction * Newtons);
}

// *****************************************************************************
void cRigidBody::ApplyCentralForce(const cVector3 & Force)
{
	m_LinearVelocity += (Force * m_InverseMass);
}

void cRigidBody::Update(const float DeltaTime)
{
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

IRigidBody * IRigidBody::Create()
{
	return DEBUG_NEW cRigidBody();
}