// *****************************************************************************
//  PhysicsSystem version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "PhysicsSystem.h"
#include "EntityManager.hxx"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "physics.hxx"
#include "EventManager.hxx"
#include "EntityInitializedEventData.h"
#include "EntityScaledEventData.h"

using namespace GameBase;
using namespace Utilities;
using namespace Base;
using namespace Physics;

// *****************************************************************************
cPhysicsSystem::cPhysicsSystem()
	:cProcess("PhysicsSystem")
{
	VInitialize();
}

// *****************************************************************************
cPhysicsSystem::~cPhysicsSystem()
{
	IPhysics::Destroy();

	EventListenerCallBackFn listener = bind(&cPhysicsSystem::ActorInitializedListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEntityInitializedEventData::m_Name);

	listener = bind(&cPhysicsSystem::ActorScaledListener, this, _1);
	IEventManager::Instance()->VRemoveListener(listener, cEntityScaledEventData::m_Name);
}

// *****************************************************************************
void cPhysicsSystem::VInitialize()
{
	cProcess::VInitialize();

	EventListenerCallBackFn listener = bind(&cPhysicsSystem::ActorInitializedListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEntityInitializedEventData::m_Name);

	listener = bind(&cPhysicsSystem::ActorScaledListener, this, _1);
	IEventManager::Instance()->VAddListener(listener, cEntityScaledEventData::m_Name);

	IPhysics::GetInstance()->VInitialize("Physics");

}

// *****************************************************************************
void cPhysicsSystem::VUpdate(const float deltaTime)
{
	cProcess::VUpdate(deltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cPhysicsComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		pPhysics->Update();
	}
	
	IPhysics::GetInstance()->VUpdate(deltaTime);
	
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransform = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		pTransform->SetPosition(pPhysics->GetPosition());
	}
}

// *****************************************************************************
void cPhysicsSystem::ActorInitializedListener(IEventDataPtr pEventData)
{
	shared_ptr<cEntityInitializedEventData> pCastEventData = static_pointer_cast<cEntityInitializedEventData>(pEventData);

	int id = pCastEventData->GetActorID();

	IBaseEntity * pEntity = IEntityManager::GetInstance()->VGetEntityFromID(id);

	cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
	if(pPhysics != NULL)
	{
		pPhysics->Initialize(pCastEventData->GetPosition(), pCastEventData->GetRotation());
	}
}

// *****************************************************************************
void cPhysicsSystem::ActorScaledListener(IEventDataPtr pEventData)
{
	shared_ptr<cEntityScaledEventData> pCastEventData = static_pointer_cast<cEntityScaledEventData>(pEventData);

	int id = pCastEventData->GetActorID();
    cVector3 size = pCastEventData->GetSize();
	
	IBaseEntity * pEntity = IEntityManager::GetInstance()->VGetEntityFromID(id);
	if(pEntity != NULL)
	{
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		if(pPhysics != NULL)
		{
			pPhysics->OnSizeUpdated();
		}
	}
}
