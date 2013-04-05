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
		GAMEBASE_API cBaseEntity(const int iID, const Base::cString & strName);
		GAMEBASE_API cBaseEntity(const Base::cString & strName);
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API void AddComponent(IBaseComponent * pComponent);
		GAMEBASE_API unsigned long RemoveComponent(const Base::cString & strComponentName);
		GAMEBASE_API void GetAllComponents(ComponentList & components) const;
		GAMEBASE_API IBaseComponent * GetComponent(const Base::cString & strComponentName);
		GAMEBASE_API Base::cString GetName() const;
		GAMEBASE_API int GetID() const;

	private:
		GAMEBASE_API bool VOnHandleMessage(const AI::Telegram & telegram);

		void SetID(const int iID);

	protected:
		GAMEBASE_API void VInitialize();
		GAMEBASE_API void VCleanup();

	protected:
		Base::cString	m_strName;

	private:
		int				m_iID;
		ComponentMap	m_Components;
		static int		m_siNextValidID;
	};
}
#endif // BaseEntity_h__