// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef SpriteComponent_h__
#define SpriteComponent_h__

#include "GameBaseDefines.h"
#include "BaseComponent.h"

namespace Graphics
{
	class ISprite;
	class ICamera;
}

namespace Base
{
	class cVector2;
}

namespace GameBase
{
	class cSpriteComponent
		: public cBaseComponent
	{
	public:
		GAMEBASE_API cSpriteComponent();
		GAMEBASE_API ~cSpriteComponent();
		void VInitialize();
		void VCleanup();
		void UpdateTransform(const Base::cVector2 & vPosition,
			const Base::cVector2 & vRotation, const Base::cVector2 & vSize);
		void Render(const Graphics::ICamera * const pCamera);

	public:
		Base::cString					m_strSpriteName;	///< The sprite file name

	private:
		shared_ptr<Graphics::ISprite>	m_pSprite;	///< The 2d Sprite
	};
}
#endif // SpriteComponent_h__