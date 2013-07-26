// *****************************************************************************
//  Shape version:  1.0   Ankur Sheel  date: 2013/06/22
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Shape_h
#define Shape_h

#include "Shape.hxx"
#include "vector3.h"

namespace Physics
{
	class cShape
		: public IShape
	{
	public:
		cShape();
		virtual ~cShape();
		virtual Base::cHashedString VGetShapeName() = 0;
		cShape(const cShape & other);
		cShape & operator =(const cShape & other);
		Base::cVector3 VGetCenter() const { return m_Center; }
		Base::cVector3 VGetHalfExtents() const { return m_HalfExtents; }
		Base::cHashedString VGetName() { return VGetShapeName(); }

	protected:
		Base::cVector3	m_Center;
		Base::cVector3	m_HalfExtents;
	};
}
#endif //Shape_h