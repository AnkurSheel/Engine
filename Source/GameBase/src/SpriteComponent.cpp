// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "SpriteComponent.h"
#include "Sprite.hxx"

using namespace Graphics;
using namespace GameBase;
using namespace Base;

// *****************************************************************************
cSpriteComponent::cSpriteComponent()
	: cBaseComponent("SpriteComponent")
	, m_pSprite(NULL)
{

}

// *****************************************************************************
cSpriteComponent::~cSpriteComponent()
{
	VCleanup();
}

// *****************************************************************************
void cSpriteComponent::VInitialize()
{
	if (!m_strSpriteName.IsEmpty())
	{
		m_pSprite = ISprite::CreateSprite();
		m_pSprite->VInitialize(m_strSpriteName);
	}
}

// *****************************************************************************
void cSpriteComponent::VCleanup()
{
	//SafeDelete(&m_pSprite);
}

// *****************************************************************************
void cSpriteComponent::UpdateTransform(const Base::cVector2<float> & vPosition,
	const Base::cVector2<float> & vRotation, const Base::cVector2<float> & vSize)
{
	if(m_pSprite != NULL)
	{
		m_pSprite->VSetPosition(vPosition);
		m_pSprite->VSetSize(vSize);
	}
}

// *****************************************************************************
void cSpriteComponent::Render(const ICamera * const pCamera)
{
	if(m_pSprite)
	{
		m_pSprite->VRender(pCamera);
	}
}