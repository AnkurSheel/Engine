#include "stdafx.h"
#include "BaseApp.h"
#include "MainWindow.hxx"
#include "Timer.hxx"
#include "HumanView.h"
#include "ParamLoaders.hxx"
#include "Optional.h"
#include "SystemChecker.hxx"
#include "EntityManager.hxx"
#include "MessageDispatchManager.hxx"
#include "ResourceManager.hxx"
#include "GraphicsClass.hxx"
#include "ProcessManager.hxx"
#include "GameDirectories.h"
#include "GameOptions.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;
using namespace Graphics;
using namespace std;

// *****************************************************************************
cBaseApp::cBaseApp(const cString & Name)
: m_pGameTimer(NULL)
, m_pHumanView(NULL)
, m_pParamLoader(NULL)
, m_pHighScoreTable(NULL)
, m_pGameControls(NULL)
, m_Quitting(false)
, m_pProcessManager(NULL)
{
	// make sure our memory leak checker is working
#if _DEBUG
	int * p = DEBUG_NEW int();
#endif

}

// *****************************************************************************
void cBaseApp::VOnInitialization(const HINSTANCE & hInstance, const int nCmdShow,
								 const cString & strOptionsFile)
{
	ILogger::Instance()->VInitialize();
	if(m_pParamLoader == NULL)
	{
		m_pParamLoader = IParamLoader::CreateParamLoader();
		m_pParamLoader->VLoadParametersFromFile(strOptionsFile);
	}

	m_Title = m_pParamLoader->VGetParameterValueAsString("-title", "Game");

	bool MultipleInstances = m_pParamLoader->VGetParameterValueAsBool("-multipleinstances", false);
	if (MultipleInstances)
	{
		if (!ISystemChecker::Instance()->VIsOnlyInstance(m_Title))
		{
			PostQuitMessage(0);
			m_Quitting = true;
			return;
		}
	}

	if(!ISystemChecker::Instance()->VCheckMemory(32, 64) 
		|| !ISystemChecker::Instance()->VCheckHardDiskSpace(6) 
		|| !ISystemChecker::Instance()->VCheckCPUSpeed(266))
	{
		PostQuitMessage(0);
		m_Quitting = true;
		return;
	}
	
	bool ShowConsoleLog = m_pParamLoader->VGetParameterValueAsBool("-showconsolelog", false);
	bool LogToText = m_pParamLoader->VGetParameterValueAsBool("-logtotext", true);
	bool LogToXML = m_pParamLoader->VGetParameterValueAsBool("-logtoxml", false);
	unsigned int PriorityLevel = m_pParamLoader->VGetParameterValueAsInt("-loglevel", 1);
	ILogger::Instance()->VSetLogOptions(ShowConsoleLog, LogToText, LogToXML, PriorityLevel);

	ISystemChecker::Destroy();

	// initialize resource manager
	cString AssetsPath = m_pParamLoader->VGetParameterValueAsString("-AssetsPath", "");
	if(!IResourceManager::GetInstance()->VInitialize(AssetsPath))
	{
		m_Quitting = true;
		return;
	}

	cGameDirectories::Initialize();
	cGameOptions::InitializeGameOptions(cGameDirectories::GameDirectories().strMediaDirectory + "PlayerOptions.xml");
#if _DEBUG
	cGameOptions::GameOptions().bFullScreen = m_pParamLoader->VGetParameterValueAsBool("-fullscreen", cGameOptions::GameOptions().bFullScreen);
	cGameOptions::GameOptions().iWidth = m_pParamLoader->VGetParameterValueAsInt("-WindowWidth", cGameOptions::GameOptions().iWidth);
	cGameOptions::GameOptions().iHeight = m_pParamLoader->VGetParameterValueAsInt("-WindowHeight", cGameOptions::GameOptions().iHeight);
#endif

	HWND hwnd = IMainWindow::GetInstance()->VOnInitialization(hInstance, nCmdShow, this);

	if(hwnd == NULL)
	{
		m_Quitting = true;
		return;
	}

	vector<int> vBGColor;
	m_pParamLoader->VGetParameterValueAsIntList("-BackGroundColor", vBGColor);
	cColor bgColor = cColor::BLACK;
	if(!vBGColor.empty() && vBGColor.size() == 4)
	{
		bgColor = cColor(vBGColor[0], vBGColor[1], vBGColor[2], vBGColor[3]);
	}
	bool bVSyncEnabled = m_pParamLoader->VGetParameterValueAsBool("-VSyncEnabled", false);
	float fScreenFar = m_pParamLoader->VGetParameterValueAsFloat("-ScreenFar", 1000.0f);
	float fScreenNear = m_pParamLoader->VGetParameterValueAsFloat("-ScreenNear", 0.1f);

	if(!IGraphicsClass::GetInstance()->VInitialize(hwnd, bgColor,
		cGameOptions::GameOptions().bFullScreen, bVSyncEnabled,
		cGameOptions::GameOptions().iWidth, 
		cGameOptions::GameOptions().iHeight, fScreenFar, fScreenNear))
	{
		m_Quitting = true;
		return;
	}

	m_pProcessManager = IProcessManager::CreateProcessManager();

	VCreateHumanView();
	m_pHumanView->VOnCreateDevice(this, hInstance, hwnd);
}

void cBaseApp::VCreateHumanView()
{
	m_pHumanView = DEBUG_NEW cHumanView();
}

// *****************************************************************************
// the message loop
// *****************************************************************************
void cBaseApp::VRun()
{
	MSG Msg ;

	m_pGameTimer = ITimer::CreateTimer();
	m_pGameTimer->VStartTimer();

	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE) ;
	// run till completed
	while (Msg.message!=WM_QUIT)
	{
		// is there a message to process?
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			// dispatch the message
			TranslateMessage(&Msg) ;
			DispatchMessage(&Msg) ;
		}
		else
		{
			//No message to process?
			// Then do your game stuff here
			VOnUpdate();
			VRender(m_pGameTimer->VGetRunningTicks(), m_pGameTimer->VGetDeltaTime());
		}
	}
}

void cBaseApp::VOnUpdate()
{
	if(m_Quitting)
	{
		return;
	}
	m_pGameTimer->VOnUpdate();
	IMessageDispatchManager::GetInstance()->VOnUpdate();

	if(m_pProcessManager)
	{
		m_pProcessManager->UpdateProcesses(m_pGameTimer->VGetRunningTicks());
	}

}

// *****************************************************************************
// Deletes the memory
// *****************************************************************************
void cBaseApp::VCleanup()
{
	SafeDelete(&m_pGameTimer);
	SafeDelete(&m_pParamLoader);
	SafeDelete(&m_pProcessManager);
	SafeDelete(&m_pHumanView);

	IEntityManager::Destroy();
	IMessageDispatchManager::Destroy();
	IGraphicsClass::Destroy();
	IResourceManager::Destroy();
	IMainWindow::Destroy();
	
	ILogger::Destroy();
}

// *****************************************************************************
float cBaseApp::GetRunningTime() const
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTime();

	return 0.f;
}

// *****************************************************************************
TICK cBaseApp::GetRunningTicks() const
{
	if(m_pGameTimer)
		return m_pGameTimer->VGetRunningTicks();

	return 0;
}

// *****************************************************************************
// Display the FPS
// *****************************************************************************
float cBaseApp::VGetFPS() const
{
	return m_pGameTimer->VGetFPS();
}

// *****************************************************************************
bool cBaseApp::VOnMsgProc( const Base::AppMsg & msg )
{
	return m_pHumanView->VOnMsgProc(msg);
}

// *****************************************************************************
// Display the Graphics
// *****************************************************************************
void cBaseApp::VRender(TICK tickCurrent, float fElapsedTime)
{
	m_pHumanView->VOnRender(tickCurrent, fElapsedTime);
}

// *****************************************************************************
cHumanView * const cBaseApp::VGetHumanView() const
{
	return m_pHumanView;
}

// *****************************************************************************
Utilities::IParamLoader * cBaseApp::VGetParamLoader() const
{
	return m_pParamLoader;
}

// *****************************************************************************
cGameControls * cBaseApp::GetGameControls() const
{
	return m_pGameControls;
}

// *****************************************************************************
IProcessManager * cBaseApp::VGetProcessManager() const
{
	return m_pProcessManager;
}
