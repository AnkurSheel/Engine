// *****************************************************************************
//  SpriteComponent   version:  1.0   Ankur Sheel  date: 2013/04/08
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "SpriteComponent.h"
#include "Sprite.hxx"
#include "XMLNode.hxx"

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
	: m_pSprite(ISprite::CreateSprite())
{
}

cSpriteComponent & cSpriteComponent::operator =(const cSpriteComponent & other)
{
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
void cSpriteComponent::UpdateTransform(const Base::cVector2 & vPosition,
	const Base::cVector2 & vRotation, const Base::cVector2 & vSize)
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