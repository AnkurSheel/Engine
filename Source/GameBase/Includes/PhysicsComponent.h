// *****************************************************************************
//  PhysicsComponent version:  1.0   Ankur Sheel  date: 2013/05/17
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef PhysicsComponent_h__
#define PhysicsComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "vector3.h"

namespace GameBase
{
	class cPhysicsComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cPhysicsComponent();
		GAMEBASE_API ~cPhysicsComponent();
		GAMEBASE_API void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		GAMEBASE_API void VCleanup();
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		void Update();

	public:
		bool	m_ApplyGravity;
		float	m_TopSpeed;
		float	m_Acceleration;
		Base::cVector3 m_CurrentVelocity;
		Base::cVector3 m_CurrentAcceleration;
		float	m_DragFactor;

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		static Base::cHashedString	m_Name;	///< The component name
	};
}
#endif // PhysicsComponent_h__
