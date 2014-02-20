//  *******************************************************************************************************************
//  UiManager   version:  1.0   Ankur Sheel  date: 2014/02/20
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#include "stdafx.h"
#include "UiManager.h"
#include "UiCOntrolFactory.h"
#include "BaseControl.hxx"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"
#include "XMLNode.hxx"

using namespace Utilities;
using namespace Base;
using namespace Graphics;

cUiManager * cUiManager::s_pUiManager = NULL;

//  *******************************************************************************************************************
cUiManager::cUiManager()
{
}

//  *******************************************************************************************************************
cUiManager::~cUiManager()
{
}

//  *******************************************************************************************************************
void cUiManager::Initialize()
{
	m_pUiFactory = shared_ptr<cUiControlFactory>(DEBUG_NEW cUiControlFactory());
	m_pUiFactory->VRegisterUiControls();
}

//  *******************************************************************************************************************
const shared_ptr<IBaseControl> cUiManager::VCreateUI(const Base::cString & FileName)
{
	shared_ptr<IBaseControl> pUi = NULL;
	if(FileName.IsEmpty())
	{
		Log_Write(ILogger::LT_ERROR, 1, "FileName is empty");
		return NULL;
	}

	IResource * pResource = IResource::CreateResource(cGameDirectories::GetUiDirectory() + FileName +  ".xml");
	shared_ptr<IResHandle> pXMLFile = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	SafeDelete(&pResource);

	shared_ptr<IXMLNode> pRoot;
	if(pXMLFile != NULL)
	{
		pRoot = shared_ptr<IXMLNode>(IXMLNode::Parse(pXMLFile->GetBuffer(), pXMLFile->GetSize()));
	}

	if (pRoot == NULL)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not find " + FileName + " .xml");
		return NULL;
	}

	pUi = shared_ptr<IBaseControl>(m_pUiFactory->CreateUiControl(cHashedString("windowcontrol")));
	pUi->VInitialize(pRoot);

	shared_ptr<IXMLNode> pControls = pRoot->VGetChild("Controls");

	IXMLNode::XMLNodeList List;
	pControls->VGetChildren(List);
	IXMLNode::XMLNodeList::iterator Iter;
	cString type;
	for (Iter = List.begin(); Iter != List.end(); Iter++)
	{
		shared_ptr<IXMLNode> pControlDefNode = *Iter;
		type = pControlDefNode->VGetName();
		Log_Write(ILogger::LT_COMMENT, 2, "Element Name : " + type);

		shared_ptr<IBaseControl> pControl(m_pUiFactory->CreateUiControl(cHashedString(type.GetInLowerCase())));

		if (pControl == NULL)
		{
			Log_Write(ILogger::LT_ERROR, 1, "Ui Control " + type + " Not Created");
		}
		else
		{
			pControl->VInitialize(pControlDefNode);
			pUi->VAddChildControl(pControl);
		}
	}
	return pUi;
}

//  *******************************************************************************************************************
IUiManager * IUiManager::GetInstance()
{
	if(cUiManager::s_pUiManager == NULL)
	{
		cUiManager::s_pUiManager = DEBUG_NEW cUiManager();
		cUiManager::s_pUiManager->Initialize();
	}
	return cUiManager::s_pUiManager;
}

//  *******************************************************************************************************************
void IUiManager::Destroy()
{
	SafeDelete(&cUiManager::s_pUiManager);
}
