// *****************************************************************************
//  Checks   version:  1.0   Ankur Sheel  date: 2013/04/24
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Checks_hxx__
#define Checks_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	class IResourceChecker
	{
	public:
		UTILITIES_API virtual ~IResourceChecker(){}
		UTILITIES_API virtual bool VIsOnlyInstance(const Base::cString &  gameTitle) = 0;
		UTILITIES_API virtual bool VCheckMemory( const unsigned int physicalRAMNeeded,
			const unsigned int virtualRAMNeeded) = 0; 
		UTILITIES_API virtual bool CheckHardDisk(const unsigned int diskSpaceNeeded) = 0; 
		UTILITIES_API virtual bool CheckCPUSpeedinMhz(const unsigned int uMinSpeedReq) = 0;
		UTILITIES_API virtual unsigned int GetTotalPhysicalMemory() const = 0;
		UTILITIES_API virtual unsigned int GetTotalVirtualMemory() const = 0;
		UTILITIES_API virtual unsigned int GetAvailablePhysicalMemory() const = 0;
		UTILITIES_API virtual unsigned int GetAvailableVirtualMemory() const = 0;
		UTILITIES_API virtual unsigned int GetTotalHardDiskSpace() const = 0;
		UTILITIES_API virtual unsigned int GetAvailableHardDiskSpace() const = 0;
		UTILITIES_API virtual unsigned int GetCPUSpeed() const = 0;
		UTILITIES_API virtual Base::cString GetCPUBrand() = 0;
		UTILITIES_API virtual Base::cString GetOSVersion() = 0;
		UTILITIES_API static void Destroy();
		UTILITIES_API static IResourceChecker * GetInstance();
	};
}
#endif // Checks_h__
