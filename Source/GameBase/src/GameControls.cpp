// *****************************************************************************
//  GameControls   version:  1.0   Ankur Sheel  date: 2013/03/19
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameControls.h"
#include "XMLFileio.hxx"

using namespace Base;
using namespace GameBase;
using namespace Utilities;

// *****************************************************************************
cGameControls::cGameControls(const cString & strPath)
: m_strKeysFile(strPath + "controls.dat")
{
}

// *****************************************************************************
cGameControls::~cGameControls()
{
	m_keyMap.clear();
}

// *****************************************************************************
cGameControls::KeyMapping cGameControls::GetKeyMap() const
{
	return m_keyMap;
}

// *****************************************************************************
void cGameControls::SetKey(const int iKeyIndex, const unsigned int uiKey)
{
	unsigned int uiPrevKey = m_keyMap[iKeyIndex].m_uiKeyCode;
	
	// assign the new key
	m_keyMap[iKeyIndex].m_uiKeyCode = uiKey;

	// If any other action already had the key, reassign it to prevent
	// unwanted behavior becuase of clashes
	for(KeyMapping::iterator iter = m_keyMap.begin(); iter != m_keyMap.end(); iter++)
	{
		if(iter->second.m_uiKeyCode == uiKey && iter->first != iKeyIndex)
		{
			iter->second.m_uiKeyCode = uiPrevKey;
		}
	}
}

// *****************************************************************************
cString cGameControls::GetKeyName(const unsigned int uiKey)
{
	int scanCode = MapVirtualKey(uiKey, MAPVK_VK_TO_VSC);
 
	switch (uiKey)
	{
		// arrow keys
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		// page up and page down 
	case VK_PRIOR:
	case VK_NEXT:

	case VK_HOME: 
	case VK_END: 
	case VK_INSERT:
	case VK_DELETE: 
	case VK_DIVIDE: 
	case VK_NUMLOCK:
		{
			scanCode |= 0x100; //set extended bit
			break;
		}
	}
	char keyName[50];
    GetKeyNameText(scanCode << 16,  keyName, sizeof(keyName));
	return keyName;
}

// *****************************************************************************
void cGameControls::Save()
{
	IXMLFileIO * pXml = IXMLFileIO::CreateXMLFile();

	pXml->VInitializeForSave("Keys", "");
	cString strElementName;
	for(KeyMapping::iterator iter = m_keyMap.begin(); iter != m_keyMap.end(); iter++)
	{
		strElementName = pXml->VAddElement("Keys", "Key", cString(20, "%d",iter->first), "");
		pXml->VAddAttribute(strElementName, "name", iter->second.m_strDisplayName);
		pXml->VAddAttribute(strElementName, "code", static_cast<int>(iter->second.m_uiKeyCode));
	}
	pXml->VSave(m_strKeysFile);
	SafeDelete(&pXml);
}

// *****************************************************************************
void cGameControls::Load()
{
	DWORD attr = GetFileAttributes(m_strKeysFile.GetData());
	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		VSetDefaults();
		Save();
	}
	else
	{
		IXMLFileIO	* pXml = IXMLFileIO::CreateXMLFile();
		if(pXml->VLoad(m_strKeysFile))
		{
			m_keyMap.clear();
			std::vector<cString> vKeyIDs;
			pXml->VGetAllChildrenNames("Keys", vKeyIDs);
			int iNoOfKeys= vKeyIDs.size();
			stGameControl gameControl;
			std::vector<cString>::iterator iter;
			for(iter = vKeyIDs.begin(); iter != vKeyIDs.end(); iter++)
			{
				cString strKeyID = (*iter);
				int iKeyIndex = pXml->VGetNodeAttributeAsInt(strKeyID, "id");
				gameControl.m_strDisplayName = pXml->VGetNodeAttribute(strKeyID, "name");
				gameControl.m_uiKeyCode = pXml->VGetNodeAttributeAsInt(strKeyID, "code");

				m_keyMap.insert(std::make_pair(iKeyIndex, gameControl));
			}
		}
		SafeDelete(&pXml);
	}
}

// *****************************************************************************
unsigned int cGameControls::operator[](unsigned int i)
{
	return m_keyMap[i].m_uiKeyCode;
}
