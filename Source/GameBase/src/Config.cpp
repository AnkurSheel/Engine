// *****************************************************************************
//  Config   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "Config.h"
#include "XMLNode.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "BaseEntity.h"
#include "BaseComponent.hxx"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cConfig * cConfig::m_pInstance = NULL;

// *****************************************************************************
cConfig::cConfig()
{

}

// *****************************************************************************
cConfig::~cConfig()
{
	Cleanup();
}

// *****************************************************************************
const cEntityDef * const cConfig::GetEntityDef(const Base::cHashedString & EntityType)
{
	if(m_pInstance != NULL)
	{
		return m_pInstance->m_EntityDefs[EntityType.GetHash()];
	}
	return NULL;
}

// *****************************************************************************
void cConfig::InitPrivate(const cString & FileName)
{
	IResource * pResource = IResource::CreateResource(cGameDirectories::GetDesignDirectory() + FileName + ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	shared_ptr<IXMLNode> pRoot;
	SafeDelete(&pResource);
	if(pXMLFile != NULL)
	{
		pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}

	if (pRoot == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not find " + FileName + ".xml");
		return;
	}

	IXMLNode::XMLNodeList List;
	pRoot->VGetChildren(List);
	IXMLNode::XMLNodeList::iterator Iter;
	for (Iter = List.begin(); Iter != List.end(); Iter++)
	{
		IXMLNode * pEntityDefNode = (*Iter).get();
		Log_Write(ILogger::LT_COMMENT, 2, "Element Name : " + pEntityDefNode->VGetName() );
		cEntityDef * pEntityDef = DEBUG_NEW cEntityDef();
		m_EntityDefs[cHashedString::CalculateHash(pEntityDefNode->VGetName().GetInLowerCase())] = pEntityDef;

		IXMLNode::XMLNodeList List;
		pEntityDefNode->VGetChildren(List);
		IXMLNode::XMLNodeList::iterator Iter;
		for (Iter = List.begin(); Iter != List.end(); Iter++)
		{
			IXMLNode * pComponentDefNode = (*Iter).get();
			Log_Write(ILogger::LT_COMMENT, 2, "Element Name : " + pComponentDefNode->VGetName() );

			unsigned long hash = cHashedString::CalculateHash(pComponentDefNode->VGetName().GetInLowerCase());
			IBaseComponent * pComponent = m_RegisteredComponents.Create(hash);
			if(pComponent != NULL)
			{
				pComponent->VInitialize(pComponentDefNode);
				pEntityDef->m_Components[hash] = pComponent;
			}
		}
	}
}

// *****************************************************************************
void cConfig::Cleanup()
{
	EnitityDefMap ::iterator iter = m_EntityDefs.begin();
	while(iter != m_EntityDefs.end())
	{
		cEntityDef * pEntityDef = const_cast<cEntityDef *>(iter->second);
		iter++;
		SafeDelete(&pEntityDef);
	}
	m_EntityDefs.clear();
}
