// *****************************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "StdAfx.h"
#include "EntityManager.h"
#include "BaseEntity.h"
#include "BaseComponent.hxx"

using namespace Utilities;
using namespace Base;
using namespace GameBase;

IEntityManager * GameBase::cEntityManager::s_pEntityManager = NULL;

// *****************************************************************************
cEntityManager::cEntityManager()
{
	m_EntityMap.clear();
}

// *****************************************************************************
cEntityManager::~cEntityManager()
{

}

// *****************************************************************************
void cEntityManager::VRegisterEntity( IBaseEntity * const pNewEntity )
{
	Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Registering Entity: %d ", pNewEntity->VGetID()) + pNewEntity->VGetName());
	m_EntityMap.insert(std::make_pair(pNewEntity->VGetID(), pNewEntity));
	IBaseEntity::ComponentList components;
	pNewEntity->VGetAllComponents(components);
	IBaseEntity::ComponentList::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++)
	{
		VAddComponent(pNewEntity, *iter);
	}
}

// *****************************************************************************
void cEntityManager::VUnRegisterEntity( IBaseEntity * const pNewEntity )
{
	m_EntityMap.erase(pNewEntity->VGetID());
	IBaseEntity::ComponentList components;
	pNewEntity->VGetAllComponents(components);
	IBaseEntity::ComponentList::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++)
	{
		VRemoveComponent(pNewEntity, (*iter)->VGetName());
	}
}

// *****************************************************************************
IBaseEntity * const cEntityManager::VGetEntityFromID( const int iID )
{
	EntityMap::iterator iter = m_EntityMap.find(iID);
	if(iter == m_EntityMap.end())
	{
		return NULL;
	}
	return iter->second;
}

// *****************************************************************************
cString const cEntityManager::VGetEntityNameFromID( const int iID )
{
	IBaseEntity * pEntity = VGetEntityFromID(iID);
	if (pEntity != NULL)
	{
		return pEntity->VGetName();
	}
	return "";
}

// *****************************************************************************
IBaseComponent * cEntityManager::VGetComponent(IBaseEntity * pEntity,
	const Base::cString & strComponentName)
{
	return pEntity->VGetComponent(strComponentName);
}

// *****************************************************************************
void cEntityManager::VAddComponent(IBaseEntity * pEntity, 
	IBaseComponent * pComponent)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	pComponent->VInitialize();
	if(pEnt != NULL && pComponent != NULL)
	{
		pEnt->AddComponent(pComponent);
		EntityComponentMap::iterator iter = m_ComponentMap.find(pComponent->VGetID());
		if(iter == m_ComponentMap.end())
		{
			EntityList list;
			list.push_back(pEntity);
			m_ComponentMap.insert(std::make_pair(pComponent->VGetID(), list));
		}
		else
		{
			EntityList & list = iter->second;
			list.push_back(pEntity);
		}
	}
}

// *****************************************************************************
void cEntityManager::VRemoveComponent(IBaseEntity * pEntity,
	const Base::cString & strComponentName)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	unsigned long ulComponentID = 0; 
	if(pEnt != NULL)
	{
		ulComponentID = pEnt->RemoveComponent(strComponentName);
	}

	EntityComponentMap::iterator iter = m_ComponentMap.find(ulComponentID);
	if(iter == m_ComponentMap.end())
	{
		Log_Write(ILogger::LT_ERROR, 1, "Trying to remove non existent component");
	}
	else
	{
		EntityList & list = iter->second;
		list.remove(pEntity);
		if(list.empty())
		{
			m_ComponentMap.erase(ulComponentID);
		}
	}
}

// *****************************************************************************
void cEntityManager::VGetEntities(const Base::cString & strComponentName,
	EntityList & entities)
{
	unsigned long hash = cHashedString::CalculateHash(strComponentName);
	EntityComponentMap::iterator iter = m_ComponentMap.find(hash);
	if(iter == m_ComponentMap.end())
	{
		Log_Write(ILogger::LT_ERROR, 1, "Trying to access non existent component");
	}
	else
	{
		entities = iter->second;
	}
}

// *****************************************************************************
void cEntityManager::Cleanup()
{
	m_EntityMap.clear();
	for(EntityComponentMap::iterator iter = m_ComponentMap.begin(); iter != m_ComponentMap.end(); iter++)
	{
		iter->second.clear();
	}
	m_ComponentMap.clear();
}

// *****************************************************************************
IEntityManager * IEntityManager::GetInstance()
{
	if(cEntityManager::s_pEntityManager == NULL)
		cEntityManager::s_pEntityManager = DEBUG_NEW cEntityManager();
	return cEntityManager::s_pEntityManager;
}

// *****************************************************************************
void IEntityManager::Destroy()
{
	SafeDelete(&cEntityManager::s_pEntityManager);
}
