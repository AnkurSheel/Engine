//  *******************************************************************************************************************
//  UiControlFactory   version:  1.0   Ankur Sheel  date: 2013/05/15
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#include "StdAfx.h"
#include "UiControlFactory.h"
#include "WindowControl.h"
#include "LabelControl.h"

using namespace Graphics;
using namespace Base;
using namespace Utilities;

cUiControlFactory * cUiControlFactory::m_pInstance = NULL;

//  *******************************************************************************************************************
cUiControlFactory::cUiControlFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

//  *******************************************************************************************************************
cUiControlFactory::~cUiControlFactory()
{
}

//  *******************************************************************************************************************
void cUiControlFactory::VRegisterUiControls()
{
	m_RegisteredControls.Register<cWindowControl>(cWindowControl::GetName().GetHash());
	m_RegisteredControls.Register<cLabelControl>(cLabelControl::GetName().GetHash());
}

//  *******************************************************************************************************************
IBaseControl * cUiControlFactory::CreateUiControl(const Base::cHashedString & Type)
{
	IBaseControl * pControl= m_RegisteredControls.Create(Type.GetHash());
	return pControl;
}