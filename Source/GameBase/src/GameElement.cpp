// *****************************************************************************
//  GameElement   version:  1.0   Ankur Sheel  date: 05/14/2008
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "GameElement.h"
#include "Model.hxx"
#include "Vector3.h"
#include "BaseApp.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;

const cBaseApp * cGameElement::m_pBaseApp = NULL;

// *******************************************************************************************
cGameElement::cGameElement()
: m_bIsDirty(false)
, m_bActive(true)
, m_fReactivateTime(0.0f)
, m_bVisible(true)
{

}

// *******************************************************************************************
cGameElement::~cGameElement()
{
	Cleanup();
}

// *******************************************************************************************
void cGameElement::VInitialize(const cGameElementDef & def)
{
	SetPosition(def.vPosition);
	SetScale(def.vScale);
	SetRotation(def.vRotation);
}

// *******************************************************************************************
void cGameElement::OnUpdate(float fElapsedTime)
{
	if(!m_bActive)
	{
		if(m_fReactivateTime > 0.0f && m_fReactivateTime <= m_pBaseApp->GetRunningTime())
		{
			VSetActive(true);
			m_fReactivateTime = 0.0f;
			OnRestart();
		}
	}
}

// *******************************************************************************************
void cGameElement::VOnRender(const ICamera * const pCamera)
{
	//if (m_bActive && m_bVisible && m_pModel != NULL)
	//{
	//	m_pModel->VRender(pCamera);
	//}
}

// *******************************************************************************************
cVector3 cGameElement::GetRotation() const
{
	return m_vRotation;
}

// *******************************************************************************************
void cGameElement::SetRotation(const Base::cVector3 & vRadians)
{
	if(m_vRotation != vRadians)
	{
		m_bIsDirty = true;
		m_vRotation.x = ClampToTwoPi(vRadians.x);
		m_vRotation.y = ClampToTwoPi(vRadians.y);
		m_vRotation.z = ClampToTwoPi(vRadians.z);
	}
}

// ***************************************************************************************
void cGameElement::SetPosition(const Base::cVector3 & vPosition)
{
	if(m_vPosition != vPosition)
	{
		m_bIsDirty = true;
		m_vPosition = vPosition;
	}
}

// ***************************************************************************************
cVector3 cGameElement::GetPosition() const
{
	return m_vPosition;
}

// ***************************************************************************************
void cGameElement::SetScale(const Base::cVector3 & vScale)
{
	if(m_vScale!= vScale)
	{
		m_bIsDirty = true;
		m_vScale= vScale;
	}
}

// ***************************************************************************************
cVector3 cGameElement::GetScale() const
{
	return m_vScale;
}

// *******************************************************************************************
const IAABB * const cGameElement::GetAABB() const
{
	//if(m_pModel)
	//{
	//	return m_pModel->VGetAABB();
	//}
	return NULL;
}

// *****************************************************************************
bool cGameElement::IsActive() const
{
	return m_bActive;
}

// *****************************************************************************
void cGameElement::VSetActive(const bool bActive)
{
	m_bActive = bActive;
}

// *******************************************************************************************
void cGameElement::MakeInactiveFor(const float fSeconds)
{
	if(m_bActive)
	{
		VSetActive(false);
		m_fReactivateTime = m_pBaseApp->GetRunningTime() + fSeconds;
	}
}

// *******************************************************************************************
void cGameElement::OnRestart()
{

}

// *****************************************************************************
void cGameElement::SetApp(const IBaseApp * const pApp)
{
	m_pBaseApp = dynamic_cast<const cBaseApp *>(pApp);
}


// *******************************************************************************************
void cGameElement::Cleanup()
{
	//SafeDelete(&m_pModel);
}
