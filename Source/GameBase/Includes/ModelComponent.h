// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"
#include "GameBaseDefines.h"
#include "Transform3DComponent.h"

namespace Graphics
{
	class IModel;
	class ICamera;
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
		void UpdateTransform(const cTransform3DComponent * const pTransform);
		void Render(const Graphics::ICamera * const pCamera);

	public:
		Base::cString		m_strModelName;	///< The model file name

	private :
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		Base::cString VGetName() const { return m_Name.GetString(); }

	private:
		static Base::cHashedString	m_Name;	///< The component name
		Graphics::IModel *			m_pModel;	///< The 3D model
		cTransform3DComponent *		m_pTransform;
	};
}
#endif // ModelComponent_h__
