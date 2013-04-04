// *****************************************************************************
//  RenderSystem version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef RenderSystem_h__
#define RenderSystem_h__
#include "Process.h"

namespace GameBase
{
	class cRenderSystem
		: public Utilities::cProcess
	{
	public:
		cRenderSystem();
		~cRenderSystem();
		void VInitialize();
		void VUpdate(const int iDeltaMilliSeconds);
	};
}
#endif // RenderSystem_h__
