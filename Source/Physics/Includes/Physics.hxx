// *****************************************************************************
//  Physics version:  1.0   Ankur Sheel  date: 2013/06/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Physics_hxx
#define Physics_hxx

#include "PhysicsDefines.h"

namespace Physics
{
	class IRigidBody;
	struct stRigidBodyDef;
}

namespace Physics
{
	struct	stPhysicsDef
	{
		float	m_Gravity;

		stPhysicsDef()
			: m_Gravity(0.0f)
		{
		}
	};

	class IPhysics
	{
	public:
		virtual ~IPhysics() {}
		virtual void VInitialize(const stPhysicsDef & def) = 0;
		virtual void VUpdate(const float DeltaTime) = 0;
		virtual void VAddRigidBody(const int ID, const stRigidBodyDef & def) = 0;
		virtual void VRemoveRigidBody(const int ID) = 0;
	};
}
#endif //Physics_hxx