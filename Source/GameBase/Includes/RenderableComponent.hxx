// *****************************************************************************
//  RenderableComponent   version:  1.0   Ankur Sheel  date: 2013/05/21
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef RenderableComponent_hxx__
#define RenderableComponent_hxx__

#include "GameBaseDefines.h"

namespace Base
{
	class cVector3;
}
namespace Graphics
{
	class ICamera;
}

namespace GameBase
{
	class IRenderableComponent
	{
	public:
		virtual ~IRenderableComponent() {};
		virtual void VUpdateTransform(const Base::cVector3 & vPosition,
			const Base::cVector3 & vRotation, const Base::cVector3 & vSize) = 0;
		virtual void VRender(const Graphics::ICamera * const pCamera) = 0;
		virtual void VGetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBounds) = 0;
	};
}
#endif // RenderableComponent_hxx__