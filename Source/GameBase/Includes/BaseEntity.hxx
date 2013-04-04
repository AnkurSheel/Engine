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
		virtual ~IBaseEntity(){}
		virtual void VInitialize() = 0;
		virtual void VOnUpdate() = 0;
		virtual bool VOnHandleMessage(const AI::Telegram & telegram) = 0;
		virtual int VGetID() const = 0;
		virtual Base::cString VGetName() const = 0;
		virtual IBaseComponent * VGetComponent(const Base::cString & strComponentName) = 0;			
	};
}
#endif // BaseEntity_hxx__