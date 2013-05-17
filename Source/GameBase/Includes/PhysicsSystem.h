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
	class cPhysicsSystem
		: public Utilities::cProcess
	{
	public:
		GAMEBASE_API cPhysicsSystem();
		GAMEBASE_API ~cPhysicsSystem();
		void VUpdate(const float DeltaTime);
	};
}
#endif // PhysicsSystem_h__
