// *****************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseEntity.h"
#include "FSM/StateMachine.h"
#include "BaseComponent.h"
#include "EntityManager.hxx"

using namespace AI;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

int cBaseEntity::m_siNextValidID = 0;

// *****************************************************************************
cBaseEntity::cBaseEntity(const int iID, const Base::cString & strName)
: m_strName(strName)
{
	SetID(iID);
}

// *****************************************************************************
cBaseEntity::cBaseEntity(const Base::cString & strName)
: m_strName(strName)
{
	SetID(m_siNextValidID);
}

// *****************************************************************************
cBaseEntity::~cBaseEntity()
{
	VCleanup();
}

// *****************************************************************************
void cBaseEntity::SetID(const int iID)
{
	if(iID >= m_siNextValidID)
	{
		m_iID = iID;
	}
	else
	{
		Log_Write(ILogger::LT_ERROR, 2, cString(30, "%d is less than valid id. Setting ID to %d", m_iID, m_siNextValidID));
		m_iID = m_siNextValidID;
	}
	m_siNextValidID = m_iID + 1;
}

// *****************************************************************************
int cBaseEntity::VGetID() const
{
	return m_iID;
}

// *****************************************************************************
cString cBaseEntity::VGetName() const
{
	return m_strName;
}

// *****************************************************************************
void cBaseEntity::VInitialize()
{
	ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		iter->second->VInitialize();
	}
}

// *****************************************************************************
void cBaseEntity::AddComponent(IBaseComponent * pComponent)
{
	pComponent->VSetOwner(this);
	m_Components.insert(std::make_pair(pComponent->VGetID(), pComponent));
}

// *****************************************************************************
unsigned long cBaseEntity::RemoveComponent(const Base::cString & strComponentName)
{
	unsigned long ulID = 0; 
	IBaseComponent * pComponent = VGetComponent(strComponentName);
	if(pComponent != NULL)
	{
		ulID = pComponent->VGetID();
		m_Components.erase(ulID);
		SafeDelete(&pComponent);
	}
	return ulID;
}

// *****************************************************************************
IBaseComponent * cBaseEntity::VGetComponent(const Base::cString & strComponentName)
{
	unsigned long hash = cHashedString::CalculateHash(strComponentName);
	ComponentMap::iterator iter = m_Components.find(hash);
	if(iter == m_Components.end())
	{
		return NULL;
	}
	return iter->second;
}

// *****************************************************************************
bool cBaseEntity::VOnHandleMessage(const AI::Telegram & telegram)
{
	return false;
}

// *****************************************************************************
void cBaseEntity::VCleanup()
{
	ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		iter->second->VCleanup();
		SafeDelete(&(iter->second));
	}
	m_Components.clear();
}

// *****************************************************************************
void cBaseEntity::VGetAllComponents(ComponentList & components)
{
	components.clear();
	ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		components.push_back(iter->second);
	}
}
