// *****************************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/01/04
//  ----------------------------------------------------------------------------
// 2011/01/04 : based on 
//	     		http://archive.gamedev.net/reference/programming/features/xmltech/default.asp 
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Logger_h__
#define Logger_h__

#include "Logger.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IXMLFileIO;
	class IFileOutput;
}

namespace Utilities
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Implementation of the Logger
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cLogger
		: public ILogger
		, public Base::cNonCopyable
	{
	public:
		~cLogger();

	private:
		cLogger();
		void VInitialize();
		void VSetLogOptions(const bool bShowConsole, const bool bLogToText,
			const bool bLogToXML, const unsigned int uiPriorityLevel);
		void VWriteLogEntry(LogType eLogEntryType,
			const Base::cString & strSourceFile, const Base::cString & strFunction,
			int iSourceLine, const Base::cString & strMessage);
		void CreateHeader();
		void Close();
		void LogTypeToString(const LogType eLogEntryType, Base::cString & str );
		void Log(const LogType eLogEntryType, const Base::cString & str);
		void SetConsoleTextColor(const LogType eLogEntryType);

	private:
		IFileOutput *	m_pTextLogFile;
		HANDLE			m_hStdOut;
		IXMLFileIO	*	m_pXmlLogFile;
		unsigned int	m_uiPriorityLevel;

		static int		m_iCurrentId;
		static cLogger * s_pLogger;

	private:
		friend static ILogger * ILogger::Instance();
		friend static void ILogger::Destroy();
	};
}
#endif // Logger_h__