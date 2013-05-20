// *****************************************************************************
//  Transform2DComponent version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "Transform2DComponent.h"
#include "XMLNode.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cTransform2DComponent::m_Name = cHashedString("transform2dcomponent");

// *****************************************************************************
cTransform2DComponent::cTransform2DComponent()
	: m_LookAt(1.0f, 0.0f)
{
}

// *****************************************************************************
cTransform2DComponent::~cTransform2DComponent()
{
}

// *****************************************************************************
void cTransform2DComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}

	shared_ptr<IXMLNode> pPositionNode(pXMLNode->VGetChild("Position"));
	if(pPositionNode != NULL)
	{
		m_Position.x = pPositionNode->VGetNodeAttributeAsInt("x");
		m_Position.y = pPositionNode->VGetNodeAttributeAsInt("y");
	}
	
	shared_ptr<IXMLNode> pSizeNode(pXMLNode->VGetChild("ScaleInPixels"));
	if(pSizeNode != NULL)
	{
		m_Size.x = pSizeNode->VGetNodeAttributeAsInt("x");
		m_Size.y = pSizeNode->VGetNodeAttributeAsInt("y");
	}
}

// *****************************************************************************
void cTransform2DComponent::VCleanup()
{

}
