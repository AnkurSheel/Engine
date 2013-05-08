// *****************************************************************************
//  EntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "EntityFactory.h"
#include "Transform2DComponent.h"
#include "SpriteComponent.h"

using namespace GameBase;

cEntityFactory * cEntityFactory::m_pInstance = NULL;

// *****************************************************************************
cEntityFactory::cEntityFactory()
{

}

// *****************************************************************************
cEntityFactory::~cEntityFactory()
{
}

// *****************************************************************************
void cEntityFactory::RegisterComponents()
{
	m_RegisteredComponents.Register<cTransform2DComponent>(cTransform2DComponent::m_Name.GetHash());
	m_RegisteredComponents.Register<cSpriteComponent>(cSpriteComponent::m_Name.GetHash());
}
