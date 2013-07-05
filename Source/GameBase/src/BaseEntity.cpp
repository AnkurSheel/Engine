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
#include "TransformComponent.h"

using namespace AI;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

int cBaseEntity::m_siNextValidID = 1;

// *****************************************************************************
cEntityDef::cEntityDef()
{

}

// *****************************************************************************
cEntityDef::~cEntityDef()
{
	Cleanup();
}

// *****************************************************************************
void cEntityDef::Cleanup() 
{
	ComponentMap::iterator iter = m_Components.begin();
	while(iter != m_Components.end())
	{
		IBaseComponent * pComponent = const_cast<IBaseComponent *>(iter->second);
		iter++;
		SafeDelete(&pComponent);
	}
	m_Components.clear();
}

// *****************************************************************************
cBaseEntity::cBaseEntity()
	: m_pTransFormComponent(NULL)
{
	SetID(m_siNextValidID);
}

// *****************************************************************************
cBaseEntity::cBaseEntity(const int iID)
{
	SetID(iID);
}

// *****************************************************************************
cBaseEntity::~cBaseEntity()
{
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
void cBaseEntity::VInitialize()
{
	m_pTransFormComponent = dynamic_cast<cTransformComponent *>(GetComponent(cTransformComponent::GetName().GetHash()));
}

// *****************************************************************************
void cBaseEntity::VCleanup()
{
	/*ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		iter->second->VCleanup();
		SafeDelete(&(iter->second));
	}
	m_Components.clear();*/
	IEntityManager::GetInstance()->VUnRegisterEntity(this);
}

// *****************************************************************************
bool cBaseEntity::VOnHandleMessage(const AI::Telegram & telegram)
{
	return false;
}

// *****************************************************************************
void cBaseEntity::AddComponent(IBaseComponent * pComponent)
{
	ComponentMap::iterator iter = m_Components.find(pComponent->VGetID());
	if(iter == m_Components.end())
	{
		pComponent->VOnAttached(this);
		m_Components.insert(std::make_pair(pComponent->VGetID(), pComponent));
	}
}

// *****************************************************************************
void cBaseEntity::RemoveComponent(const unsigned long ComponentID)
{
	IBaseComponent * pComponent = GetComponent(ComponentID);
	if(pComponent != NULL)
	{
		m_Components.erase(ComponentID);
		SafeDelete(&pComponent);
	}
}

// *****************************************************************************
IBaseComponent * cBaseEntity::GetComponent(const cHashedString & ComponentName)
{
	return GetComponent(ComponentName.GetHash());
}

// *****************************************************************************
IBaseComponent * cBaseEntity::GetComponent(const unsigned long ComponentID)
{
	ComponentMap::iterator iter = m_Components.find(ComponentID);
	if(iter == m_Components.end())
	{
		return NULL;
	}
	return iter->second;
}

// *****************************************************************************
void cBaseEntity::GetAllComponents(ComponentList & components) const
{
	components.clear();
	ComponentMap::const_iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		components.push_back(iter->second);
	}
}

// *****************************************************************************
void cBaseEntity::VHandleInput(const unsigned int CharID)
{
	Log_Write(ILogger::LT_ERROR, 1, "Should be handled by derived class");
}
