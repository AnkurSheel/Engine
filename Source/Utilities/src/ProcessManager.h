// ***************************************************************
//  ProcessManager   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ProcessManager_h__
#define ProcessManager_h__

#include "ProcessManager.hxx"

namespace Utilities
{
	class cProcess;
}

namespace Utilities
{
	class cProcessManager
		: public IProcessManager
	{
	public:
		~cProcessManager();

	private:
		void VAttachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcess(shared_ptr<cProcess> pProcess);
		void VDetachProcesses(const Base::cString & strType);
		void VSetProcessesActive(const Base::cString & strType, const bool bActive);
		void VGetProcesses(const Base::cString & strType, ProcessList & pProcessList);
		void VUpdateProcesses(const float deltaTime);
		bool VHasProcesses() const { return !(m_pProcessList.empty()); }

	protected:
		ProcessList m_pProcessList;
	};
}
#endif // ProcessManager_h__