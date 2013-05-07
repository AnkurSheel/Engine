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
#include "XMLNode.hxx"

using namespace AI;
using namespace Utilities;
using namespace Base;
using namespace GameBase;

int cBaseEntity::m_siNextValidID = 0;

// *****************************************************************************
cBaseEntity::cBaseEntity(const int iID)
{
	SetID(iID);
}

// *****************************************************************************
cBaseEntity::cBaseEntity()
{
	SetID(m_siNextValidID);
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
int cBaseEntity::GetID() const
{
	return m_iID;
}

// *****************************************************************************
void cBaseEntity::VInitialize()
{
	const shared_ptr<IXMLNode> pRoot = IXMLNode::Load("Paddle.xml");
	Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pRoot->VGetName() );
	Log_Write(ILogger::LT_COMMENT, 1, "Element Type : " + pRoot->VGetNodeAttribute("type"));
	
	IXMLNode::XMLNodeList List;
	pRoot->VGetChildren(List);
	IXMLNode::XMLNodeList::iterator Iter;
	for (Iter = List.begin(); Iter != List.end(); Iter++)
	{
		IXMLNode * pNode = (*Iter).get();
		Log_Write(ILogger::LT_COMMENT, 1, "Element Name : " + pNode->VGetName() );
 //       StrongActorComponentPtr pComponent(VCreateComponent(pNode));
 //       if (pComponent)
 //       {
 //           pActor->AddComponent(pComponent);
 //           pComponent->SetOwner(pActor);
 //       }
 //       else
 //       {
 //           // If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be 
 //           // partially complete so it's not worth it.  Note that the pActor instance will be destroyed because it
 //           // will fall out of scope with nothing else pointing to it.
 //           return StrongActorPtr();
 //       }
	}
	/*ComponentMap::iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		iter->second->VInitialize();
	}*/
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
	IBaseComponent * pComponent = GetComponent(strComponentName);
	if(pComponent != NULL)
	{
		ulID = pComponent->VGetID();
		m_Components.erase(ulID);
		SafeDelete(&pComponent);
	}
	return ulID;
}

// *****************************************************************************
IBaseComponent * cBaseEntity::GetComponent(const Base::cString & strComponentName)
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
void cBaseEntity::GetAllComponents(ComponentList & components) const
{
	components.clear();
	ComponentMap::const_iterator iter;
	for(iter = m_Components.begin(); iter != m_Components.end(); iter++)
	{
		components.push_back(iter->second);
	}
}
