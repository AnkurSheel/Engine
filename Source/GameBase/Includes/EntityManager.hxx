// *****************************************************************************
//  EntityManager   version:  1.0   Ankur Sheel  date: 2012/07/31
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef EntityManager_hxx__
#define EntityManager_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseEntity;
	class IBaseComponent;
}

namespace GameBase
{
	class IEntityManager
	{
	public:
		typedef std::list<IBaseEntity *> EntityList;

	public:
		virtual ~IEntityManager(){}
		virtual void VRegisterEntity(IBaseEntity * const pNewEntity) = 0;
		virtual void VUnRegisterEntity(IBaseEntity * const pNewEntity) = 0;
		virtual IBaseEntity * const VGetEntityFromID(const int iID) = 0;
		virtual Base::cString const VGetEntityNameFromID(const int iID) = 0;
		virtual IBaseComponent * VGetComponent(IBaseEntity * pEntity, const Base::cString & strComponentName) = 0;
		virtual void VGetEntities(const Base::cString & strComponentName, EntityList & entities) = 0;
		virtual void VAddComponent(IBaseEntity * pEntity, const Base::cString & strComponentName) = 0;
		virtual void VRemoveComponent(IBaseEntity * pEntity, const Base::cString & strComponentName) = 0;

		GAMEBASE_API static IEntityManager * GetInstance();
		GAMEBASE_API static void Destroy();
	};
}

#endif // EntityManager_hxx__