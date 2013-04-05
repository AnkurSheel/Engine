// *****************************************************************************
//  TransformComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "TransformComponent.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cTransformComponent::cTransformComponent()
	: cBaseComponent("Transform Component")
	, m_vScale(1.0f, 1.0f, 1.0f)
{
}

// *****************************************************************************
cTransformComponent::~cTransformComponent()
{
}

// *****************************************************************************
void cTransformComponent::VInitialize()
{
}

// *****************************************************************************
void cTransformComponent::VCleanup()
{

}
