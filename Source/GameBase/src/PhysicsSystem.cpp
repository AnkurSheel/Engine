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

using namespace GameBase;
using namespace Utilities;
using namespace Base;
using namespace Physics;

// *****************************************************************************
cPhysicsSystem::cPhysicsSystem()
	:cProcess("PhysicsSystem")
{

}

// *****************************************************************************
cPhysicsSystem::~cPhysicsSystem()
{
	IPhysics::Destroy();
}

// *****************************************************************************
void cPhysicsSystem::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cPhysicsComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		if(!pPhysics->GetInitialized())
		{
			cTransformComponent * pTransform = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
			pPhysics->Initialize(pTransform->GetPosition());
		}
		pPhysics->Update();
	}
	
	IPhysics::GetInstance()->VUpdate(DeltaTime);
	
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransform = dynamic_cast<cTransformComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransformComponent::GetName()));
		cPhysicsComponent * pPhysics = dynamic_cast<cPhysicsComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cPhysicsComponent::GetName()));
		pTransform->SetPosition(pPhysics->GetPosition());
	}
}
