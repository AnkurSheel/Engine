// *****************************************************************************
//  InputSystem version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "InputSystem.h"
#include "EntityManager.hxx"
#include "KeyboardHandlerComponent.h"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

// *****************************************************************************
cInputSystem::cInputSystem()
	:cProcess("InputSystem")
{

}

// *****************************************************************************
cInputSystem::~cInputSystem()
{

}

// *****************************************************************************
void cInputSystem::VUpdate(const float deltaTime)
{
	cProcess::VUpdate(deltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cKeyboardHandlerComponent::GetName(), entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cKeyboardHandlerComponent * pKeyboardHandler = dynamic_cast<cKeyboardHandlerComponent*>(IEntityManager::GetInstance()->VGetComponent(pEntity, cKeyboardHandlerComponent::GetName()));
		if(pKeyboardHandler != NULL)
		{
			pKeyboardHandler->Update(deltaTime);
		}
	}
}
