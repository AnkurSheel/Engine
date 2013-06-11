#include "stdafx.h"
#include "RigidBody.h"

using namespace Physics;
using namespace Base;
using namespace Utilities;

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
void cRigidBody::VInitialize(const stRigidBodyDef * const pDef)
{
	if(isZero(pDef->m_Mass))
	{	
		m_InverseMass = 0.0f;
	}
	else
	{
		m_InverseMass = 1.0f / pDef->m_Mass;
	}
	m_LinearDamping = pDef->m_LinearDamping;
	m_ApplyGravity = pDef->m_ApplyGravity;
	m_TopSpeed = pDef->m_TopSpeed;
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
	Clamp<float>(m_LinearVelocity.x, -m_TopSpeed, m_TopSpeed);
	Clamp<float>(m_LinearVelocity.y, -m_TopSpeed, m_TopSpeed);
}

// *****************************************************************************
void cRigidBody::Update(const float DeltaTime)
{
	if(m_ApplyGravity)
	{
		ApplyCentralForce(cVector3(0,981, 0));
	}

	if(!m_LinearVelocity.IsZero())
	{
		m_Position += m_LinearVelocity * DeltaTime;
		m_LinearVelocity *= (1 - m_LinearDamping);
	}
}

// *****************************************************************************
IRigidBody * IRigidBody::Create()
{
	return DEBUG_NEW cRigidBody();
}