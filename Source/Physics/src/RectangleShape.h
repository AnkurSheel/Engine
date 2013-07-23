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
		void VInitialize(const Base::cVector3 & MinBound, const Base::cVector3 & MaxBound);
		static Base::cHashedString	GetName()  {return m_Name; }

	private:
		static Base::cHashedString			m_Name;	///< The component name
	};
}
#endif //RectangleShape_hxx