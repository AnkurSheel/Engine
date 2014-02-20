//  *******************************************************************************************************************
//  LabelControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#include "stdafx.h"
#include "LabelControl.h"
#include "Sentence.hxx"
#include "Sprite.hxx"
#include "XMLNode.hxx"
#include "Optional.h"

using namespace Base;
using namespace Utilities;
using namespace Graphics;

cHashedString cLabelControl::m_Name = cHashedString("labelcontrol");

//  *******************************************************************************************************************
cLabelControl::cLabelControl()
: m_pSentence(NULL)
{
}

//  *******************************************************************************************************************
cLabelControl::~cLabelControl()
{
	VCleanup();
}

//  *******************************************************************************************************************
void cLabelControl::VInitialize(const shared_ptr<IXMLNode const> pXMLNode) 
{
	if(pXMLNode == NULL)
	{
		return;
	}
	
	cString font = pXMLNode->VGetChildValue("Font");
	if(!font.IsEmpty())
	{
		cString text = pXMLNode->VGetChildValue("Text");
		cString value = pXMLNode->VGetChildValue("Height");
		tOptional<float> height = value.ToFloat();
		if(!height.IsValid())
		{
			height = 8.0f;
		}

		cColor textColor;
		shared_ptr<IXMLNode> ptextColor(pXMLNode->VGetChild("TextColor"));
		if(ptextColor != NULL)
		{
			textColor.m_iRed = ptextColor->VGetNodeAttributeAsInt("r");
			textColor.m_iBlue = ptextColor->VGetNodeAttributeAsInt("b");
			textColor.m_iGreen = ptextColor->VGetNodeAttributeAsInt("g");
			textColor.m_iAlpha = ptextColor->VGetNodeAttributeAsInt("a");
		}

		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(font, text, textColor);
		m_pSentence->VSetHeight(*height);
	}

	cBaseControl::VInitialize(pXMLNode);

	cString value = pXMLNode->VGetChildValue("AutoSize");
	tOptional<bool> autoSize = value.ToBool();
	
	if(m_pSentence != NULL && autoSize.IsValid() && *autoSize == true)
	{
		VSetSize(cVector2(m_pSentence->VGetWidth(), m_pSentence->VGetHeight()));
	}

}

//  *******************************************************************************************************************
void cLabelControl::Initialize(const cLabelControlDef & def)
{
	if(!def.strFont.IsEmpty())
	{
		m_pSentence = ISentence::CreateSentence();
		m_pSentence->VInitialize(def.strFont, def.strText, def.textColor);
		m_pSentence->VSetHeight(def.fTextHeight);
	}
	if(!def.strBGImageFile.IsEmpty())
	{
		m_pBGSprite = ISprite::CreateSprite();
		m_pBGSprite->VInitialize(def.strBGImageFile);
	}

	cBaseControl::Initialize(def);
	if(def.bAutoSize && m_pSentence != NULL)
	{
		VSetSize(cVector2(m_pSentence->VGetWidth(), m_pSentence->VGetHeight()));
	}
}

//  *******************************************************************************************************************
void cLabelControl::VRender(const ICamera * const pCamera)
{
	if(m_bVisible)
	{
		cBaseControl::VRender(pCamera);
		if (m_pSentence)
		{
			m_pSentence->VRender(pCamera);
		}
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VSetAbsolutePosition()
{
	cBaseControl::VSetAbsolutePosition();
	if(m_pSentence)
	{
		m_pSentence->VSetPosition(m_vControlAbsolutePosition);	
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VSetText(const Base::cString & strText)
{
	if(m_pSentence != NULL)
	{
		m_pSentence->VSetText(strText);
		VSetSize(cVector2(m_pSentence->VGetWidth(strText), m_pSentence->VGetHeight()));
	}
}

//  *****************************************************************************************************************************
void cLabelControl::VCleanup()
{
	SafeDelete(&m_pSentence);
	cBaseControl::VCleanup();
}

//  *****************************************************************************************************************************
IBaseControl * IBaseControl::CreateLabelControl(const cLabelControlDef & def)
{
	cLabelControl * pControl = DEBUG_NEW cLabelControl();
	pControl->Initialize(def);
	return pControl;
}