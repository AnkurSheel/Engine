// *****************************************************************************
//  PhysicsComponent version:  1.0   Ankur Sheel  date: 2013/05/17
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "PhysicsComponent.h"
#include "XMLNode.hxx"
#include "optional.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cPhysicsComponent::m_Name = cHashedString("physicscomponent");

// *****************************************************************************
cPhysicsComponent::cPhysicsComponent()
	: m_ApplyGravity(false)
	, m_TopSpeed(0)
	, m_Acceleration(0)
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

	m_ApplyGravity = pXMLNode->VGetNodeAttributeAsBool("ApplyGravity");
	
	shared_ptr<IXMLNode> pSpeedNode(pXMLNode->VGetChild("TopSpeed"));
	cString NodeValue;
	if(pSpeedNode != NULL)
	{
		NodeValue = pSpeedNode->VGetNodeValue();
		tOptional<float> speed = NodeValue.ToFloat();
		if(speed.IsValid())
		{
			m_TopSpeed = *speed;
		}
	}

	shared_ptr<IXMLNode> pAccelNode(pXMLNode->VGetChild("Acceleration"));
	if(pSpeedNode != NULL)
	{
		NodeValue = pAccelNode->VGetNodeValue();
		tOptional<float> accel = NodeValue.ToFloat();
		if(accel.IsValid())
		{
			m_Acceleration = *accel;
		}
	}
}

// *****************************************************************************
void cPhysicsComponent::VCleanup()
{
}

// *****************************************************************************
void cPhysicsComponent::Update()
{
}
