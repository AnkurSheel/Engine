// *****************************************************************************
//  RigidBody version:  1.0   Ankur Sheel  date: 2013/05/23
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef RigidBody_h
#define RigidBody_h

#include "RigidBody.hxx"
#include "vector3.h"

namespace Physics
{
	class cRigidBody
		: public IRigidBody
	{
	public:
		cRigidBody();
		~cRigidBody();

	private:
		PHYSICS_API virtual void VInitialize(const stRigidBodyDef & def);

	private:
		float			m_InverseMass;
		Base::cVector3	m_LinearVelocity;
		Base::cVector3	m_TotalForce;
		float			m_LinearDamping;
		float			m_TopSpeed;
		bool			m_ApplyGravity;
	};
}
#endif //RigidBody_hxx