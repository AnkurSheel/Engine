// *****************************************************************************
//  ComponentCreator version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ComponentCreator_h__
#define ComponentCreator_h__

namespace GameBase
{
	class IBaseComponent;
}

namespace GameBase
{
	class cComponentCreator
	{
	public:
		cComponentCreator();
		~cComponentCreator();
		IBaseComponent * CreateComponent(const Base::cString & strComponentName);
		
		static cComponentCreator * GetInstance();
		static void Destroy();

	private:
		static cComponentCreator * s_pComponentCreator;
	};
}
#endif //Component_hxx__