// *****************************************************************************
//  SystemChecker   version:  1.0   Ankur Sheel  date: 2013/04/24
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef SystemChecker_hxx__
#define SystemChecker_hxx__

#include "UtilitiesDefines.h"

namespace Utilities
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Interface to check System resources
	///
	///////////////////////////////////////////////////////////////////////////
	class ISystemChecker
	{
	public:
		UTILITIES_API virtual ~ISystemChecker(){}
		////////////////////////////////////////////////////////////////////////
		/// Checks if this is the only instance of the game that is running
		///
		/// @param[in] gameTitle The title of the game
		/// @return True if this is the only instance. False if the game
		/// is already running
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual bool VIsOnlyInstance(const Base::cString & gameTitle) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Checks if there is enough hard disk space available
		///
		/// @param[in] diskSpaceNeeded The hard disk space needed (in MB)
		/// @return True if there is enough hard disk space. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual bool VCheckHardDiskSpace(const unsigned int diskSpaceNeeded) = 0; 
		////////////////////////////////////////////////////////////////////////
		/// Checks if there is enough hard System Ram and Virtual Ram
		///
		/// @param[in] physicalRAMNeeded The system RAM needed (in MB)
		/// @param[in] virtualRAMNeeded The virtual RAM needed (in MB)
		/// @return True if there is enough System RAM and VRAM. False otherwise
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual bool VCheckMemory( const unsigned int physicalRAMNeeded,
			const unsigned int virtualRAMNeeded) = 0; 
		////////////////////////////////////////////////////////////////////////
		/// Checks if the machine runs on a minimum speed
		///
		/// @param[in] minSpeedReq The minimum system speed need (in Mhz)
		/// @return True if the system is faster than the minimum required speed.
		/// False otherwise,
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual bool VCheckCPUSpeed(const unsigned int minSpeedNeeded) = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the total system RAM (in MB) 
		///
		/// @return The total system RAM (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetTotalPhysicalMemory() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the available system RAM (in MB) 
		///
		/// @return The available system RAM (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetAvailablePhysicalMemory() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the total virtual RAM (in MB) 
		///
		/// @return The total virtual RAM (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetTotalVirtualMemory() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the available virtual RAM (in MB) 
		///
		/// @return The available virtual RAM (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetAvailableVirtualMemory() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the total hard disk space (in MB) 
		///
		/// @return The total hard disk space (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetTotalHardDiskSpace() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the available hard disk space (in MB) 
		///
		/// @return The available hard disk space (in MB) 
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetAvailableHardDiskSpace() const = 0;
		////////////////////////////////////////////////////////////////////////
		/// Gets the CPU speed (in Mhz)
		///
		/// @return The CPU speed (in Mhz)
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual unsigned int VGetCPUSpeed() const = 0;
		UTILITIES_API static void Destroy();
		UTILITIES_API static ISystemChecker * Instance();
	};
}
#endif // Checks_h__
