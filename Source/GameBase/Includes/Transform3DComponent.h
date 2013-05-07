// *****************************************************************************
//  Transform3DComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef Transform3DComponent_h__
#define Transform3DComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "Vector3.h"

namespace GameBase
{
	class cTransform3DComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cTransform3DComponent();
		GAMEBASE_API ~cTransform3DComponent();
		void VInitialize();
		void VCleanup();

	public:
		Base::cVector3	m_vPosition;	///< The position of the game element.
		Base::cVector3	m_vRotation;	///< The rotation of the game element.
		Base::cVector3	m_vScale;		///< The scale of the game element.

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		Base::cString VGetName() const { return m_Name.GetString(); }

	private:
		static Base::cHashedString	m_Name;	///< The component name
	};
}
#endif // Transform3DComponent_h__
