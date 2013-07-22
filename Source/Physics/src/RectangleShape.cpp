// *****************************************************************************
//  RectangleShape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "RectangleShape.h"

using namespace Physics;
using namespace Base;

// *****************************************************************************
cRectangleShape::cRectangleShape()
{
}

// *****************************************************************************
cRectangleShape::~cRectangleShape()
{
}

// *****************************************************************************
void cRectangleShape::VInitialize(const cVector3 & MinVertex, const cVector3 & MaxVertex)
{
	m_Center = ((MinVertex + MaxVertex) * 0.5f);
	m_HalfExtents = ((MaxVertex - MinVertex) * 0.5f);
}

// *****************************************************************************
IShape * IShape::CreateRectangleShape()
{
	return DEBUG_NEW cRectangleShape();
}
