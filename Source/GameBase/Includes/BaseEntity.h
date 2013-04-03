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
	class cBaseComponent;
}

namespace GameBase
{
	class cBaseEntity
		: public IBaseEntity
		, public Base::cNonCopyable
	{
	private :
		typedef std::map<unsigned long, cBaseComponent *> ComponentMap;

	public:
		GAMEBASE_API cBaseEntity(const int iID, const Base::cString strName);
		GAMEBASE_API cBaseEntity(const Base::cString strName);
		GAMEBASE_API virtual ~cBaseEntity();
		GAMEBASE_API virtual void VInitialize();
		GAMEBASE_API virtual void VCleanup();
		GAMEBASE_API int VGetID() const;
		GAMEBASE_API Base::cString VGetName() const;
		

	private:
		void SetID(const int iID);
		
		void AddComponent(cBaseComponent * pComponent);
		void RemoveComponent(cBaseComponent * pComponent);
		cBaseComponent * GetComponent(const Base::cString & strComponentName);

	protected:
		Base::cString	m_strName;

	private:
		int				m_iID;
		ComponentMap	m_Components;
		static int		m_siNextValidID;
	};
}
#endif // BaseEntity_h__