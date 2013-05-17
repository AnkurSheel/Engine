// *****************************************************************************
//  Render2DSystem version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Render2DSystem_h__
#define Render2DSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class cRender2DSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cRender2DSystem();
		GAMEBASE_API ~cRender2DSystem();
		void VUpdate(const float DeltaTime);
		GAMEBASE_API void Render(const Graphics::ICamera * const pCamera);
	};
}
#endif // Render2DSystem_h__
