// *****************************************************************************
//  Transform3DComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "Transform3DComponent.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cTransform3DComponent::m_Name = cHashedString("transform3dcomponent");

// *****************************************************************************
cTransform3DComponent::cTransform3DComponent()
	: m_vScale(1.0f, 1.0f, 1.0f)
{
}

// *****************************************************************************
cTransform3DComponent::~cTransform3DComponent()
{
}

// *****************************************************************************
void cTransform3DComponent::VInitialize(const IXMLNode * const pXMLNode)
{
}

// *****************************************************************************
void cTransform3DComponent::VCleanup()
{

}
