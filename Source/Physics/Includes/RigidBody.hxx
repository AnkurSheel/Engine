// *****************************************************************************
//  RigidBody version:  1.0   Ankur Sheel  date: 2013/05/23
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef RigidBody_hxx
#define RigidBody_hxx

#include "PhysicsDefines.h"

namespace Base
{
	class cVector3;
}

namespace Physics
{
	struct	stRigidBodyDef
	{
		float	m_Mass;
		float	m_LinearDamping;
		float	m_TopSpeed;
		bool	m_ApplyGravity;

		stRigidBodyDef()
			: m_Mass(1.0f)
			, m_LinearDamping(1.0f)
			, m_ApplyGravity(false)
			, m_TopSpeed(0.0f)
		{
		}
	};

	class IRigidBody
	{
	public:
		virtual ~IRigidBody() {}
		virtual void VInitialize(const stRigidBodyDef & def) = 0;
		virtual void VApplyForce(const Base::cVector3 & Direction, const float Newtons) = 0;
		static IRigidBody * Create();
	};
}
#endif //RigidBody_hxx