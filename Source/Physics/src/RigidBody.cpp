#include "stdafx.h"
#include "RigidBody.h"
#include "Shape.hxx"
#include "RectangleShape.h"

using namespace Physics;
using namespace Base;
using namespace Utilities;

// *****************************************************************************
cRigidBody::cRigidBody()
	: m_InverseMass(0.0f)
	, m_LinearDamping(0.0f)
	, m_pCollisionShape(NULL)
	, m_ApplyGravity(false)
	, m_TopSpeed(0.0f)
	, m_Initialized(false)
{
}

// *****************************************************************************
cRigidBody::~cRigidBody()
{
	SafeDelete(&m_pCollisionShape);
}

// *****************************************************************************
cRigidBody::cRigidBody(const cRigidBody & other)
	: m_LinearVelocity(other.m_LinearVelocity)
	, m_Position(other.m_Position)
	, m_pCollisionShape(other.m_pCollisionShape->VDuplicate())
	, m_InverseMass(other.m_InverseMass)
	, m_LinearDamping(other.m_LinearDamping)
	, m_TopSpeed(other.m_TopSpeed)
	, m_ApplyGravity(other.m_ApplyGravity)
	, m_Initialized(other.m_Initialized)
	, m_Force(other.m_Force)
	, m_PreviousPosition(other.m_PreviousPosition)
{
}

// *****************************************************************************
cRigidBody & cRigidBody::operator =(const cRigidBody & other)
{
	m_LinearVelocity = other.m_LinearVelocity;
	m_Position = other.m_Position;
	m_pCollisionShape = other.m_pCollisionShape->VDuplicate();
	m_InverseMass = other.m_InverseMass;
	m_LinearDamping = other.m_LinearDamping;
	m_TopSpeed = other.m_TopSpeed;
	m_ApplyGravity = other.m_ApplyGravity;
	m_Initialized = other.m_Initialized;
	m_Force = other.m_Force;
	m_PreviousPosition = other.m_PreviousPosition;

	return *this;
}

// *****************************************************************************
void cRigidBody::VInitialize(const cVector3 & position)
{
	if(!m_Initialized)
	{
		m_Initialized = true;
		m_PreviousPosition = position;
		VSetPosition(position);
	}
}

// *****************************************************************************
void cRigidBody::VApplyForce(const cVector3 & Direction, const float Newtons)
{
	m_Force += (Direction * Newtons);
}

// *****************************************************************************
void cRigidBody::VUpdateBounds(const cVector3 & minBound, const cVector3 & maxBound)
{
	if(m_pCollisionShape != NULL)
	{
		m_pCollisionShape->VUpdateBounds(m_Position, minBound, maxBound);
	}
}

// *****************************************************************************
void cRigidBody::VSetPosition(const cVector3 & position)
{
	if(m_Position != position)
	{
		if(m_pCollisionShape != NULL)
		{
			m_pCollisionShape->VOnMoved(position - m_Position);
		}
		m_Position = position;
	}

}

// *****************************************************************************
void cRigidBody::OnCreated(shared_ptr<const stRigidBodyDef> pDef)
{
	if(pDef == NULL)
	{
		return;
	}

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
	if(pDef->m_Shape == cRectangleShape::m_Name)
	{
		m_pCollisionShape = IShape::CreateRectangleShape();
		m_pCollisionShape->VInitialize(pDef->m_MinBound, pDef->m_MaxBound);
	}
}

// *****************************************************************************
void cRigidBody::IntegrateForces()
{
	if(!m_Initialized || isZero(m_InverseMass))
	{
		return;
	}

	if(m_ApplyGravity)
	{
		VApplyForce(cVector3(0,1, 0), 981);
	}

	m_LinearVelocity += (m_Force * m_InverseMass);
	Clamp<float>(m_LinearVelocity.x, -m_TopSpeed, m_TopSpeed);
	Clamp<float>(m_LinearVelocity.y, -m_TopSpeed, m_TopSpeed);
	m_Force = cVector3::Zero();
}

// *****************************************************************************
void cRigidBody::IntegrateVelocity(const float timeStep)
{
	if(!m_Initialized)
	{
		return;
	}

	if(!m_LinearVelocity.IsZero())
	{
		VSetPosition(m_Position + (m_LinearVelocity * timeStep));
		m_LinearVelocity *= (1 - m_LinearDamping);
	}
}

// *****************************************************************************
void cRigidBody::ApplyImpulse(const cVector3 & impulse)
{
	m_LinearVelocity += (m_InverseMass * impulse);
}

// *****************************************************************************
void cRigidBody::ApplyPositionCorrection(const cVector3 & correction)
{
	if(!isZero(m_InverseMass))
	{
		VSetPosition(m_Position + (correction * m_InverseMass));
	}
}

// *****************************************************************************
void cRigidBody::Interpolate(const float alpha)
{
	cVector3 position = m_Position;
	if(m_PreviousPosition != m_Position)
	{
		position = cVector3::Lerp(m_PreviousPosition, m_Position, alpha);
	}
	m_PreviousPosition = m_Position;
	VSetPosition(position);
}

// *****************************************************************************
IRigidBody * IRigidBody::Create(shared_ptr<const stRigidBodyDef> pDef)
{
	cRigidBody * pBody = DEBUG_NEW cRigidBody();
	if(pBody)
	{
		pBody->OnCreated(pDef);
	}
	return pBody;
}