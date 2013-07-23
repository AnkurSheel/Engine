// *****************************************************************************
//  CollisionInfo version:  1.0   Ankur Sheel  date: 2013/06/23
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef CollisionInfo_h
#define CollisionInfo_h

#include "vector3.h"

namespace Physics
{
	class cRigidBody;
}

namespace Physics
{
	class cCollisionInfo
		: public Base::cNonCopyable
	{
	public:
		cCollisionInfo(cRigidBody * pBodyA , cRigidBody * pBodyB);
		~cCollisionInfo();
		void Solve();

	public:
		cRigidBody *	m_pBodyA;
		cRigidBody *	m_pBodyB;
		Base::cVector3	m_Normal;
		Base::cVector3	m_Distance;
		bool			m_Collided;
	};
}
#endif //CollisionInfo_hxx