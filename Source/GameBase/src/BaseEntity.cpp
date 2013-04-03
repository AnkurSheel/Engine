// *****************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseEntity.h"
#include "FSM/StateMachine.h"
#include "BaseComponent.h"

using namespace AI;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

int cBaseEntity::m_siNextValidID = 0;

// *****************************************************************************
cBaseEntity::cBaseEntity(const int iID, const Base::cString strName)
: m_strName(strName)
{
	SetID(iID);
}

// *****************************************************************************
cBaseEntity::cBaseEntity(const Base::cString strName)
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
void cBaseEntity::AddComponent(cBaseComponent * pComponent)
{
	pComponent->SetOwner(this);
	m_Components.insert(std::make_pair(pComponent->GetHashedID(), pComponent));
}

// *****************************************************************************
void cBaseEntity::RemoveComponent(cBaseComponent * pComponent)
{
	ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		if(pComponent->GetHashedID() == iter->second->GetHashedID())
		{
			m_Components.erase(iter);
		}
	}
}

// *****************************************************************************
cBaseComponent * cBaseEntity::GetComponent(const cString & strComponentName)
{
	cBaseComponent * pComponent = NULL;
	unsigned long hash = cHashedString::CalculateHash(strComponentName);
	ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		if(hash == iter->second->GetHashedID())
		{
			pComponent = iter->second;
			break;
		}
	}
	return pComponent;
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