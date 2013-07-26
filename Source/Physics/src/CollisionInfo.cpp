#include "stdafx.h"
#include "CollisionInfo.h"
#include "RigidBody.h"
#include "Shape.hxx"
#include "RectangleShape.h"
#include "Vector2.h"

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
	if(m_pBodyA->GetCollisionShape()->VGetName() == cRectangleShape::m_Name
		&& m_pBodyB->GetCollisionShape()->VGetName() == cRectangleShape::m_Name)
	{
		cVector3 centerDelta = m_pBodyA->GetCollisionShape()->VGetCenter() -  m_pBodyB->GetCollisionShape()->VGetCenter();
		cVector3 overlap = centerDelta;
		overlap.AbsTo();

		cVector3 halfExtentSum = m_pBodyA->GetCollisionShape()->VGetHalfExtents() + m_pBodyB->GetCollisionShape()->VGetHalfExtents();
		overlap = halfExtentSum - overlap;

		m_Collided = overlap.x > 0 && overlap.y > 0;
		if(m_Collided)
		{
			cVector2 smallestOverlap = cVector2(overlap.x, overlap.y);
			smallestOverlap = smallestOverlap.MinorAxis();

			cVector3 smallestOverlap3 = cVector3(smallestOverlap.x, smallestOverlap.y, 0.0f);
			m_Normal = (centerDelta * smallestOverlap3).MajorAxis();
			m_Distance = overlap * m_Normal;
		}
	}
}
