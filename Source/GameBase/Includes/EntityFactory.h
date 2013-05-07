// *****************************************************************************
//  EntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef EntityFactory_h__
#define EntityFactory_h__

#include "GenericObjectCreation.h"
#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseEntity;
	class IBaseComponent;
}

namespace GameBase
{
	class cEntityFactory
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cEntityFactory();
		GAMEBASE_API virtual ~cEntityFactory();
		GAMEBASE_API virtual void RegisterEntities() = 0;
		GAMEBASE_API virtual IBaseEntity * VCreateEntity(const Base::cHashedString & Type) = 0;
		GAMEBASE_API static cEntityFactory * Instance() { return m_pInstance; }
		GAMEBASE_API virtual void RegisterComponents();

	protected:
		GenericObjectFactory<IBaseEntity, unsigned long>	m_RegisteredEntities;
		GenericObjectFactory<IBaseComponent, unsigned long>	m_RegisteredComponents;
		GAMEBASE_API static cEntityFactory *				m_pInstance;
	};

}
#endif // EntityFactory_h__
