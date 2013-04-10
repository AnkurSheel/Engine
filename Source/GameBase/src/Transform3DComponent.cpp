// *****************************************************************************
//  Transform3DComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "Transform3DComponent.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cTransform3DComponent::cTransform3DComponent()
	: cBaseComponent("Transform3DComponent")
	, m_vScale(1.0f, 1.0f, 1.0f)
{
}

// *****************************************************************************
cTransform3DComponent::~cTransform3DComponent()
{
}

// *****************************************************************************
void cTransform3DComponent::VInitialize()
{
}

// *****************************************************************************
void cTransform3DComponent::VCleanup()
{

}
