// *****************************************************************************
//  Physics version:  1.0   Ankur Sheel  date: 2013/06/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Physics_h
#define Physics_h

#include "Physics.hxx"

namespace Physics
{
	class cPhysics
		: public IPhysics
	{
	public:
		cPhysics();
		~cPhysics();

	private:
		void VInitialize(const stPhysicsDef & def);
		void VUpdate(const float DeltaTime);
		IRigidBody * const VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef);
		void VRemoveRigidBody(const int ID);
		IRigidBody* FindRigidBody(const int ID) const;
	
	private:
		typedef std::map<int, IRigidBody * const > RigidBodyMap;
	
		float				m_Gravity;
		RigidBodyMap		m_RigidBodyMap;
		static IPhysics * s_pPhysics;	/*!< static object of this class */

	private:
		friend static IPhysics * IPhysics::GetInstance();
		friend static void IPhysics::Destroy();
	};
}
#endif //Physics_hxx