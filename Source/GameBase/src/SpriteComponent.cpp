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

cHashedString	cSpriteComponent::m_Name = cHashedString("spritecomponent");

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
void cSpriteComponent::VSetPosition(const cVector3 & position)
{
	if(m_pSprite != NULL)
	{
		m_pSprite->VSetPosition(cVector2(position.x, position.y));
	}
}

// *****************************************************************************
void cSpriteComponent::VSetRotation(const cVector3 & rotation)
{
}

// *****************************************************************************
void cSpriteComponent::VSetSize(const cVector3 & size)
{
	if(m_pSprite != NULL)
	{
		m_pSprite->VSetSize(cVector2(size.x, size.y));
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
void cSpriteComponent::VGetBounds(cVector3 & minBound, cVector3 & maxBounds)
{
	minBound = cVector3::Zero();
	maxBounds = cVector3(m_pSprite->VGetScaledSize().x, m_pSprite->VGetScaledSize().y, 0.0f);
}
