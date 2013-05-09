// *****************************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "ResCache.h"
#include "ZipFile.hxx"
#include "Optional.h"
#include "FileInput.hxx"

using namespace Utilities;
using namespace Base;
	
// *****************************************************************************
cResCache::cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile)
: m_iCacheSize(iCacheSizeInMB * MEGABYTE)
, m_iTotalMemoryAllocated(0)
{
	m_pFile = const_cast<IResourceFile *>(pResFile);
}

// *****************************************************************************
cResCache::~cResCache()
{
	while(!m_lru.empty())
	{
		FreeOneResource();
	}
	SafeDelete(&m_pFile);
}

// *****************************************************************************
bool cResCache::Init()
{
	return m_pFile->Open();
}

// *****************************************************************************
shared_ptr<IResHandle> cResCache::GetHandle(IResource & r)
{
	shared_ptr<IResHandle> handle(Find(r));
	if(handle == NULL)
	{
		handle = Load(r);
	}
	else
	{
		Update(handle);
	}
	return handle;
}
		
// *****************************************************************************
void cResCache::Flush()
{
	while(m_lru.empty())
	{
		shared_ptr<IResHandle> handle = *(m_lru.begin());
		Free(handle);
		m_lru.pop_front();
	}
}

// *****************************************************************************
shared_ptr<IResHandle> cResCache::Find(const IResource & r)
{
	ResHandleMap::const_iterator itr = m_Resources.find(r.VGetFileName());
	if(itr == m_Resources.end())
	{
		Log_Write(ILogger::LT_COMMENT, 2, cString(100, "Could not find %s in cache", r.VGetFileName().GetData()));
		return shared_ptr<IResHandle>(); 
	}
	Log_Write(ILogger::LT_COMMENT, 3, cString(100, "Found %s in cache", r.VGetFileName().GetData()));

	return (*itr).second;
}

// *****************************************************************************
const void cResCache::Update(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_lru.push_front(handle);
}

// *****************************************************************************
shared_ptr<IResHandle> cResCache::Load(IResource & r)
{
	int iSize = m_pFile->GetResourceSize(r);
	if (iSize == 0)
	{
		Log_Write(ILogger::LT_ERROR, 1, "Could not find file " + r.VGetFileName() + " in zip file");
		return shared_ptr<IResHandle>();
	}
	char * pBuffer = Allocate(iSize);
	if(pBuffer == NULL)
	{
		return shared_ptr<IResHandle>();
	}

	shared_ptr<IResHandle> handle(r.VCreateHandle(pBuffer, iSize, this));

	handle->Load(m_pFile);

	m_lru.push_front(handle);
	m_Resources[r.VGetFileName()] = handle;

	return handle;
}

// *****************************************************************************
void cResCache::Free(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_Resources.erase(handle->GetResource()->VGetFileName());
}

// *****************************************************************************
bool cResCache::MakeRoom(unsigned int iSize)
{
	if(iSize > m_iCacheSize)
	{
		Log_Write(ILogger::LT_DEBUG, 3, cString(100, "File size %d greater than cache size %d",iSize, m_iCacheSize));
		return false;
	}

	while(iSize > (m_iCacheSize - m_iTotalMemoryAllocated))
	{
		Log_Write(ILogger::LT_DEBUG, 2, cString(100, "Cache needs to be freed to make space"));
		if(m_lru.empty())
		{
			return false;
		}
		 FreeOneResource();
	}
	return true;
}

// *****************************************************************************
char * cResCache::Allocate(unsigned int iSize)
{
	if(!MakeRoom(iSize))
	{
		return NULL;
	}
	char * pBuffer = DEBUG_NEW char[iSize];
	if(pBuffer)
	{	
		m_iTotalMemoryAllocated += iSize;
		Log_Write(ILogger::LT_DEBUG, 2, cString(300, "Allocating Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));
	}
	return pBuffer;
}

// *****************************************************************************
void cResCache::FreeOneResource()
{
	ResHandleList::const_iterator itr = m_lru.end();
	
	itr--;
	shared_ptr<IResHandle> handle = *itr;
	m_lru.pop_back();
	m_Resources.erase(handle->GetResource()->VGetFileName());
	Log_Write(ILogger::LT_DEBUG, 3, cString(100, "Removed file %s from cache", handle->GetResource()->VGetFileName().GetData()));
}

// *****************************************************************************
void cResCache::MemoryHasBeenFreed(unsigned int iSize)
{
	m_iTotalMemoryAllocated -= iSize;
	Log_Write(ILogger::LT_DEBUG, 2, cString(300, "Freeing Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));
}

// *****************************************************************************
IResCache * IResCache::CreateResourceCache(const int SizeInMB,
	const cString & FileName, const bool UseDevelopmentDirectory)
{
	IResourceFile * pResFile = NULL;
	if(UseDevelopmentDirectory)
	{
		pResFile = DEBUG_NEW cDevelopmentResourceZipFile(FileName);
	}
	else
	{
		pResFile = DEBUG_NEW cResourceZipFile(FileName);
	}

	cResCache * pResCache = DEBUG_NEW cResCache(SizeInMB, pResFile);
	return pResCache;
}

// *****************************************************************************
cResourceZipFile::cResourceZipFile(const Base::cString & resFileName) 
: m_pZipFile(NULL)
, m_strResFileName(resFileName) 
{ 
}

// *****************************************************************************
cResourceZipFile::~cResourceZipFile()
{
	SafeDelete(&m_pZipFile);
}

// *****************************************************************************
bool cResourceZipFile::Open()
{
	m_pZipFile = IZipFile::CreateZipFile();
	if(m_pZipFile)
	{
		return m_pZipFile->Init(m_strResFileName);
	}
	return false;
}

// *****************************************************************************
int cResourceZipFile::GetResourceSize(const IResource &r)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(*resNum);
	}
	return iSize;
}

// *****************************************************************************
void cResourceZipFile::GetResource(const IResource &r, char *buffer)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(*resNum);
		m_pZipFile->ReadFile(*resNum, buffer);
	}
}

// *****************************************************************************
cDevelopmentResourceZipFile::cDevelopmentResourceZipFile(const cString & resFileName) 
	: cResourceZipFile(resFileName)
{ 
	m_AssetsDir = resFileName;
}

// *****************************************************************************
cDevelopmentResourceZipFile::~cDevelopmentResourceZipFile()
{
}

// *****************************************************************************
bool cDevelopmentResourceZipFile::Open()
{
	ReadAssetsDirectory("*");
	return true;
}

// *****************************************************************************
int cDevelopmentResourceZipFile::GetResourceSize(const IResource &r)
{
	int Size = 0;

	tOptional<int> num = Find(r.VGetFileName().GetData());
	if (num.IsValid())
		Size = m_AssetFileInfo[*num].nFileSizeLow;
	return Size;
}

// *****************************************************************************
void cDevelopmentResourceZipFile::GetResource(const IResource &r, char *buffer)
{
	int Size = 0;
	tOptional<int> num = Find(r.VGetFileName().GetData());
	if (num.IsValid())
	{
		Size = m_AssetFileInfo[*num].nFileSizeLow;
		cString fullFileSpec = m_AssetsDir + r.VGetFileName(); 
		IFileInput * pFile = IFileInput::CreateInputFile();
		pFile->Open(fullFileSpec, std::ios::in | std::ios::binary);
		pFile->ReadAll(buffer);
		pFile->Close();
		SafeDelete(&pFile);
	}
}

// *****************************************************************************
bool cDevelopmentResourceZipFile::ReadAssetsDirectory(const cString & FileSpec)
{
	HANDLE fileHandle;
	WIN32_FIND_DATA findData;

	// get first file
	cString PathSpec = m_AssetsDir + FileSpec;
	fileHandle = FindFirstFile(PathSpec.GetData(), &findData);
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		// loop on all remeaining entries in dir
		while(FindNextFile( fileHandle,&findData))
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;

			cString fileName(findData.cFileName); 
			if( findData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY )
			{
				if (fileName == ".." || fileName == ".")
				{
					continue;
				}
				else
				{
					fileName = FileSpec.GetSubString(0, FileSpec.GetLength() - 1) + fileName + "\\*";
					ReadAssetsDirectory(fileName);
				}
			}
			else
			{
				fileName = FileSpec.GetSubString(0, FileSpec.GetLength() - 1) + fileName;
				cString lower = fileName.GetInLowerCase();
				m_DirectoryContentsMap[lower] = m_AssetFileInfo.size();
				m_AssetFileInfo.push_back(findData);
			} 
		}
	} 

	FindClose(fileHandle);
	return true;
}

// *****************************************************************************
tOptional<int> cDevelopmentResourceZipFile::Find(const cString & Name)
{
	tOptional<int> val;

	cString lowerCase = Name.GetInLowerCase();
	IZipFile::ZipContentsMap::const_iterator i = m_DirectoryContentsMap.find(lowerCase);
	if (i==m_DirectoryContentsMap.end())
	{
		val.clear();
	}
	else
	{
		val = i->second;
	}
	return val;
}
