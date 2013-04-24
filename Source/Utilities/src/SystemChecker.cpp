#include "stdafx.h"
#include "SystemChecker.h"
#include <direct.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include <intrin.h>

using namespace Base;
using namespace Utilities;

cSystemChecker * cSystemChecker::m_pResourceChecker = NULL;

// *****************************************************************************
cSystemChecker::cSystemChecker()
: m_TotalPhysicalMemory(0)
, m_AvailablePhysicalMemory(0)
, m_TotalVirtualMemory(0)
, m_AvailableVirtualMemory(0)
, m_AvailableHardDiskSpace(0)
, m_TotalHardDiskSpace(0)
, m_CPUSpeed(0)
, m_Initialized(false)
{
}

// *****************************************************************************
cSystemChecker::~cSystemChecker()
{
}

// *****************************************************************************
bool cSystemChecker::VIsOnlyInstance(const cString & gameTitle) 
{ 
	// Find the window. If active, set and return false 
	// Only one game instance may have this mutex at a time... 
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle.GetData()); 
	
	if (GetLastError() != ERROR_SUCCESS) 
	{ 
		HWND hWnd = FindWindow(NULL, gameTitle.GetData()); 
		if (hWnd) 
		{ 
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL); 
			SetFocus(hWnd); 
			SetForegroundWindow(hWnd); 
			SetActiveWindow(hWnd);
			return false; 
		} 
	} 
	return true; 
}

// *****************************************************************************
bool cSystemChecker::VCheckHardDiskSpace(const unsigned int diskSpaceNeeded) 
{ 
	if (m_AvailableHardDiskSpace < diskSpaceNeeded) 
	{ 
		Log_Write(ILogger::LT_ERROR, 1, cString(100, "Not Enough HardDisk Space - Required : %ld, Available %ld \n", diskSpaceNeeded, m_AvailableHardDiskSpace));
		return false; 
	} 
	return true;
}

// *****************************************************************************
bool cSystemChecker::VCheckMemory(const unsigned int physicalRAMNeeded,
	const unsigned int virtualRAMNeeded) 
{
	if (m_AvailablePhysicalMemory < physicalRAMNeeded)
	{ 
		Log_Write(ILogger::LT_ERROR, 1, cString(100, "Not Enough Physical Memory - Required : %ld, Available %ld \n", physicalRAMNeeded, m_AvailablePhysicalMemory));
		return false; 
	} 
	// Check for enough free memory. 
	if (m_AvailableVirtualMemory < virtualRAMNeeded) 
	{ 
		Log_Write(ILogger::LT_ERROR, 1, cString(100, "Not Enough Virtual Memory - Required : %ld, Available %ld \n", virtualRAMNeeded, m_AvailableVirtualMemory));
		return false; 
	} 
	char * buff = DEBUG_NEW char[virtualRAMNeeded]; 
	if (buff) 
	{
		SafeDeleteArray(&buff);
	}
	else 
	{ 
		Log_Write(ILogger::LT_ERROR, 1, "System Lied: Not Enough Virtual Memory");
		return false; 
	} 
	return true;
}

// *****************************************************************************
bool cSystemChecker::VCheckCPUSpeed(const unsigned int minSpeedNeeded)
{ 
	if(m_CPUSpeed < minSpeedNeeded)
	{
		Log_Write(ILogger::LT_ERROR, 1, cString( 100, "CPU is too slow - Required speed: %ld, Actual Speed %ld \n", minSpeedNeeded, m_CPUSpeed));
		return false;
	}
	return true;
}

// *****************************************************************************
bool cSystemChecker::Initialize()
{
	if(!m_Initialized)
	{
		m_Initialized = true;
		CalculateHardDiskSpace();
		CalculateRAM();
		CalculateCPUSpeed();
	}
	return m_Initialized;
}

// *****************************************************************************
void cSystemChecker::CalculateHardDiskSpace() 
{ 
	const int drive = _getdrive(); 
	struct _diskfree_t diskfree; 
	_getdiskfree(drive, &diskfree); 

	m_TotalHardDiskSpace = diskfree.total_clusters / MEGABYTE * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
	m_AvailableHardDiskSpace = diskfree.avail_clusters / MEGABYTE * diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
}

// *****************************************************************************
void cSystemChecker::CalculateRAM() 
{
	MEMORYSTATUSEX status; 
	
	GlobalMemoryStatusEx(&status); 

	m_TotalPhysicalMemory = static_cast<unsigned int>(status.ullTotalPhys / MEGABYTE);
	m_AvailablePhysicalMemory= static_cast<unsigned int>(status.ullAvailPhys / MEGABYTE);
	m_AvailableVirtualMemory = static_cast<unsigned int>(status.ullAvailVirtual / MEGABYTE);
	m_TotalVirtualMemory= static_cast<unsigned int>(status.ullTotalVirtual / MEGABYTE);
}

// *****************************************************************************
void cSystemChecker::CalculateCPUSpeed()
{ 
	unsigned long bufSize = sizeof(unsigned long);
	unsigned long type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden: 
	long error = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0, KEY_READ, &hKey);
	if(error == ERROR_SUCCESS)
	{
		unsigned long speed;
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE) &speed, &bufSize);
		m_CPUSpeed = static_cast<unsigned int>(speed);
	}
}

// *****************************************************************************
ISystemChecker * ISystemChecker::Instance()
{
	if(cSystemChecker::m_pResourceChecker == NULL)
	{
		cSystemChecker::m_pResourceChecker = DEBUG_NEW cSystemChecker();
		cSystemChecker::m_pResourceChecker->Initialize();
	}
	return cSystemChecker::m_pResourceChecker;
}

// ***************************************************************
void ISystemChecker::Destroy()
{
	SafeDelete(&cSystemChecker::m_pResourceChecker);
}
