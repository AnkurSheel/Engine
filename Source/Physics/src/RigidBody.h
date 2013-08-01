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
	class IShape;
}

namespace Physics
{
	class cRigidBody
		: public IRigidBody
	{
	public:
		cRigidBody();
		~cRigidBody();
		cRigidBody(const cRigidBody & other);
		cRigidBody & operator =(const cRigidBody & other);
		void VSetPosition(const Base::cVector3 & Position);
		Base::cVector3 VGetPosition() const { return m_Position; }
		IShape * GetCollisionShape() const { return m_pCollisionShape; }
		bool GetInitialized() const { return m_Initialized; }
		Base::cVector3 GetLinearVelocity() const { return m_LinearVelocity; }
		float GetInverseMass() const { return m_InverseMass; }
		void OnCreated(shared_ptr<const stRigidBodyDef>);
		void IntegrateForces();
		void IntegrateVelocity(const float deltaTime);
		void ApplyImpulse(const Base::cVector3 & impulse);
		void ApplyPositionCorrection(const Base::cVector3 & correction);

	private:
		PHYSICS_API virtual void VInitialize(const Base::cVector3 & position);
		void VApplyForce(const Base::cVector3 & Direction, const float Newtons);
		void VUpdateBounds(const Base::cVector3 & minBound, 
			const Base::cVector3 & maxBound);

	private:
		Base::cVector3	m_LinearVelocity;
		Base::cVector3	m_Position;
		Base::cVector3	m_Force;
		IShape *		m_pCollisionShape;
		float			m_InverseMass;
		float			m_LinearDamping;
		float			m_TopSpeed;
		bool			m_ApplyGravity;
		bool			m_Initialized;
	};
}
#endif //RigidBody_hxx