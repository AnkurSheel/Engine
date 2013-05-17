// *****************************************************************************
//  Render3DSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "Render3DSystem.h"
#include "EntityManager.hxx"
#include "Transform3DComponent.h"
#include "ModelComponent.h"
#include "Camera.hxx"

using namespace GameBase;
using namespace Utilities;
using namespace Graphics;

// *****************************************************************************
cRender3DSystem::cRender3DSystem()
	:cProcess("Render3DSystem")
{

}

// *****************************************************************************
cRender3DSystem::~cRender3DSystem()
{

}

// *****************************************************************************
void cRender3DSystem::VUpdate(const float DeltaTime)
{
	cProcess::VUpdate(DeltaTime);

	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cModelComponent::m_Name, entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cTransform3DComponent * pTransform = dynamic_cast<cTransform3DComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, cTransform3DComponent::m_Name));
		cModelComponent * pModel = dynamic_cast<cModelComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, cModelComponent::m_Name));
		if(pTransform != NULL)
		{
			pModel->UpdateTransform(pTransform);
		}
	}
}

// *****************************************************************************
void cRender3DSystem::Render(const ICamera * const pCamera)
{
	IEntityManager::EntityList entityList;
	IEntityManager::GetInstance()->VGetEntities(cModelComponent::m_Name, entityList);
	IEntityManager::EntityList::iterator enityIter;
	for(enityIter = entityList.begin(); enityIter != entityList.end(); enityIter++)
	{
		IBaseEntity * pEntity = *enityIter;
		cModelComponent * pModel = dynamic_cast<cModelComponent *>(IEntityManager::GetInstance()->VGetComponent(pEntity, cModelComponent::m_Name));
		pModel->Render(pCamera);
	}

}