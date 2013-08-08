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
		Base::cVector3 VGetRenderPosition() const { return m_RenderPosition; }
		IShape * GetCollisionShape() const { return m_pCollisionShape; }
		bool GetInitialized() const { return m_Initialized; }
		Base::cVector3 GetLinearVelocity() const { return m_LinearVelocity; }
		void SetLinearVelocity(const Base::cVector3 & velocity) { m_LinearVelocity = velocity; }
		float GetInverseMass() const { return m_InverseMass; }
		float GetRestitution() const { return m_MaterialData.restitution; }
		void OnCreated(shared_ptr<const stRigidBodyDef>);
		void IntegrateForces(const float timestep);
		void IntegrateVelocity(const float timestep);
		void ApplyImpulse(const Base::cVector3 & impulse);
		void ApplyPositionCorrection(const Base::cVector3 & correction);
		void Sync(const float alpha);
		void OnMoved();

	private:
		PHYSICS_API virtual void VInitialize(const Base::cVector3 & position);
		void VApplyForce(const Base::cVector3 & Direction, const float Newtons);
		void VUpdateCollisionShape(const Base::cVector3 & minBound, 
			const Base::cVector3 & maxBound);

	private:
		Base::cVector3	m_LinearVelocity;
		Base::cVector3	m_Position;
		Base::cVector3	m_PreviousPosition;
		Base::cVector3	m_RenderPosition;
		Base::cVector3	m_Force;
		IShape *		m_pCollisionShape;
		float			m_InverseMass;
		float			m_LinearDamping;
		float			m_TopSpeed;
		bool			m_ApplyGravity;
		bool			m_Initialized;
		stMaterialData	m_MaterialData;
	};
}
#endif //RigidBody_hxx