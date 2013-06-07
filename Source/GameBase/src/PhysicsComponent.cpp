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

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Physics;

Base::cHashedString	cPhysicsComponent::m_Name = cHashedString("physicscomponent");

// *****************************************************************************
cPhysicsComponent::cPhysicsComponent()
	: m_pRigidBody(NULL)
	, m_Force(0.0f)
{
}

// *****************************************************************************
cPhysicsComponent::~cPhysicsComponent()
{
}

// *****************************************************************************
void cPhysicsComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}
	stRigidBodyDef def;

	def.m_ApplyGravity = pXMLNode->VGetNodeAttributeAsBool("ApplyGravity");
	
	shared_ptr<IXMLNode> pSpeedNode(pXMLNode->VGetChild("TopSpeed"));
	cString NodeValue;
	if(pSpeedNode != NULL)
	{
		NodeValue = pSpeedNode->VGetNodeValue();
		tOptional<float> speed = NodeValue.ToFloat();
		if(speed.IsValid())
		{
			def.m_TopSpeed = *speed;
		}
	}

	shared_ptr<IXMLNode> pLinearDampingNode(pXMLNode->VGetChild("LinearDamping"));
	if(pLinearDampingNode != NULL)
	{
		NodeValue = pLinearDampingNode->VGetNodeValue();
		tOptional<float> LinearDamping = NodeValue.ToFloat();
		if(LinearDamping.IsValid())
		{
			def.m_LinearDamping = *LinearDamping;
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
	if(m_pOwner != NULL)
	{
		//IPhysics::VAddRigidBody(m_pOwner->VGetID(), def);
	}
}

// *****************************************************************************
void cPhysicsComponent::VCleanup()
{
	//IPhysics::VRemoveRigidBody(m_pOwner->VGetID());
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
		if(m_pRigidBody != NULL)
		{
			m_pRigidBody->VApplyForce(m_Direction, 10);
		}
		/// rigidbody apply force
		
	}
}