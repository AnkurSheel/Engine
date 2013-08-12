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
#include "ComponentFactory.h"

using namespace Utilities;
using namespace Base;
using namespace GameBase;

IEntityManager * cEntityManager::s_pEntityManager = NULL;

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
void cEntityManager::VInitializeEntityFactory(shared_ptr<cEntityFactory> pEntityFactory)
{
	if(m_pEntityFactory == NULL && pEntityFactory != NULL)
	{
		m_pEntityFactory = pEntityFactory;
		m_pEntityFactory->VRegisterEntities();
	}
}

// *****************************************************************************
void cEntityManager::VInitializeComponentFactory(shared_ptr<cComponentFactory> pComponentFactory)
{
	if(m_pComponentFactory == NULL && pComponentFactory != NULL)
	{
		m_pComponentFactory = pComponentFactory;
		m_pComponentFactory->VRegisterComponents();
	}
}
// *****************************************************************************
void cEntityManager::VAddEntity(IBaseEntity * const pNewEntity)
{
	InitializeEntity(pNewEntity);
}

// *****************************************************************************
IBaseEntity * const cEntityManager::VAddEntity(const cString & Type)
{
	if(m_pEntityFactory == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Entity Factory Not Created");
		return NULL;
	}

	IBaseEntity * pEntity = m_pEntityFactory->VCreateEntity(cHashedString(Type.GetInLowerCase()));
	if (pEntity == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Entity " + Type + " Not Created");
		return NULL;
	}

	InitializeEntity(pEntity);

	return pEntity;
}

// *****************************************************************************
void cEntityManager::VDeleteEntity( IBaseEntity * const pNewEntity )
{
	cBaseEntity * pEntity = dynamic_cast<cBaseEntity *>(pNewEntity);
	if (pEntity != NULL)
	{
		EntityMap::iterator Entityiter = m_EntityMap.find(pEntity->VGetEntityID());
		if(Entityiter == m_EntityMap.end())
		{
			return;
		}
		IBaseEntity::ComponentList components;

		pEntity->GetAllComponents(components);

		IBaseEntity::ComponentList::iterator iter;
		for (iter = components.begin(); iter != components.end(); iter++)
		{
			VRemoveComponent(pNewEntity, (*iter)->VGetID());
		}
		m_EntityMap.erase(pEntity->VGetEntityID());
	}
}

// *****************************************************************************
int cEntityManager::VGetEntityID(const IBaseEntity * const pEntity) const
{
	const cBaseEntity * const pEnt = dynamic_cast<const cBaseEntity * const>(pEntity);

	if (pEnt != NULL)
	{
		return pEnt->VGetEntityID();
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
	const cHashedString & ComponentName)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		return pEnt->GetComponent(ComponentName);
	}
	return NULL;
	
}

// *****************************************************************************
void cEntityManager::VAddComponent(IBaseEntity * const pEntity, IBaseComponent * pComponent)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		EntityMap::iterator iter = m_EntityMap.find(pEnt->VGetEntityID());
		if(iter == m_EntityMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Adding component to unregistered entity");
			return;
		}

		if(pComponent != NULL)
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
}

// *****************************************************************************
void cEntityManager::VRemoveComponent(IBaseEntity * const pEntity,
	const unsigned long ComponentID)
{
	cBaseEntity * pEnt = dynamic_cast<cBaseEntity *>(pEntity);
	if (pEnt != NULL)
	{
		EntityMap::iterator Entityiter = m_EntityMap.find(pEnt->VGetEntityID());
		if(Entityiter == m_EntityMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Removing component from unregistered entity");
			return;
		}

		pEnt->RemoveComponent(ComponentID);

		EntityComponentMap::iterator iter = m_ComponentMap.find(ComponentID);
		if(iter == m_ComponentMap.end())
		{
			Log_Write(ILogger::LT_ERROR, 1, "Trying to remove non existent component");
			return;
		}
		
		EntityList & list = iter->second;
		list.remove(pEntity);
		if(list.empty())
		{
			m_ComponentMap.erase(ComponentID);
		}
	}
}

// *****************************************************************************
void cEntityManager::VGetEntities(const cHashedString & Component,
	EntityList & entities)
{
	EntityComponentMap::iterator iter = m_ComponentMap.find(Component.GetHash());
	if(iter != m_ComponentMap.end())
	{
		entities = iter->second;
	}
}

// *****************************************************************************
void cEntityManager::VUpdate(const float deltaTime)
{
	EntityMap::iterator iter = m_EntityMap.begin();
	for(iter != m_EntityMap.begin(); iter != m_EntityMap.end(); iter++)
	{
		IBaseEntity * pEntity = iter->second;
		pEntity->VOnUpdate(deltaTime);
	}
}

// *****************************************************************************
void cEntityManager::InitializeEntity(IBaseEntity * const pEntity)
{
	cBaseEntity * pBaseEntity = dynamic_cast<cBaseEntity *>(pEntity);
	m_EntityMap.insert(std::make_pair(pBaseEntity->VGetEntityID(), pEntity));

	Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Registering Entity: %d ", pBaseEntity->VGetEntityID())
		+ pEntity->VGetName());

	pEntity->VInitialize();

	IBaseEntity::ComponentList components;
	pBaseEntity->GetAllComponents(components);

	IBaseEntity::ComponentList::iterator iter;
	for (iter = components.begin(); iter != components.end(); iter++)
	{
		VAddComponent(pEntity, *iter);
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
