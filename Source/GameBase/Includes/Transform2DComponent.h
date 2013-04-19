// *****************************************************************************
//  Transform2DComponent version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Transform2DComponent_h__
#define Transform2DComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "Vector2.h"

namespace GameBase
{
	class cTransform2DComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cTransform2DComponent();
		GAMEBASE_API ~cTransform2DComponent();
		void VInitialize();
		void VCleanup();

	public:
		Base::cVector2<float>	m_vPosition;	///< The position of the game element.
		Base::cVector2<float>	m_vRotation;	///< The rotation of the game element.
		Base::cVector2<float>	m_vSize;		///< The size of the game element.
	};
}
#endif // Transform2DComponent_h__
