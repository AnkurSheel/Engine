// *****************************************************************************
//  PhysicsSystem version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef PhysicsSystem_h__
#define PhysicsSystem_h__

#include "GameBaseDefines.h"
#include "Process.h"

namespace GameBase
{
	class IEventData;
	typedef shared_ptr<IEventData> IEventDataPtr;
}

namespace GameBase
{
	class cPhysicsSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cPhysicsSystem();
		GAMEBASE_API ~cPhysicsSystem();
		void VInitialize();
		void VUpdate(const float DeltaTime);
		void ActorInitializedListener(IEventDataPtr pEventData);
		void ActorScaledListener(IEventDataPtr pEventData);
	};
}
#endif // PhysicsSystem_h__
