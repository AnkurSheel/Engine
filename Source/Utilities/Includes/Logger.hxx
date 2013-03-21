// ***************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/02/16
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Logger_hxx__
#define Logger_hxx__

#include "UtilitiesDefines.h"

//#define TEST

//configure some basic precompilation defines
//0 - no debugging wanted
//1 - very basic debug output
//2 - comprehensive debug output
//3 - all output, and a transcript of all messages
#ifdef TEST
#define SYSTEM_DEBUG_LEVEL 3
#else
#ifdef _DEBUG
//Set the output level for 'DEBUG' builds
#define SYSTEM_DEBUG_LEVEL 2
#else
//Set the output level for 'RELEASE' builds
#define SYSTEM_DEBUG_LEVEL 1
#endif

#endif

#define Log_Write( linetype, linetext )  \
	if(ILogger::Instance()) \
	{ \
		ILogger::Instance()->VWriteLogEntry( \
      (linetype), \
      __FILE__, \
      __FUNCSIG__, \
      __LINE__, \
      (linetext) ); \
	} 

#if SYSTEM_DEBUG_LEVEL == 3
  //enable all macros
  #define Log_Write_L1( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L3( linetype, linetext ) Log_Write( linetype, linetext )
      
#elif SYSTEM_DEBUG_LEVEL == 2
  //enable levels 1..2 macros
  #define Log_Write_L1( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext ) Log_Write( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
      
#elif SYSTEM_DEBUG_LEVEL == 1
  //enable level 1 macros
  #define Log_Write_L1( linetype, linetext )  Log_Write( linetype, linetext )
  #define Log_Write_L2( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
      
#else
  //disable macros
  #define Log_Write_L1( linetype, linetext )
  #define Log_Write_L2( linetype, linetext )
  #define Log_Write_L3( linetype, linetext )
#endif

namespace Base
{
	class cString;
}

namespace Utilities
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Interface for Logging
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class ILogger
	{
	public:
		enum LogType
		{
			LT_UNKNOWN = -1,
			LT_DEBUG,
			LT_ERROR,
			LT_WARNING,
			LT_COMMENT,
			LT_EVENT,
			LT_GAME_MESSAGE,
			LT_TOTAL
		};

	public:
		virtual ~ILogger(){}
		////////////////////////////////////////////////////////////////////////
		/// Initializes the logger. XML Log file is always created.
		///
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual void VInitialize() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Sets the log options
		///
		/// @param[in] bShowConsole True if we want to log to a console window. 
		/// @param[in] bLogToText True if we want to log to a text file. 
		/// @param[in] bLogToXML True if we want to log to a XML file. 
		/// @param[in] uiPriorityLevel The minimum level that must be logged
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual void VSetLogOptions(const bool bShowConsole,
			const bool bLogToText, const bool bLogToXML,
			const unsigned int uiPriorityLevel) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Writes the log to the various outputs. This function should not be 
		/// used directly. Instead the macro should be used
		///
		/// @param[in] eLogEntryType The log Type
		/// @param[in] strSourceFile The FIle in which this log originated
		/// @param[in] strFunction The Function in which this log originated
		/// @param[in] iSourceLine The line number at which this log originated
		/// @param[in] strMessage The log message
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual void VWriteLogEntry(const LogType eLogEntryType,
			const Base::cString & strSourceFile, const Base::cString & strFunction,
			int iSourceLine, const Base::cString & strMessage) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Creates and returns a pointer to a singleton object of this interface
		///
		/// @return Returns a pointer to the singleton object
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static ILogger * Instance();
		////////////////////////////////////////////////////////////////////////
		/// Deletes the singleton object
		///
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API static void Destroy();
	};
}
#endif // Logger_h__