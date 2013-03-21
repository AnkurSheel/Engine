// *****************************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  ----------------------------------------------------------------------------
//
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Logger.h"
#include <time.h>
#include "XMLFileIO.hxx"
#include "Checks.hxx"
#include "FileOutput.hxx"

using namespace Utilities;
using namespace Base;
using namespace std;

int cLogger::m_iCurrentId = 1;
cLogger * Utilities::cLogger::s_pLogger = NULL;

// *****************************************************************************
cLogger::cLogger()
: m_pTextLogFile(NULL)
, m_hStdOut(NULL) 
, m_pXmlLogFile(NULL)
, m_uiPriorityLevel(1)
{
}

// *****************************************************************************
cLogger::~cLogger()
{
	Close();
	SafeDelete(&m_pXmlLogFile);
}

// *****************************************************************************
void cLogger::VInitialize()
{
	m_pTextLogFile = IFileOutput::CreateOutputFile();
	if(!(m_pTextLogFile->Open("log.txt", ios_base::out)))
	{
		SafeDelete(&m_pTextLogFile);
	}
}

// *****************************************************************************
void cLogger::VSetLogOptions(const bool bShowConsole, const bool bLogToText,
	const bool bLogToXML, const unsigned int uiLevel)
{
	m_uiPriorityLevel = uiLevel;

	if(bShowConsole)
	{
		m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if(m_hStdOut == NULL && AllocConsole() != 0)
		{
			SetConsoleTitle("Logger");
			m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			FILE *fp;
			freopen_s(&fp, "CONOUT$", "w", stdout);
		}
	}

	if(!bLogToText && m_pTextLogFile)
	{
		SafeDelete(&m_pTextLogFile);
	}

	if(bLogToXML)
	{
		m_pXmlLogFile = IXMLFileIO::CreateXMLFile();
		m_pXmlLogFile->VInitializeForSave("RunTimeLog", "BasicXSLT.xsl");
		m_pXmlLogFile->VAddElement("RunTimeLog", "LogHeader", "", "");
		m_pXmlLogFile->VAddElement("RunTimeLog", "LogEvents", "", "");
		CreateHeader();
	}
}

// *****************************************************************************
void cLogger::CreateHeader()
{
	m_pXmlLogFile->VAddElement("LogHeader", "OutputLevel", "", cString(20, "Level %d", m_uiPriorityLevel));
	m_pXmlLogFile->VAddElement("LogHeader", "OutputLevel", "", cString(50, "%d", m_uiPriorityLevel));
	m_pXmlLogFile->VAddElement("LogHeader", "Session", "", "");
	m_pXmlLogFile->VAddElement("Session", "Configuration", "", "");
	m_pXmlLogFile->VAddElement("Configuration", "Memory", "", "");
	m_pXmlLogFile->VAddElement("Memory", "AvailablePhysical", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailablePhysicalMemory()));

	m_pXmlLogFile->VAddElement("Memory", "TotalPhysical", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalPhysicalMemory()));

	m_pXmlLogFile->VAddElement("Memory", "AvailableVirtual", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailableVirtualMemory()));

	m_pXmlLogFile->VAddElement("Memory", "TotalVirtual", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalVirtualMemory()));

	m_pXmlLogFile->VAddElement("Memory", "AvailableHardDiskSpace", "", cString(30, "%d", IResourceChecker::GetInstance()->GetAvailableHardDiskSpace()));

	m_pXmlLogFile->VAddElement("Memory", "TotalHardDiskSpace", "", cString(30, "%d", IResourceChecker::GetInstance()->GetTotalHardDiskSpace()));

	m_pXmlLogFile->VAddElement("Configuration", "Processor", "", "");
	m_pXmlLogFile->VAddElement("Processor", "ClockSpeed", "", cString(30, "%d", IResourceChecker::GetInstance()->GetCPUSpeed()));

	m_pXmlLogFile->VAddElement("Processor", "Family", "", IResourceChecker::GetInstance()->GetCPUBrand());

	m_pXmlLogFile->VAddElement("Session", "Started", "", "");

	time_t currentTime;
	time(&currentTime);
	m_pXmlLogFile->VAddElement("Started", "Time", "", cString::TimeToString(currentTime));

	m_pXmlLogFile->VAddElement("Configuration", "Environment", "", IResourceChecker::GetInstance()->GetOSVersion());
}

// *****************************************************************************
void cLogger::Log(const LogType eLogEntryType, const Base::cString & str)
{
	time_t currentTime;
	time(&currentTime);
	cString strTime = cString::TimeToString(currentTime);

	if(m_hStdOut)
	{
		SetConsoleTextColor(eLogEntryType);
		cout << strTime.GetData() << str << "\n";
	}

	if (m_pTextLogFile)
	{
		m_pTextLogFile->WriteLine(strTime + str + "\n");
		m_pTextLogFile->Flush();
	}
}

// *****************************************************************************
void cLogger::Close()
{
	m_pXmlLogFile->VSave("log.xml");
	if (m_pTextLogFile)
	{
		m_pTextLogFile->Close();
	}
}

// *****************************************************************************
void cLogger::VWriteLogEntry(const LogType eLogEntryType,
	const unsigned int uiPriorityLevel, const Base::cString & strSourceFile,
	const Base::cString & strFunction, const int iSourceLine,
	const Base::cString & strMessage)
{
	if(uiPriorityLevel > m_uiPriorityLevel)
		return;

	Log(eLogEntryType, strMessage);
	if(!m_pXmlLogFile)
		return;

	cString strEvent = m_pXmlLogFile->VAddElement("LogEvents", "LogEvent", cString(20, "%d", m_iCurrentId), "");

	cString str;
	LogTypeToString(eLogEntryType, str);
	m_pXmlLogFile->VAddElement(strEvent, "Type", "", str);

	time_t currentTime;
	time(&currentTime );

	m_pXmlLogFile->VAddElement(strEvent, "TimeIndex", "", cString::TimeToString(currentTime));

	m_pXmlLogFile->VAddElement(strEvent, "File", "", strSourceFile);
	m_pXmlLogFile->VAddElement(strEvent, "Function", "", strFunction);

	m_pXmlLogFile->VAddElement(strEvent, "LineNumber", "", cString(20, "%d", iSourceLine));
	m_pXmlLogFile->VAddElement(strEvent, "Message", "", strMessage);
	m_iCurrentId++;
}

// *****************************************************************************
void cLogger::SetConsoleTextColor(const LogType eLogEntryType)
{
	switch(eLogEntryType)
	{
	case LT_DEBUG: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		break;
	case LT_ERROR:
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED|FOREGROUND_INTENSITY);
		break;
	case LT_WARNING: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_COMMENT: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_EVENT: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	case LT_GAME_MESSAGE: 
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_INTENSITY);
		break;
	case LT_UNKNOWN:
	default:
		//set color to white
		SetConsoleTextAttribute(m_hStdOut, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		break;
	}
}

// *****************************************************************************
void cLogger::LogTypeToString(LogType eLogEntryType, cString & str)
{
	switch(eLogEntryType)
	{
	case LT_DEBUG: 
		str = "Debug";
		break;
	case LT_ERROR:
		str = "Error";
		break;
	case LT_WARNING: 
		str = "Warning";
		break;
	case LT_COMMENT: 
		str = "Comment";
		break;
	case LT_EVENT: 
		str = "Event";
		break;
	case LT_GAME_MESSAGE: 
		str = "Game Message";
		break;
	case LT_UNKNOWN:
	default:
		str = "UNKNOWN";
		break;
	}
}

// *****************************************************************************
ILogger * ILogger::Instance()
{
	if(cLogger::s_pLogger == NULL)
		cLogger::s_pLogger = DEBUG_NEW cLogger();
	return cLogger::s_pLogger;

}

// *****************************************************************************
void ILogger::Destroy()
{
	SafeDelete(&cLogger::s_pLogger);
}