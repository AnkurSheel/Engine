// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseComponent_h__
#define BaseComponent_h__

namespace GameBase
{
	class IBaseEntity;
}

namespace GameBase
{
	class cBaseComponent
	{
	public:
		cBaseComponent(const Base::cString & strComponentName);
		virtual ~cBaseComponent();
		virtual void VInitialize();
		virtual void VCleanup();
		Base::cString GetName() const;
		unsigned long GetHashedID() const;
		void SetOwner(const IBaseEntity * const pNewOwner);

	private:
		Base::cHashedString		m_strComponentName;
		const IBaseEntity *		m_pOwner;
	};
}
#endif //Component_hxx__