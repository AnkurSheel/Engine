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

namespace Physics
{
	class IRigidBody;
}

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
		GAMEBASE_API void ApplyForce(const Base::cVector3 & Direction);
		GAMEBASE_API void Update();

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		Physics::IRigidBody *		m_pRigidBody;
		float						m_Force;
		bool						m_ApplyForce;
		Base::cVector3				m_Direction;
		static Base::cHashedString	m_Name;	///< The component name
	};
}
#endif // PhysicsComponent_h__
