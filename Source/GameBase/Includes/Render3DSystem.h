// *****************************************************************************
//  Render3DSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Render3DSystem_h__
#define Render3DSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class cRender3DSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cRender3DSystem();
		GAMEBASE_API ~cRender3DSystem();
		void VUpdate(const int iDeltaMilliSeconds);
		GAMEBASE_API void Render(const Graphics::ICamera * const pCamera);
	};
}
#endif // Render3DSystem_h__
