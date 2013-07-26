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
		void VSetPosition(const Base::cVector3 & position);
		void VSetRotation(const Base::cVector3 & rotation);
		void VSetSize(const Base::cVector3 & size);
		void VRender(const Graphics::ICamera * const pCamera);
		void VGetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBounds);
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }
		
	private:
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		GAMEBASE_API static Base::cHashedString		m_Name;	///< The component name
		shared_ptr<Graphics::ISprite>	m_pSprite;	///< The 2d Sprite
	};
}
#endif // SpriteComponent_h__