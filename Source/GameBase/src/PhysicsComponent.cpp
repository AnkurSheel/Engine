// *****************************************************************************
//  PhysicsComponent version:  1.0   Ankur Sheel  date: 2013/05/17
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "PhysicsComponent.h"
#include "XMLNode.hxx"
#include "optional.h"
#include "RigidBody.hxx"
#include "Physics.hxx"
#include "BaseEntity.hxx"
#include "EntityManager.hxx"
#include "SpriteComponent.h"
#include "EntityMovedEventData.h"
#include "EntityScaledEventData.h"
#include "EventManager.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Physics;

cHashedString	cPhysicsComponent::m_Name = cHashedString("physicscomponent");

// *****************************************************************************
cPhysicsComponent::cPhysicsComponent()
	: m_pRigidBody(NULL)
	, m_Force(0.0f)
	, m_ApplyForce(false)
	, m_Initialized(false)
{
}

// *****************************************************************************
cPhysicsComponent::~cPhysicsComponent()
{
	VCleanup();
}

// *****************************************************************************
void cPhysicsComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}
	m_pDef = shared_ptr<Physics::stRigidBodyDef>(DEBUG_NEW stRigidBodyDef());
	m_pDef->m_ApplyGravity = pXMLNode->VGetNodeAttributeAsBool("ApplyGravity");
	
	cString value = pXMLNode->VGetChildValue("TopSpeed");
	tOptional<float> speed = value.ToFloat();
	if(speed.IsValid())
	{
		m_pDef->m_TopSpeed = *speed;
	}

	value = pXMLNode->VGetChildValue("LinearDamping");
	tOptional<float> LinearDamping = value.ToFloat();
	if(LinearDamping.IsValid())
	{
		m_pDef->m_LinearDamping = *LinearDamping;
	}

	value = pXMLNode->VGetChildValue("Force");
	tOptional<float> Force = value.ToFloat();
	if(Force.IsValid())
	{
		m_Force = *Force;
	}

	value = pXMLNode->VGetChildValue("Shape");
	if(!value.IsEmpty())
	{
		m_pDef->m_Shape = cHashedString(value.GetInLowerCase());
	}
	
	value = pXMLNode->VGetChildValue("Mass");
	tOptional<float> mass = value.ToFloat();
	if(mass.IsValid())
	{
		m_pDef->m_Mass = *mass;
	}
	
	value = pXMLNode->VGetChildValue("Kinematic");
	tOptional<bool> Kinematic = value.ToBool();
	if(Kinematic.IsValid())
	{
		m_pDef->m_Kinematic = *Kinematic;
	}

	m_pDef->m_Material = pXMLNode->VGetChildValue("Material");

}

// *****************************************************************************
void cPhysicsComponent::VOnAttached(IBaseEntity * const pOwner)
{
	cBaseComponent::VOnAttached(pOwner);
	if(m_pDef != NULL)
	{
		GetBounds(m_pDef->m_MinBound, m_pDef->m_MaxBound);
	}
	m_pRigidBody = IPhysics::GetInstance()->VAddRigidBody(m_pOwner->VGetEntityID(), m_pDef);	
}

// *****************************************************************************
void cPhysicsComponent::VCleanup()
{
	if(m_pOwner != NULL)
	{
		IPhysics::GetInstance()->VRemoveRigidBody(m_pOwner->VGetEntityID());
	}
}

// *****************************************************************************
void cPhysicsComponent::Initialize(const cVector3 & position,
	const cVector3 & rotation, const cVector3 & size)
{
	if(!m_Initialized && m_pRigidBody != NULL)
	{
		m_Initialized = true;
		m_pRigidBody->VInitialize(position);
		shared_ptr<cEntityMovedEventData> pMovedEvent(DEBUG_NEW cEntityMovedEventData(position, m_pOwner->VGetEntityID()));
		IEventManager::Instance()->VTriggerEvent(pMovedEvent);
		shared_ptr<cEntityScaledEventData> pScaledEvent(DEBUG_NEW cEntityScaledEventData(size, m_pOwner->VGetEntityID()));
		IEventManager::Instance()->VTriggerEvent(pScaledEvent);
		IPhysics::GetInstance()->VOnRigidBodyAdded(m_pRigidBody->VGetID());
	}
}

// *****************************************************************************
void cPhysicsComponent::ApplyForce(const cVector3 & Direction)
{
	m_ApplyForce = true;
	m_Direction = Direction;
	//m_pPhysicsComponent->m_CurrentAcceleration = m_pTransFormComponent->m_LookAt * m_pPhysicsComponent->m_Acceleration;
}

// *****************************************************************************
void cPhysicsComponent::Update(const int deltaTime)
{
	if(m_ApplyForce)
	{
		m_ApplyForce = false;
		if(m_pRigidBody != NULL && m_Initialized)
		{
			float force = m_Force * (float)deltaTime / 10000.0f;
			m_pRigidBody->VApplyForce(m_Direction, force);
		}
	}
}

// *****************************************************************************
cVector3 cPhysicsComponent::GetPosition() const
{
	if(m_pRigidBody != NULL)
	{
		return m_pRigidBody->VGetRenderPosition();
	}

	return cVector3::Zero();
}

// *****************************************************************************
void cPhysicsComponent::GetBounds(cVector3 & minBound, cVector3 & maxBound)
{
	if(m_pDef != NULL)
	{
		if(m_pDef->m_Shape == cHashedString("rectangle"))
		{
			IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(m_pOwner, cSpriteComponent::GetName()));
			if(pRenderableComponent != NULL)
			{
				pRenderableComponent->VGetBounds(minBound, maxBound);
			}
		}
	}
}

// *****************************************************************************
void cPhysicsComponent::OnSizeUpdated()
{
	cVector3 minBound;
	cVector3 maxBound;

	GetBounds(minBound, maxBound);
	if(m_pRigidBody != NULL)
	{
		m_pRigidBody->VUpdateCollisionShape(minBound, maxBound);
	}
}