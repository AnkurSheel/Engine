// ***************************************************************
//  FileInput   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include "stdafx.h"
#include "FileInput.h"
#include <sys/stat.h>
#include <errno.h>

using namespace Utilities;
using namespace Base;

cFileInput::cFileInput()
: m_iFileSize(0)
{
}

cFileInput::~cFileInput()
{
	Close();
}

bool cFileInput::Open(const cString & strFileName, const std::ios_base::openmode mode)
{
	if(m_inputFile.is_open())
		Close();

	m_strFileName = strFileName;
	m_inputFile.open(m_strFileName.GetData(), mode);

	if(!m_inputFile)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not open file " + m_strFileName + " : " + strerror(errno));
		return false;
	}
	Log_Write(ILogger::LT_COMMENT, 3, "Opened file: " + m_strFileName);
	m_inputFile.seekg(0, std::ios::end);
	m_iFileSize = static_cast<unsigned long>(m_inputFile.tellg());
	m_inputFile.seekg(0, std::ios::beg);
	Log_Write(ILogger::LT_DEBUG, 3, "Size of File " + m_strFileName + cString(20, " : %d bytes", m_iFileSize));
	return true;
}

bool cFileInput::Close()
{
	if(m_inputFile.is_open())
	{
		m_inputFile.close();
		return true;
	}
	return false;
}

void cFileInput::ReadAll(const char * pBuffer)
{
	if(!m_inputFile)
	{
		Log_Write(ILogger::LT_ERROR, 1, "File not found : " + m_strFileName);
		return;
	}
	Read(pBuffer, m_iFileSize);
}

void cFileInput::Read(const char * pBuffer, unsigned long ulSize)
{
	if(!m_inputFile)
	{
		Log_Write(ILogger::LT_ERROR, 1, "File not found : " + m_strFileName);
		return;
	}

	SafeDeleteArray(&pBuffer);
	pBuffer = DEBUG_NEW char[ulSize];
	m_inputFile.read((char *)pBuffer, ulSize);
	if(m_inputFile.bad() || (m_inputFile.fail() && !m_inputFile.eof()))
	{
		Log_Write(ILogger::LT_ERROR, 1, "Error in reading file: " + m_strFileName);
		SafeDeleteArray(&pBuffer);
	}
}

Base::cString cFileInput::ReadLine()
{
	std::string str;
	std::getline(m_inputFile, str);
	m_strBuffer = str;
	return m_strBuffer;
}

IFileInput * IFileInput::CreateInputFile()
{
	IFileInput * pFile = DEBUG_NEW cFileInput();
	return pFile;
}

// ***************************************************************
unsigned long Utilities::cFileInput::VGetFileSize() const
{
	return m_iFileSize;
}
