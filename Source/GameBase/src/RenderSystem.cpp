// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RenderSystem.h"
#include "EntityManager.hxx"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "Camera.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

// *****************************************************************************
cRenderSystem::cRenderSystem()
	:cProcess("Render System")
{

}

// *****************************************************************************
cRenderSystem::~cRenderSystem()
{

}

// *****************************************************************************
void cRenderSystem::VUpdate(const int iDeltaMilliSeconds)
{
	cProcess::VUpdate(iDeltaMilliSeconds);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities("Model Component", entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransformComponent * pTransform = dynamic_cast<cTransformComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, "Transform Component"));
		cModelComponent * pModel = dynamic_cast<cModelComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, "Model Component"));
		if(pTransform != NULL)
		{
			pModel->UpdateTransform(pTransform);
		}
	}
}


// *****************************************************************************
void cRenderSystem::Render(const ICamera * const pCamera)
{
	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities("Model Component", entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cModelComponent * pModel = dynamic_cast<cModelComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, "Model Component"));
		pModel->Render(pCamera);
	}

}