// *****************************************************************************
//  InputSystem version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef InputSystem_h__
#define InputSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class cInputSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cInputSystem();
		GAMEBASE_API ~cInputSystem();
		void VUpdate(const float deltaTime);
	};
}
#endif // InputSystem_h__
