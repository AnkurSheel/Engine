//  *******************************************************************************************************************
//  UiManager   version:  1.0   Ankur Sheel  date: 2014/02/20
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef UiManager_h__
#define UiManager_h__

#include "UiManager.hxx"

namespace Graphics
{
	class cUiControlFactory;
	class IBaseControl;
}

namespace Graphics
{
	class cUiManager
		: public IUiManager
		, public Base::cNonCopyable
	{
	public:
		~cUiManager();

	private:
		cUiManager();
		const shared_ptr<IBaseControl> VCreateUI(const Base::cString & FileName);

		void Initialize();

	private:
		static cUiManager *	s_pUiManager;
		shared_ptr<cUiControlFactory> m_pUiFactory;

	private:
		friend static IUiManager * IUiManager::GetInstance();
		friend static void IUiManager::Destroy();
	};
}

#endif // UiManager_hxx__