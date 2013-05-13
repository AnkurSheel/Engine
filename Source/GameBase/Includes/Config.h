// *****************************************************************************
//  Config   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#ifndef Config_h__
#define Config_h__

#include "GenericObjectCreation.h"
#include "GameBaseDefines.h"

namespace GameBase
{
	class cEntityDef;
	class IBaseComponent;
}

namespace GameBase
{
	class cConfig
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API virtual void VInitialize(const Base::cString & FileName) = 0;
		GAMEBASE_API static const cEntityDef * const GetEntityDef(const Base::cHashedString & EntityType);
		GAMEBASE_API virtual ~cConfig();

	protected:
		GAMEBASE_API cConfig();
		GAMEBASE_API void InitPrivate(const Base::cString & FileName);

	protected:
		typedef std::map<unsigned long, const cEntityDef *> EnitityDefMap;
		EnitityDefMap										m_EntityDefs;
		GenericObjectFactory<IBaseComponent, unsigned long>	m_RegisteredComponents;
		GAMEBASE_API static cConfig *						m_pInstance;

	private:
		void Cleanup();
	};
}
#endif // Config_h__