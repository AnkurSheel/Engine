// *****************************************************************************
//  BaseEntity   version:  1.0   Ankur Sheel  date: 2012/07/30
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseEntity_h__
#define BaseEntity_h__

#include "BaseEntity.hxx"
#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseComponent;
}

namespace GameBase
{
	class cBaseEntity
		: public IBaseEntity
		, public Base::cNonCopyable
	{
	private :
		typedef std::map<unsigned long, IBaseComponent *> ComponentMap;

	public:
		GAMEBASE_API cBaseEntity(const int iID);
		GAMEBASE_API cBaseEntity();
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API void AddComponent(IBaseComponent * pComponent);
		GAMEBASE_API unsigned long RemoveComponent(const Base::cString & strComponentName);
		GAMEBASE_API void GetAllComponents(ComponentList & components) const;
		GAMEBASE_API IBaseComponent * GetComponent(const Base::cString & strComponentName);
		GAMEBASE_API int GetID() const;
		GAMEBASE_API virtual unsigned long VGetHashedID() const  = 0;

	protected:
		GAMEBASE_API void VInitialize();
		GAMEBASE_API void VCleanup();

	private:
		GAMEBASE_API bool VOnHandleMessage(const AI::Telegram & telegram);
		void SetID(const int iID);

	private:
		int				m_iID;
		ComponentMap	m_Components;
		static int		m_siNextValidID;
	};
}
#endif // BaseEntity_h__