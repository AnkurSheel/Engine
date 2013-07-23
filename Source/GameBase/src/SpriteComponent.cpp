// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "SpriteComponent.h"
#include "Sprite.hxx"
#include "XMLNode.hxx"
#include "vector2.h"
#include "vector3.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cSpriteComponent::m_Name = cHashedString("spritecomponent");

// *****************************************************************************
cSpriteComponent::cSpriteComponent()
	: m_pSprite(NULL)
{

}

// *****************************************************************************
cSpriteComponent::~cSpriteComponent()
{
	VCleanup();
}

cSpriteComponent::cSpriteComponent(const cSpriteComponent & other)
	: cBaseComponent(other)
	, m_pSprite(ISprite::CreateSprite())
{
	m_pSprite->VInitialize(other.m_pSprite->VGetTexture());
}

cSpriteComponent & cSpriteComponent::operator =(const cSpriteComponent & other)
{
	cBaseComponent::operator=(other);
	m_pSprite = ISprite::CreateSprite();
	m_pSprite->VInitialize(other.m_pSprite->VGetTexture());
	return *this;
}


// *****************************************************************************
void cSpriteComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	if(pXMLNode == NULL)
	{
		return;
	}

	shared_ptr<IXMLNode> pName(pXMLNode->VGetChild("Name"));
	if(pName != NULL)
	{
		cString SpriteName = pName->VGetNodeValue(); 
		if (!SpriteName.IsEmpty())
		{
			m_pSprite = ISprite::CreateSprite();
			m_pSprite->VInitialize(SpriteName);
		}
		else
		{
			Log_Write(ILogger::LT_ERROR, 1, "Element Name in Sprite Component cannot be empty");
		}
	}
	else
	{
		Log_Write(ILogger::LT_ERROR, 1, "Missing Element in Sprite Component : Name");
	}
}

// *****************************************************************************
void cSpriteComponent::VCleanup()
{
	//SafeDelete(&m_pSprite);
}

// *****************************************************************************
void cSpriteComponent::VUpdateTransform(const Base::cVector3 & vPosition,
	const Base::cVector3 & vRotation, const Base::cVector3 & vSize)
{
	if(m_pSprite != NULL)
	{
		cVector2 position(vPosition.x, vPosition.y);
		cVector2 size(vSize.x, vSize.y);

		m_pSprite->VSetPosition(position);
		m_pSprite->VSetSize(size);
	}
}

// *****************************************************************************
void cSpriteComponent::VRender(const ICamera * const pCamera)
{
	if(m_pSprite)
	{
		m_pSprite->VRender(pCamera);
	}
}

// *****************************************************************************
void cSpriteComponent::VGetBounds(Base::cVector3 & minBound, Base::cVector3 & maxBounds)
{
	minBound = cVector3::Zero();
	maxBounds = cVector3(m_pSprite->VGetScaledSize().x, m_pSprite->VGetScaledSize().y, 0.0f);
}