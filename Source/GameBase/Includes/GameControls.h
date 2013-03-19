// *****************************************************************************
//  GameControls   version:  1.0   Ankur Sheel  date: 2013/03/19
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef GameControls_h__
#define GameControls_h__

#include "GameBaseDefines.h"

namespace GameBase
{
	struct stGameControl
	{
		Base::cString	m_strDisplayName;
		unsigned int	m_uiKeyCode;

		stGameControl()
			: m_uiKeyCode(0)
		{
		}

		stGameControl(const Base::cString & strDisplayName,
			const unsigned int uiKeyCode)
			: m_strDisplayName(strDisplayName)
			, m_uiKeyCode(uiKeyCode)
		{
		}
	};

	class cGameControls
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cGameControls(const Base::cString & strPath);
		GAMEBASE_API virtual ~cGameControls();
		virtual void VSetDefaults() = 0;
		unsigned int operator[](const int i);
		void Initialize();

	protected:
		typedef std::unordered_map<unsigned int, stGameControl> KeyMapping;

		KeyMapping	m_keyMap;
		void SetKey(const int iKeyIndex, const unsigned int uiKey);
		Base::cString GetKeyName(const unsigned int uiKey);
		void Save();
		void Load();

	private:
		Base::cString	m_strKeysFile;
	};
}
#endif