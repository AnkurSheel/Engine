//  *******************************************************************************************************************
//  UiControlFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef UiControlFactory_h__
#define UiControlFactory_h__

#include "GraphicEngineDefines.h"
#include "GenericObjectCreation.h"

namespace Graphics
{
	class IBaseControl;
}

namespace Graphics
{
	class cUiControlFactory
	{
	public:
		GRAPHIC_API cUiControlFactory();
		GRAPHIC_API ~cUiControlFactory();
		GRAPHIC_API void VRegisterUiControls();
		IBaseControl * CreateUiControl(const Base::cHashedString & Type);
		static cUiControlFactory * Instance() { return m_pInstance; }

	private:
		Base::GenericObjectFactory<IBaseControl, unsigned long>	m_RegisteredControls;
		GRAPHIC_API static cUiControlFactory *				m_pInstance;
	};
}
#endif // UiControlFactory_h__
