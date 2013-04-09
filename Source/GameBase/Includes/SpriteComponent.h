// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef SpriteComponent_h__
#define SpriteComponent_h__

#include "BaseComponent.h"

namespace GameBase
{
	class cSpriteComponent
		: public cBaseComponent
	{
	public:
		cSpriteComponent();
		~cSpriteComponent();
		virtual void VInitialize();
		virtual void VCleanup();

	};
}
#endif // SpriteComponent_h__