// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"

namespace Graphics
{
	class IModel;
}

namespace GameBase
{
	class cModelComponent
		: public cBaseComponent
	{
	public:
		cModelComponent(const Base::cString & strModelName);
		~cModelComponent();
		void VInitialize();
		void VCleanup();

	private:
		Graphics::IModel *	m_pModel;	///< The 3D model
		Base::cString		m_strModelName;	///< The model file name
	};
}
#endif // ModelComponent_h__
