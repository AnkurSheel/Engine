// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseComponent_h__
#define BaseComponent_h__

#include "BaseComponent.hxx"

namespace GameBase
{
	class IBaseEntity;
}

namespace GameBase
{
	class cBaseComponent
		: public IBaseComponent
	{
	public:
		cBaseComponent(const Base::cString & strComponentName);
		virtual ~cBaseComponent();
		unsigned long VGetID() const;
		void VSetOwner(const IBaseEntity * const pNewOwner);
		Base::cString VGetName() const;

	private:
		Base::cHashedString		m_strComponentName;
		const IBaseEntity *		m_pOwner;
	};
}
#endif //Component_hxx__