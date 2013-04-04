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

	public:
		IBaseEntity * const VGetEntityFromID(const int iID);
		Base::cString const VGetEntityNameFromID(const int iID);
		IBaseComponent * VGetComponent(IBaseEntity * pEntity, const Base::cString & strComponentName);

	private:
		void VRegisterEntity(IBaseEntity * const pNewEntity);
		void VUnRegisterEntity(IBaseEntity * const pNewEntity);
		void VAddComponent(IBaseEntity * pEntity, IBaseComponent * pComponent);
		void VRemoveComponent(IBaseEntity * pEntity, const Base::cString & strComponentName);
		void VGetEntities(const Base::cString & strComponentName, EntityList & entities);

		void Cleanup();

		cEntityManager();
		~cEntityManager();

	private:
		EntityMap			m_EntityMap;
		EntityComponentMap	m_ComponentMap;
		static IEntityManager * s_pEntityManager;

		private:
			friend static IEntityManager * IEntityManager::GetInstance();
			friend static void IEntityManager::Destroy();

	};

}
#endif // EnityManager_h__
