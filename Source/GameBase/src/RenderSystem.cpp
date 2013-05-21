// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RenderSystem.h"
#include "EntityManager.hxx"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Camera.hxx"
#include "ModelComponent.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

// *****************************************************************************
cRenderSystem::cRenderSystem()
	:cProcess("RenderSystem")
{

}

// *****************************************************************************
cRenderSystem::~cRenderSystem()
{

}

// *****************************************************************************
void cRenderSystem::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cModelComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransformComponent = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pTransformComponent != NULL)
		{
			pRenderableComponent->VUpdateTransform(pTransformComponent->m_Position, pTransformComponent->m_Rotation, pTransformComponent->m_Size);
		}
	}
	
	entityList.clear();
	
	IEntityManager::GetInstance()->VGetEntities(cSpriteComponent::GetName(), entityList);
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransformComponent = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pTransformComponent != NULL)
		{
			pRenderableComponent->VUpdateTransform(pTransformComponent->m_Position, pTransformComponent->m_Rotation, pTransformComponent->m_Size);
		}
	}
}

// *****************************************************************************
void cRenderSystem::Render(const ICamera * const pCamera)
{
	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cModelComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		pRenderableComponent->VRender(pCamera);
	}

	entityList.clear();

	IEntityManager::GetInstance()->VGetEntities(cSpriteComponent::GetName(), entityList);
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		pRenderableComponent->VRender(pCamera);
	}
}
