// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FileInput_hxx__
#define FileInput_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IFileInput
	{
	public:
		UTILITIES_API virtual ~IFileInput(){}
		UTILITIES_API virtual bool Open(const Base::cString & strFileName, const std::ios_base::openmode mode) = 0;
		UTILITIES_API virtual bool Close() = 0;
		UTILITIES_API virtual void ReadAll(const char * pBuffer) = 0;
		UTILITIES_API virtual void Read(const char * pBuffer, unsigned long Size) = 0;
		UTILITIES_API virtual Base::cString ReadLine() = 0;
		UTILITIES_API virtual bool IsEOF() = 0;
		UTILITIES_API virtual unsigned long VGetFileSize() const = 0;
		UTILITIES_API static  IFileInput * CreateInputFile();
	};
}
#endif // FileInput_h__