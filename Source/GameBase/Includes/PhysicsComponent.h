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
	struct stRigidBodyDef;
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
		void VOnAttached(IBaseEntity * const pOwner);
		GAMEBASE_API void VCleanup();
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		GAMEBASE_API void Initialize(const Base::cVector3 & position,
			const Base::cVector3 & rotation);
		bool GetInitialized() const { return m_Initialized; }
		Base::cVector3 GetPosition() const;
		GAMEBASE_API void ApplyForce(const Base::cVector3 & Direction);
		GAMEBASE_API void Update();
		void OnSizeUpdated();

	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		void GetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBound);

	private:
		Physics::IRigidBody *				m_pRigidBody;
		shared_ptr<Physics::stRigidBodyDef>	m_pDef;
		Base::cVector3						m_Direction;
		float								m_Force;
		bool								m_Initialized;
		bool								m_ApplyForce;
		static Base::cHashedString			m_Name;	///< The component name
	};
}
#endif // PhysicsComponent_h__
