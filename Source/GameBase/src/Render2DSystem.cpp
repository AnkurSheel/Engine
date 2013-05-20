// *****************************************************************************
//  Render2DSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Render2DSystem.h"
#include "EntityManager.hxx"
#include "Transform2DComponent.h"
#include "SpriteComponent.h"
#include "Camera.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

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
		cTransform2DComponent * pTransform = dynamic_cast<cTransform2DComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransform2DComponent::GetName()));
		cSpriteComponent * pSprite = dynamic_cast<cSpriteComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pTransform != NULL)
		{
			pSprite->UpdateTransform(pTransform->m_Position, pTransform->m_Rotation, pTransform->m_Size);
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
