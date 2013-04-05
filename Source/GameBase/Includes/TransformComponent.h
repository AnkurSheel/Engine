// *****************************************************************************
//  TransformComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef TransformComponent_h__
#define TransformComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "Vector3.h"

namespace GameBase
{
	class cTransformComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cTransformComponent();
		GAMEBASE_API ~cTransformComponent();
		void VInitialize();
		void VCleanup();

	public:
		Base::cVector3	m_vPosition;	///< The position of the game element.
		Base::cVector3	m_vRotation;	///< The rotation of the game element.
		Base::cVector3	m_vScale;		///< The scale of the game element.
	};
}
#endif // TransformComponent_h__