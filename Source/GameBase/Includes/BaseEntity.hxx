// *****************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/31
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseEntity_hxx__
#define BaseEntity_hxx__

#include "GameBaseDefines.h"

namespace AI
{
	struct Telegram;
}

namespace GameBase
{
	class IBaseComponent;
}

namespace GameBase
{
	class IBaseEntity
	{
	public:
		typedef std::list<IBaseComponent *> ComponentList;

	public:
		virtual ~IBaseEntity(){}
		virtual void VInitialize() = 0;
		virtual void VOnUpdate(const float deltaTime) = 0;
		virtual void VCleanup() = 0;
		virtual bool VOnHandleMessage(const AI::Telegram & telegram) = 0;
		virtual void VHandleInput(const unsigned int CharID, const float deltaTime) = 0;
		virtual Base::cString VGetName() const = 0;
		virtual int VGetID() const = 0;
	};
}
#endif // BaseEntity_hxx__