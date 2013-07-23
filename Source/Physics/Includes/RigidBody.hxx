// *****************************************************************************
//  RigidBody version:  1.0   Ankur Sheel  date: 2013/05/23
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef RigidBody_hxx
#define RigidBody_hxx

#include "PhysicsDefines.h"
#include "vector3.h"

namespace Physics
{
	struct	stRigidBodyDef
	{
		float				m_Mass;
		float				m_LinearDamping;
		float				m_TopSpeed;
		Base::cVector3		m_MinBound;
		Base::cVector3		m_MaxBound;
		Base::cHashedString	m_Shape; 
		bool				m_ApplyGravity;

		stRigidBodyDef()
			: m_Mass(1.0f)
			, m_LinearDamping(1.0f)
			, m_ApplyGravity(false)
			, m_TopSpeed(0.0f)
			, m_Shape("none")
		{
		}
	};

	class IRigidBody
	{
	public:
		virtual ~IRigidBody() {}
		virtual void VInitialize(shared_ptr<const stRigidBodyDef>) = 0;
		virtual void VApplyForce(const Base::cVector3 & Direction, const float Newtons) = 0;
		virtual void VSetPosition(const Base::cVector3 & Position) = 0;
		virtual Base::cVector3 VGetPosition() const = 0;
		static IRigidBody * Create();
	};
}
#endif //RigidBody_hxx