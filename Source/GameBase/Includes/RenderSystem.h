// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef RenderSystem_h__
#define RenderSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class cRenderSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cRenderSystem();
		GAMEBASE_API ~cRenderSystem();
		void VUpdate(const float DeltaTime);
		GAMEBASE_API void Render(const Graphics::ICamera * const pCamera);
	};
}
#endif // RenderSystem_h__
