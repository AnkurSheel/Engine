// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"
#include "GameBaseDefines.h"

namespace Utilities
{
	class IXMLNode;
}

namespace Graphics
{
	class IModel;
	class ICamera;
}

namespace GameBase
{
	class cTransformComponent;
}

namespace GameBase
{
	class cModelComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cModelComponent();
		GAMEBASE_API ~cModelComponent();
		void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		void VCleanup();
		void UpdateTransform(const cTransformComponent * const pTransform);
		void Render(const Graphics::ICamera * const pCamera);

	public:
		Base::cString		m_strModelName;	///< The model file name
		static Base::cHashedString	m_Name;	///< The component name

	private :
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		Graphics::IModel *			m_pModel;	///< The 3D model
		cTransformComponent *		m_pTransform;
	};
}
#endif // ModelComponent_h__
