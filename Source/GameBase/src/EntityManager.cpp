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
#include "EntityFactory.h"

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
	Cleanup();
}

// *****************************************************************************
void cEntityManager::VRegisterEntity(const cString & Type)
{
	if(cEntityFactory::Instance() == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Entity Factory Not Created");
		return;
	}

	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(cEntityFactory::Instance()->VCreateEntity(Type.GetInLowerCase()));
	m_EntityMap.insert(std::make_pair(pEntity->GetID(), pEntity));
	IBaseEntity::ComponentList components;

	Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Registering Entity: %d ", pEntity->GetID())
		+ pEntity->VGetName());
	IBaseEntity::ComponentList::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++)
	{
		VAddComponent(pEntity, *iter);
	}
}

// *****************************************************************************
void cEntityManager::VUnRegisterEntity( IBaseEntity * const pNewEntity )
{
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(pNewEntity);
	if (pEntity != NULL)
	{
		EntityMap::iterator Entityiter = m_EntityMap.find(pEntity->GetID());
		if(Entityiter == m_EntityMap.end())
		{
			return;
		}
		IBaseEntity::ComponentList components;

		pEntity->GetAllComponents(components);

		IBaseEntity::ComponentList::iterator iter;
		for (iter = components.begin(); iter != components.end(); iter++)
		{
			VRemoveComponent(pNewEntity, (*iter)->VGetName());
		}
		m_EntityMap.erase(pEntity->GetID());
	}
}

// *****************************************************************************
int cEntityManager::VGetEntityID(const IBaseEntity * const pEntity) const
{
	const cBaseEntity * const pEnt = dynamic_cast<const cBaseEntity * const>(pEntity);

	if (pEnt != NULL)
	{
		return pEnt->GetID();
	}
	return 0;
}

// *****************************************************************************
IBaseEntity * const cEntityManager::VGetEntityFromID(const int iID) const
{
	EntityMap::const_iterator iter = m_EntityMap.find(iID);
	if(iter == m_EntityMap.end())
	{
		return NULL;
	}
	return iter->second;
}

// *****************************************************************************
cString cEntityManager::VGetEntityNameFromID(const int iID) const
{
	IBaseEntity * pEntity = VGetEntityFromID(iID);
	return VGetEntityName(pEntity);
}

// *****************************************************************************
cString cEntityManager::VGetEntityName(const IBaseEntity * const pEntity) const
{
	const cBaseEntity * const pEnt = dynamic_cast<const cBaseEntity * const>(pEntity);

	if (pEnt != NULL)
	{
		return pEnt->VGetName();
	}
	return "";
}

// *****************************************************************************
IBaseComponent * cEntityManager::VGetComponent(IBaseEntity * pEntity,
	const Base::cString & strComponentName)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		return pEnt->GetComponent(strComponentName);
	}
	return NULL;
	
}

// *****************************************************************************
void cEntityManager::VAddComponent(IBaseEntity * const pEntity, IBaseComponent * pComponent)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		EntityMap::iterator iter = m_EntityMap.find(pEnt->GetID());
		if(iter == m_EntityMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Adding component to unregistered entity");
			return;
		}
		if(pComponent != NULL)
		{
			pComponent->VInitialize();
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
}

// *****************************************************************************
void cEntityManager::VRemoveComponent(IBaseEntity * const pEntity,
	const Base::cString & strComponentName)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		EntityMap::iterator Entityiter = m_EntityMap.find(pEnt->GetID());
		if(Entityiter == m_EntityMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Removing component from unregistered entity");
			return;
		}

		unsigned long ulComponentID = pEnt->RemoveComponent(strComponentName);

		EntityComponentMap::iterator iter = m_ComponentMap.find(ulComponentID);
		if(iter == m_ComponentMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Trying to remove non existent component");
			return;
		}
		
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
	EntityMap::iterator iter = m_EntityMap.begin();
	while(iter != m_EntityMap.end())
	{
		IBaseEntity * pEntity = iter->second;
		iter++;
		SafeDelete(&pEntity);
		
	}

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
