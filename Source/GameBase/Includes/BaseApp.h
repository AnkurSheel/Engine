// *****************************************************************************
//  BaseApp   version:  1.0   Ankur Sheel  date: 2011/10/19
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef BaseApp_h__
#define BaseApp_h__

#include "BaseApp.hxx"
#include "BaseEntity.h"

namespace Utilities
{
	class ITimer;
	class IParamLoader;
	class IProcessManager;
}

namespace GameBase
{
	class cHumanView;
	class cHighScoreTable;
	class cGameControls;
}

namespace GameBase
{
	class cBaseApp 
		: public IBaseApp
	{
	public:
		virtual ~cBaseApp(){}
		GAMEBASE_API virtual cHumanView * const VGetHumanView() const { return m_pHumanView; }
		GAMEBASE_API Utilities::IProcessManager * VGetProcessManager() const {return m_pProcessManager; }
		TICK GetRunningTicks() const;
		GAMEBASE_API float GetRunningTime() const;
		GAMEBASE_API cGameControls * GetGameControls() const { return m_pGameControls; }

	protected:
		GAMEBASE_API cBaseApp(const Base::cString & Name);
		GAMEBASE_API virtual void VOnInitialization(const HINSTANCE & hInstance,
			const int nCmdShow, const Base::cString & strOptionsFile);
		GAMEBASE_API virtual void VCreateHumanView();
		GAMEBASE_API virtual void VRun();
		GAMEBASE_API virtual void VOnUpdate();
		GAMEBASE_API virtual bool VOnMsgProc(const Base::AppMsg & msg);
		GAMEBASE_API virtual void VRender(TICK tickCurrent, float fElapsedTime);
		GAMEBASE_API virtual void VCleanup();

	private:
		GAMEBASE_API Utilities::IParamLoader * VGetParamLoader() const { return m_pParamLoader; }
		GAMEBASE_API float VGetFPS() const;
		Base::cString VGetName() const { return m_Title; }

	protected:
		Utilities::ITimer *				m_pGameTimer;
		cHumanView *					m_pHumanView;
		Utilities::IParamLoader *		m_pParamLoader;
		cHighScoreTable *				m_pHighScoreTable;
		cGameControls *					m_pGameControls;
		bool							m_Quitting;
		Utilities::IProcessManager *	m_pProcessManager;
		Base::cString					m_Title;
	};
}

#endif // BaseApp_h__