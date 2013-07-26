// *****************************************************************************
//  TransformComponent version:  1.0   Ankur Sheel  date: 2013/04/10
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef TransformComponent_h__
#define TransformComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "Vector3.h"

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	class cTransformComponent
		: public cBaseComponent
	{
	public:
		cTransformComponent();
		~cTransformComponent();
		void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		void VCleanup();
		static Base::cHashedString	GetName()  {return m_Name; }
		Base::cVector3 GetPosition() const { return m_Position; }
		GAMEBASE_API void SetPosition(const Base::cVector3 & position);

	public:
		Base::cVector3	m_Rotation;	///< The rotation of the game element.
		Base::cVector3	m_Size;		///< The size of the game element.
		Base::cVector3	m_LookAt;
	
	private:
		GAMEBASE_API static Base::cHashedString	m_Name;	///< The component name
		Base::cVector3	m_Position;	///< The position of the game element.

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
	};
}
#endif // TransformComponent_h__
