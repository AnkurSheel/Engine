// *****************************************************************************
//  TransformComponent version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "TransformComponent.h"
#include "XMLNode.hxx"
#include "EventManager.hxx"
#include "BaseEntity.hxx"
#include "EntityMovedEventData.h"
#include "EntityScaledEventData.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cHashedString	cTransformComponent::m_Name = cHashedString("transformcomponent");

// *****************************************************************************
cTransformComponent::cTransformComponent()
	: m_LookAt(1.0f, 0.0f, 0.0f)
{
}

// *****************************************************************************
cTransformComponent::~cTransformComponent()
{
}

// *****************************************************************************
void cTransformComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}

	shared_ptr<IXMLNode> pPositionNode(pXMLNode->VGetChild("Position"));
	if(pPositionNode != NULL)
	{
		m_Position.x = pPositionNode->VGetNodeAttributeAsFloat("x", 0.0f);
		m_Position.y = pPositionNode->VGetNodeAttributeAsFloat("y", 0.0f);
		m_Position.z = pPositionNode->VGetNodeAttributeAsFloat("z", 0.0f);
	}
	
	shared_ptr<IXMLNode> pSizeNode(pXMLNode->VGetChild("ScaleInPixels"));
	if(pSizeNode != NULL)
	{
		m_Size.x = pSizeNode->VGetNodeAttributeAsFloat("x", 8.0f);
		m_Size.y = pSizeNode->VGetNodeAttributeAsFloat("y", 8.0f);
		m_Size.z = pSizeNode->VGetNodeAttributeAsFloat("z", 1.0f);
	}
}

// *****************************************************************************
void cTransformComponent::VCleanup()
{

}

// *****************************************************************************
void cTransformComponent::SetPosition(const cVector3 & position)
{
	if (m_Position != position)
	{
		m_Position = position;
		shared_ptr<cEntityMovedEventData> pEvent(DEBUG_NEW cEntityMovedEventData(m_Position, m_pOwner->VGetEntityID()));
		IEventManager::Instance()->VQueueEvent(pEvent);
	}
}

// *****************************************************************************
void cTransformComponent::SetSize(const cVector3 & size)
{
	if (m_Size != size)
	{
		m_Size = size;
		shared_ptr<cEntityScaledEventData> pEvent(DEBUG_NEW cEntityScaledEventData(m_Size, m_pOwner->VGetEntityID()));
		IEventManager::Instance()->VQueueEvent(pEvent);
	}
}

// *****************************************************************************
void cTransformComponent::SetRotation(const cVector3 & rotation)
{
	if (m_Rotation != rotation)
	{
		m_Rotation = rotation;
	}
}
