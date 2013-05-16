// *****************************************************************************
//  ComponentFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "ComponentFactory.h"
#include "Transform2DComponent.h"
#include "SpriteComponent.h"
#include "KeyboardHandlerComponent.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cComponentFactory * cComponentFactory::m_pInstance = NULL;

// *****************************************************************************
cComponentFactory::cComponentFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cComponentFactory::~cComponentFactory()
{
}

// *****************************************************************************
void cComponentFactory::RegisterComponents()
{
	m_RegisteredComponents.Register<cTransform2DComponent>(cTransform2DComponent::GetName().GetHash());
	m_RegisteredComponents.Register<cSpriteComponent>(cSpriteComponent::GetName().GetHash());
	m_RegisteredComponents.Register<cKeyboardHandlerComponent>(cKeyboardHandlerComponent::GetName().GetHash());
}

// *****************************************************************************
IBaseComponent * cComponentFactory::CreateComponent(const cHashedString & Type)
{
	IBaseComponent * pComponent = m_RegisteredComponents.Create(Type.GetHash());
	return pComponent;
}

// *****************************************************************************
IBaseComponent * cComponentFactory::GetDuplicateComponent(const IBaseComponent * const pComponent)
{
	IBaseComponent * pNewComponent = m_RegisteredComponents.Duplicate(pComponent->VGetID(), pComponent);
	return pNewComponent;
}