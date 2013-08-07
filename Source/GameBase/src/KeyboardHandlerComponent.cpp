// *****************************************************************************
//  KeyboardHandlerComponent version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "KeyboardHandlerComponent.h"
#include "KeyboardController.hxx"
#include "BaseEntity.hxx"
#include "optional.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cKeyboardHandlerComponent::m_Name = cHashedString("keyboardhandlercomponent");

// *****************************************************************************
cKeyboardHandlerComponent::cKeyboardHandlerComponent()
{
}

// *****************************************************************************
cKeyboardHandlerComponent::~cKeyboardHandlerComponent()
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::VInitialize(const IXMLNode * const pXMLNode)
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::VCleanup()
{
}

// *****************************************************************************
void cKeyboardHandlerComponent::Update(const float deltaTime)
{
	tOptional<unsigned int> charPressed;
	if(IKeyboardController::Instance()->VIsKeyPressed(VK_LEFT))
	{
		charPressed = VK_LEFT;
	}
	else if(IKeyboardController::Instance()->VIsKeyPressed(VK_RIGHT))
	{
		charPressed = VK_RIGHT;
	}
	if(charPressed.IsValid())
	{
		m_pOwner->VHandleInput(*charPressed, deltaTime);
	}
}
