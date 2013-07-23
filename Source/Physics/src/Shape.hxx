// *****************************************************************************
//  Shape version:  1.0   Ankur Sheel  date: 2013/06/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Shape_hxx
#define Shape_hxx

#include "PhysicsDefines.h"

namespace Base
{
	class cVector3;
}

namespace Physics
{
	class IShape
	{
	public:
		virtual ~IShape() {}
		virtual void VInitialize(const Base::cVector3 & MinBound, const Base::cVector3 & MaxBound) = 0;
		virtual Base::cVector3 VGetCenter() const = 0; 
		virtual Base::cVector3 VGetHalfExtents() const = 0;
		static IShape * CreateRectangleShape();
	};
}
#endif //Shape_hxx