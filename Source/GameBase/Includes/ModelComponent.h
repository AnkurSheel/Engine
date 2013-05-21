// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"
#include "GameBaseDefines.h"
#include "RenderableComponent.hxx"

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
	class cModelComponent
		: public cBaseComponent
		, public IRenderableComponent
	{
	public:
		GAMEBASE_API cModelComponent();
		GAMEBASE_API ~cModelComponent();
		void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		void VCleanup();
		void VUpdateTransform(const Base::cVector3 & vPosition,
			const Base::cVector3 & vRotation, const Base::cVector3 & vSize);
		void VRender(const Graphics::ICamera * const pCamera);
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }

	private :
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		Graphics::IModel *			m_pModel;	///< The 3D model
		static Base::cHashedString	m_Name;	///< The component name
	};
}
#endif // ModelComponent_h__
