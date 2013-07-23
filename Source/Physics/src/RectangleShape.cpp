// *****************************************************************************
//  RectangleShape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RectangleShape.h"

using namespace Physics;
using namespace Base;

Base::cHashedString	cRectangleShape::m_Name = cHashedString("rectangle");

// *****************************************************************************
cRectangleShape::cRectangleShape()
{
}

// *****************************************************************************
cRectangleShape::~cRectangleShape()
{
}

// *****************************************************************************
void cRectangleShape::VInitialize(const cVector3 & MinBound, const cVector3 & MaxBound)
{
	m_Center = ((MinBound + MaxBound) * 0.5f);
	m_HalfExtents = ((MaxBound - MinBound) * 0.5f);
}

// *****************************************************************************
IShape * IShape::CreateRectangleShape()
{
	return DEBUG_NEW cRectangleShape();
}
