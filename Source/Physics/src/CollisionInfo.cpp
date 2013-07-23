#include "stdafx.h"
#include "CollisionInfo.h"
#include "RigidBody.h"
#include "Shape.hxx"

using namespace Physics;
using namespace Base;

// *****************************************************************************
cCollisionInfo::cCollisionInfo(cRigidBody * pBodyA, cRigidBody * pBodyB)
	: m_pBodyA(pBodyA)
	, m_pBodyB(pBodyB)
{
}

// *****************************************************************************
cCollisionInfo::~cCollisionInfo()
{
}

// *****************************************************************************
void cCollisionInfo::Solve()
{
	cVector3 vCenterDelta = m_pBodyA->GetCollisionShape()->VGetCenter() -  m_pBodyB->GetCollisionShape()->VGetCenter();
	cVector3 vOverlap = vCenterDelta;
	vOverlap.AbsTo();

	cVector3 vHalfExtentSum = m_pBodyA->GetCollisionShape()->VGetHalfExtents() + m_pBodyB->GetCollisionShape()->VGetHalfExtents();
	vOverlap = vHalfExtentSum - vOverlap;

	m_Collided = vOverlap.x > 0 && vOverlap.y > 0;
	if(m_Collided)
	{
		cVector3 vSmallestOverlap = vOverlap.MinorAxis();

		m_Normal = (vCenterDelta * vSmallestOverlap).MajorAxis();
		m_Distance = vOverlap * m_Normal;
	}
}
