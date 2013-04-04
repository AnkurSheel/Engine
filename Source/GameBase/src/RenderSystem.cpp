// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RenderSystem.h"
#include "EntityManager.hxx"

using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cRenderSystem::cRenderSystem()
	:cProcess("RenderingSystem")
{

}

// *****************************************************************************
cRenderSystem::~cRenderSystem()
{

}

// *****************************************************************************
void cRenderSystem::VInitialize()
{
	cProcess::VInitialize();
	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities("ModelComponent", entityList);
}

// *****************************************************************************
void cRenderSystem::VUpdate(const int iDeltaMilliSeconds)
{
	cProcess::VUpdate(iDeltaMilliSeconds);
}
