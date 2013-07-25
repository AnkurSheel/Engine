// *****************************************************************************
//  ActorMovedEventData version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ActorMovedEventData_h__
#define ActorMovedEventData_h__

#include "BaseEventData.h"

namespace GameBase
{
	class cActorMovedEventData
		: public cBaseEventData
	{
	public:
		cActorMovedEventData();
		~cActorMovedEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }

	public:
		static Base::cHashedString m_Name;
	};
}
#endif //ActorMovedEventData_h__