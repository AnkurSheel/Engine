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

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	class cTransform2DComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cTransform2DComponent();
		GAMEBASE_API ~cTransform2DComponent();
		GAMEBASE_API void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		GAMEBASE_API void VCleanup();
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }

	public:
		Base::cVector2	m_Position;	///< The position of the game element.
		Base::cVector2	m_Rotation;	///< The rotation of the game element.
		Base::cVector2	m_Size;		///< The size of the game element.
		Base::cVector2	m_LookAt;
	
	private:
		GAMEBASE_API static Base::cHashedString	m_Name;	///< The component name
	
	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	};
}
#endif // Transform2DComponent_h__
