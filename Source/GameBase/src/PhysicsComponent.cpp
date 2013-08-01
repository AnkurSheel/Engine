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
	
	shared_ptr<IXMLNode> pSpeedNode(pXMLNode->VGetChild("TopSpeed"));
	cString NodeValue;
	if(pSpeedNode != NULL)
	{
		NodeValue = pSpeedNode->VGetNodeValue();
		tOptional<float> speed = NodeValue.ToFloat();
		if(speed.IsValid())
		{
			m_pDef->m_TopSpeed = *speed;
		}
	}

	shared_ptr<IXMLNode> pLinearDampingNode(pXMLNode->VGetChild("LinearDamping"));
	if(pLinearDampingNode != NULL)
	{
		NodeValue = pLinearDampingNode->VGetNodeValue();
		tOptional<float> LinearDamping = NodeValue.ToFloat();
		if(LinearDamping.IsValid())
		{
			m_pDef->m_LinearDamping = *LinearDamping;
		}
	}

	shared_ptr<IXMLNode> pForceNode(pXMLNode->VGetChild("Force"));
	if(pForceNode != NULL)
	{
		NodeValue = pForceNode->VGetNodeValue();
		tOptional<float> Force = NodeValue.ToFloat();
		if(Force.IsValid())
		{
			m_Force = *Force;
		}
	}

	shared_ptr<IXMLNode> pShapeNode(pXMLNode->VGetChild("Shape"));
	if(pShapeNode != NULL)
	{
		NodeValue = pShapeNode->VGetNodeValue();
		if(!NodeValue.IsEmpty())
		{
			m_pDef->m_Shape = cHashedString(NodeValue.GetInLowerCase());
		}
	}

	shared_ptr<IXMLNode> pMassNode(pXMLNode->VGetChild("Mass"));
	if(pMassNode != NULL)
	{
		NodeValue = pMassNode->VGetNodeValue();
		tOptional<float> mass = NodeValue.ToFloat();
		if(mass.IsValid())
		{
			m_pDef->m_Mass = *mass;
		}
	}
}

// *****************************************************************************
void cPhysicsComponent::VOnAttached(IBaseEntity * const pOwner)
{
	cBaseComponent::VOnAttached(pOwner);
	if(m_pDef != NULL)
	{
		GetBounds(m_pDef->m_MinBound, m_pDef->m_MaxBound);
	}
	m_pRigidBody = IPhysics::GetInstance()->VAddRigidBody(m_pOwner->VGetID(), m_pDef);	
}

// *****************************************************************************
void cPhysicsComponent::VCleanup()
{
	if(m_pOwner != NULL)
	{
		IPhysics::GetInstance()->VRemoveRigidBody(m_pOwner->VGetID());
	}
}

// *****************************************************************************
void cPhysicsComponent::Initialize(const cVector3 & position,
	const cVector3 & rotation)
{
	if(!m_Initialized && m_pRigidBody != NULL)
	{
		m_Initialized = true;
		m_pRigidBody->VInitialize(position);
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
void cPhysicsComponent::Update()
{
	if(m_ApplyForce)
	{
		m_ApplyForce = false;
		if(m_pRigidBody != NULL && m_Initialized)
		{
			m_pRigidBody->VApplyForce(m_Direction, m_Force);
		}
	}
}

// *****************************************************************************
cVector3 cPhysicsComponent::GetPosition() const
{
	if(m_pRigidBody != NULL)
	{
		return m_pRigidBody->VGetPosition();
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
		m_pRigidBody->VUpdateBounds(minBound, maxBound);
	}
}