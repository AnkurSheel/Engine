// *****************************************************************************
//  ActorMovedEventData version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ActorMovedEventData_h__
#define ActorMovedEventData_h__

#include "BaseEventData.h"
#include "vector3.h"

namespace GameBase
{
	class cActorMovedEventData
		: public cBaseEventData
	{
	public:
		cActorMovedEventData();
		cActorMovedEventData(const Base::cVector3 & position, const int actorID);
		~cActorMovedEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }
		int GetActorID() const { return m_ActorID; }
		Base::cVector3 GetPosition() const { return m_Position; }

	public:
		static Base::cHashedString m_Name;

	private:
		Base::cVector3	m_Position;
		int				m_ActorID;
	};
}
#endif //ActorMovedEventData_h__