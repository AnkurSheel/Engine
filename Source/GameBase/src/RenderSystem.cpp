// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RenderSystem.h"
#include "EntityManager.hxx"
#include "SpriteComponent.h"
#include "Camera.hxx"
#include "ModelComponent.h"
#include "EventManager.hxx"
#include "EntityMovedEventData.h"
#include "EntityScaledEventData.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;
using namespace Base;

// *****************************************************************************
cRenderSystem::cRenderSystem()
	:cProcess("RenderSystem")
{
	VInitialize();
}

// *****************************************************************************
cRenderSystem::~cRenderSystem()
{
	EventListenerCallBackFn listener = bind(&cRenderSystem::ActorMovedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEntityMovedEventData::m_Name);

	listener = bind(&cRenderSystem::ActorScaledListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEntityScaledEventData::m_Name);
}

void cRenderSystem::VInitialize()
{
	cProcess::VInitialize();
	EventListenerCallBackFn listener = bind(&cRenderSystem::ActorMovedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEntityMovedEventData::m_Name);

	listener = bind(&cRenderSystem::ActorScaledListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEntityScaledEventData::m_Name);
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

// *****************************************************************************
void cRenderSystem::ActorMovedListener(IEventDataPtr pEventData)
{
	shared_ptr<cEntityMovedEventData> pCastEventData = static_pointer_cast<cEntityMovedEventData>(pEventData);

	int id = pCastEventData->GetActorID();
    cVector3 position = pCastEventData->GetPosition();
	
	IBaseEntity * pEntity = IEntityManager::GetInstance()->VGetEntityFromID(id);
	if(pEntity != NULL)
	{
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pRenderableComponent == NULL)
		{
			pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		}

		if(pRenderableComponent != NULL)
		{
			pRenderableComponent->VSetPosition(position);
		}
	}
}

// *****************************************************************************
void cRenderSystem::ActorScaledListener(IEventDataPtr pEventData)
{
	shared_ptr<cEntityScaledEventData> pCastEventData = static_pointer_cast<cEntityScaledEventData>(pEventData);

	int id = pCastEventData->GetActorID();
    cVector3 size = pCastEventData->GetSize();
	
	IBaseEntity * pEntity = IEntityManager::GetInstance()->VGetEntityFromID(id);
	if(pEntity != NULL)
	{
		IRenderableComponent * pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		if(pRenderableComponent == NULL)
		{
			pRenderableComponent = dynamic_cast<IRenderableComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cSpriteComponent::GetName()));
		}

		if(pRenderableComponent != NULL)
		{
			pRenderableComponent->VSetSize(size);
		}
	}
}
