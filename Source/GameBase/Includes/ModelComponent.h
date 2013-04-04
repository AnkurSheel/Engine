// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"
#include "GameBaseDefines.h"

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
		GAMEBASE_API cModelComponent();
		GAMEBASE_API ~cModelComponent();
		void VInitialize();
		void VCleanup();

	public:
		Base::cString		m_strModelName;	///< The model file name

	private:
		Graphics::IModel *	m_pModel;	///< The 3D model
	};
}
#endif // ModelComponent_h__
