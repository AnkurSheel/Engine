#include "stdafx.h"
#include "RigidBody.h"
#include "Shape.hxx"
#include "RectangleShape.h"
#include "Physics.h"

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
	, m_ID(-1)
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
	, m_RenderPosition(other.m_RenderPosition)
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
	m_RenderPosition = other.m_RenderPosition;

	return *this;
}

// *****************************************************************************
void cRigidBody::VInitialize(const cVector3 & position)
{
	if(!m_Initialized)
	{
		m_Initialized = true;
		m_Position = position;
	}
}

// *****************************************************************************
void cRigidBody::VApplyForce(const cVector3 & Direction, const float Newtons)
{
	m_Force += (Direction * Newtons);
}

// *****************************************************************************
void cRigidBody::VUpdateCollisionShape(const cVector3 & minBound, const cVector3 & maxBound)
{
	if(m_pCollisionShape != NULL)
	{
		m_pCollisionShape->VUpdateBounds(m_Position, minBound, maxBound);
	}
}

// *****************************************************************************
void cRigidBody::OnCreated(shared_ptr<const stRigidBodyDef> pDef, const int ID)
{
	if(pDef == NULL)
	{
		return;
	}

	m_ID = ID;
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
	m_MaterialData = cPhysics::LookUpMaterialData(pDef->m_Material);
}

// *****************************************************************************
void cRigidBody::IntegrateForces(const float timeStep)
{
	if(!m_Initialized || isZero(m_InverseMass))
	{
		return;
	}

	if(m_ApplyGravity)
	{
		ApplyImpulse(cVector3(0, cPhysics::GetGravity() * timeStep / 2.0f, 0));
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

	if(m_ApplyGravity)
	{
		ApplyImpulse(cVector3(0, cPhysics::GetGravity() * timeStep / 2.0f, 0));
	}

	if(!m_LinearVelocity.IsZero())
	{
		m_Position += (m_LinearVelocity * timeStep);
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
		m_Position += (correction * m_InverseMass);
	}
}

// *****************************************************************************
void cRigidBody::Sync(const float alpha)
{
	m_RenderPosition = cVector3::Lerp(m_PreviousPosition, m_Position, alpha);

	if(m_Position != m_PreviousPosition)
	{
		OnMoved();
	}
}

// *****************************************************************************
void cRigidBody::OnMoved()
{
	if(m_pCollisionShape != NULL)
	{
		m_pCollisionShape->VOnMoved(m_Position - m_PreviousPosition);
	}

	m_PreviousPosition = m_Position;
}

// *****************************************************************************
IRigidBody * IRigidBody::Create(shared_ptr<const stRigidBodyDef> pDef, const int ID)
{
	cRigidBody * pBody = DEBUG_NEW cRigidBody();
	if(pBody)
	{
		pBody->OnCreated(pDef, ID);
	}
	return pBody;
}