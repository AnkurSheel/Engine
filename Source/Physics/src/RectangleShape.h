// *****************************************************************************
//  RectangleShape version:  1.0   Ankur Sheel  date: 2013/06/07
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef RectangleShape_hxx
#define RectangleShape_hxx

#include "Shape.h"

namespace Physics
{
	class cRectangleShape 
		: public cShape
	{
	public:
		cRectangleShape();
		~cRectangleShape();
		void VInitialize(const Base::cVector3 & MinVertex, const Base::cVector3 & MaxVertex);
	};
}
#endif //RectangleShape_hxx