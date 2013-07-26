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
		void Update(const float DeltaTime);
		IShape * GetCollisionShape() const { return m_pCollisionShape; }
		void OnCreated(shared_ptr<const stRigidBodyDef>);
		bool GetInitialized() const { return m_Initialized; }

	private:
		PHYSICS_API virtual void VInitialize(const Base::cVector3 & position);
		void VApplyForce(const Base::cVector3 & Direction, const float Newtons);
		void ApplyCentralForce(const Base::cVector3 & Force);
		void VSetPosition(const Base::cVector3 & Position);
		void VUpdateBounds(const Base::cVector3 & minBound, 
			const Base::cVector3 & maxBound);
		Base::cVector3 VGetPosition() const { return m_Position; }

	private:
		Base::cVector3	m_LinearVelocity;
		Base::cVector3	m_Position;
		IShape *		m_pCollisionShape;
		float			m_InverseMass;
		float			m_LinearDamping;
		float			m_TopSpeed;
		bool			m_ApplyGravity;
		bool			m_Initialized;
	};
}
#endif //RigidBody_hxx