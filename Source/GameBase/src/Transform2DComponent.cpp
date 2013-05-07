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
		m_vPosition.x = pPositionNode->VGetNodeAttributeAsInt("x");
		m_vPosition.y = pPositionNode->VGetNodeAttributeAsInt("y");
	}
}

// *****************************************************************************
void cTransform2DComponent::VCleanup()
{

}
