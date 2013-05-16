// *****************************************************************************
//  KeyboardHandlerComponent version:  1.0   Ankur Sheel  date: 2013/05/16
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "stdafx.h"
#include "KeyboardHandlerComponent.h"
#include "KeyboardController.hxx"

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
void cKeyboardHandlerComponent::Update()
{
	if(IKeyboardController::Instance()->VIsKeyPressed(VK_LEFT))
	{
		Log_Write(ILogger::LT_COMMENT, 1, "Left Pressed");
	}
	else if(IKeyboardController::Instance()->VIsKeyPressed(VK_RIGHT))
	{
		Log_Write(ILogger::LT_COMMENT, 1, "Right Pressed");
	}
}
