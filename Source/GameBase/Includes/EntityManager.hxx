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
	class cEntityFactory;
	class cComponentFactory;
}

namespace GameBase
{
	class IEntityManager
	{
	public:
		typedef std::list<IBaseEntity *> EntityList;

	public:
		virtual ~IEntityManager(){}
		virtual void VInitializeEntityFactory(shared_ptr<cEntityFactory> pEntityFactory) = 0;
		virtual void VInitializeComponentFactory(shared_ptr<cComponentFactory> pComponentFactory) = 0;
		virtual void VAddEntity(IBaseEntity * const pNewEntity) = 0;
		virtual IBaseEntity * const VAddEntity(const Base::cString & Type) = 0;
		virtual void VDeleteEntity(IBaseEntity * const pNewEntity) = 0;
		virtual IBaseEntity * const VGetEntityFromID(const int iID) const = 0;
		virtual Base::cString VGetEntityNameFromID(const int iID) const  = 0;
		virtual Base::cString VGetEntityName(const IBaseEntity * const pEntity) const = 0;
		virtual int VGetEntityID(const IBaseEntity * const pEntity) const = 0;
		virtual IBaseComponent * VGetComponent(IBaseEntity * pEntity,
			const Base::cHashedString & ComponentName) = 0;
		virtual void VGetEntities(const Base::cHashedString & Component,
			EntityList & entities) = 0;
		virtual void VAddComponent(IBaseEntity * const pEntity,
			IBaseComponent * pComponent) = 0;
		virtual void VRemoveComponent(IBaseEntity * const pEntity,
			const unsigned long ComponentID) = 0;
		virtual void VUpdate() = 0;

		GAMEBASE_API static IEntityManager * GetInstance();
		GAMEBASE_API static void SetApp(IBaseEntity * const pApp);
		GAMEBASE_API static IBaseEntity * const GetApp();

		GAMEBASE_API static void Destroy();
	};
}

#endif // EntityManager_hxx__