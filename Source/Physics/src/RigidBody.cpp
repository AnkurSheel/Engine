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