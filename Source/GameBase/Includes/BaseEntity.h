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
	class cComponentDef;
}

namespace GameBase
{
	typedef std::map<unsigned long, IBaseComponent *> ComponentMap;
	class cEntityDef
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cEntityDef();
		GAMEBASE_API virtual ~cEntityDef();

	public:
		bool			m_IsCollidable;
		Base::cString	m_Type;
		ComponentMap	m_Components;
	
	private:
		void Cleanup();
	};

	class cBaseEntity
		: public IBaseEntity
	{
	public:
		GAMEBASE_API cBaseEntity();
		GAMEBASE_API cBaseEntity(const int iID);
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API void VInitialize();
		GAMEBASE_API void VCleanup();
		GAMEBASE_API bool VOnHandleMessage(const AI::Telegram & telegram);
		GAMEBASE_API void VHandleInput(const unsigned int CharID);
		GAMEBASE_API virtual unsigned long VGetHashedID() const = 0;
		GAMEBASE_API void AddComponent(IBaseComponent * pComponent);
		GAMEBASE_API void RemoveComponent(const unsigned long ComponentID);
		GAMEBASE_API void GetAllComponents(ComponentList & components) const;
		GAMEBASE_API IBaseComponent * GetComponent(const Base::cHashedString & ComponentName);
		GAMEBASE_API IBaseComponent * GetComponent(const unsigned long ComponentID);
		GAMEBASE_API int GetID() const;

	private:
		void SetID(const int iID);

	private:
		int				m_iID;
		ComponentMap	m_Components;
		static int		m_siNextValidID;
	};
}
#endif // BaseEntity_h__