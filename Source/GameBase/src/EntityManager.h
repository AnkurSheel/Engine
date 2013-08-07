// *****************************************************************************
//  EnityManager   version:  1.0   Ankur Sheel  date: 2012/07/27
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#ifndef EntityManager_h__
#define EntityManager_h__

#include "EntityManager.hxx"

namespace GameBase
{
	class IBaseEntity;
	class IBaseComponent;
}

namespace GameBase
{
	class cEntityManager
		: public IEntityManager
		, public Base::cNonCopyable
	{
	private:
		typedef std::map<int, IBaseEntity * const > EntityMap;
		typedef std::map<unsigned long, EntityList> EntityComponentMap;

	private:
		void VInitializeEntityFactory(shared_ptr<cEntityFactory> pEntityFactory);
		void VInitializeComponentFactory(shared_ptr<cComponentFactory> pComponentFactory);
		void VAddEntity(IBaseEntity * const pNewEntity);
		IBaseEntity * const VAddEntity(const Base::cString & Type);
		void VDeleteEntity(IBaseEntity * const pNewEntity);
		void VAddComponent(IBaseEntity * const pEntity, IBaseComponent * pComponent);
		void VRemoveComponent(IBaseEntity * const pEntity,
			const unsigned long ComponentID);
		void VGetEntities(const Base::cHashedString & Component,
			EntityList & entities);
		IBaseEntity * const VGetEntityFromID(const int iID) const;
		Base::cString VGetEntityNameFromID(const int iID) const;
		Base::cString VGetEntityName(const IBaseEntity * const pEntity) const;
		IBaseComponent * VGetComponent(IBaseEntity * pEntity, const Base::cHashedString & ComponentName);
		int VGetEntityID(const IBaseEntity * const pEntity) const;
		void VUpdate(const float deltaTime);
		void InitializeEntity(IBaseEntity * const pEntity);
		void Cleanup();

		cEntityManager();
		~cEntityManager();

	private:
		static IEntityManager *			s_pEntityManager;
		EntityMap						m_EntityMap;
		EntityComponentMap				m_ComponentMap;
		shared_ptr<cEntityFactory>		m_pEntityFactory;
		shared_ptr<cComponentFactory>	m_pComponentFactory;

	private:
		friend static IEntityManager * IEntityManager::GetInstance();
		friend static void IEntityManager::Destroy();
	};
}
#endif // EnityManager_h__
