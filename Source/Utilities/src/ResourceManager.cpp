// ****************************************************************************
//  ResourceManager   version:  1.0   Ankur Sheel  date: 2011/11/16
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ****************************************************************************
// 
// ****************************************************************************
#include "stdafx.h"
#include "ResourceManager.h"
#include "ResCache.hxx"

using namespace Utilities;
using namespace Base;

IResourceManager * Utilities::cResourceManager::s_pResourceManager = NULL;

// ****************************************************************************
cResourceManager::cResourceManager()
: m_pResourceCache(NULL)
{

}

// ****************************************************************************
cResourceManager::~cResourceManager()
{
	SafeDelete(&m_pResourceCache);
}

// ****************************************************************************
bool cResourceManager::VInitialize(const int SizeInMB,
	const cString & FileName, const bool UseDevelopmentDirectory)
{
	if (FileName.IsEmpty())
	{	
		Log_Write(ILogger::LT_ERROR, 1, "Empty Assets Path");
		m_pResourceCache = IResCache::CreateResourceCache(SizeInMB, "resources.zip", UseDevelopmentDirectory);
	}
	else
	{
		m_pResourceCache = IResCache::CreateResourceCache(SizeInMB, FileName, UseDevelopmentDirectory);
	}
	if(!m_pResourceCache->Init())
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not create Resource Cache.\n");
		PostQuitMessage(0);
		return false;
	}
	return true;
}

// ****************************************************************************
IResCache * cResourceManager::VGetResourceCache() const
{
	return m_pResourceCache;
}

// ****************************************************************************
IResourceManager * IResourceManager::GetInstance()
{
	if(cResourceManager::s_pResourceManager == NULL)
		cResourceManager::s_pResourceManager = DEBUG_NEW cResourceManager();
	return cResourceManager::s_pResourceManager;
}

// ****************************************************************************
void IResourceManager::Destroy()
{
	SafeDelete(&cResourceManager::s_pResourceManager);
}
