// *****************************************************************************
//  Render2DSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Render2DSystem.h"
#include "EntityManager.hxx"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Camera.hxx"
#include "vector2.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

// *****************************************************************************
cRender2DSystem::cRender2DSystem()
	:cProcess("Render2DSystem")
{

}

// *****************************************************************************
cRender2DSystem::~cRender2DSystem()
{

}

// *****************************************************************************
void cRender2DSystem::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cSpriteComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransform = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		cSpriteComponent * pSprite = dynamic_cast<cSpriteComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pTransform != NULL)
		{
			cVector2 position(pTransform->m_Position.x, pTransform->m_Position.y);
			cVector2 rotation(pTransform->m_Rotation.x, pTransform->m_Rotation.y);
			cVector2 size(pTransform->m_Size.x, pTransform->m_Size.y);
			pSprite->UpdateTransform(position, rotation, size);
		}
	}
}

// *****************************************************************************
void cRender2DSystem::Render(const ICamera * const pCamera)
{
	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cSpriteComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cSpriteComponent * pSprite = dynamic_cast<cSpriteComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		pSprite->Render(pCamera);
	}
}
