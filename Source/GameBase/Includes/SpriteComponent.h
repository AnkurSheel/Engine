// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef SpriteComponent_h__
#define SpriteComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"
#include "RenderableComponent.hxx"

namespace Utilities
{
	class IXMLNode;
}

namespace Graphics
{
	class ISprite;
	class ICamera;
}

namespace Base
{
	class cVector3;
}

namespace GameBase
{
	class cSpriteComponent
		: public cBaseComponent
		, public IRenderableComponent
	{
	public:
		GAMEBASE_API cSpriteComponent();
		GAMEBASE_API ~cSpriteComponent();
		GAMEBASE_API cSpriteComponent(const cSpriteComponent & other);
		GAMEBASE_API cSpriteComponent & operator =(const cSpriteComponent & other);

		GAMEBASE_API void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		GAMEBASE_API void VCleanup();
		void VUpdateTransform(const Base::cVector3 & vPosition,
			const Base::cVector3 & vRotation, const Base::cVector3 & vSize);
		void VRender(const Graphics::ICamera * const pCamera);
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		
	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		GAMEBASE_API static Base::cHashedString		m_Name;	///< The component name
		shared_ptr<Graphics::ISprite>	m_pSprite;	///< The 2d Sprite
	};
}
#endif // SpriteComponent_h__