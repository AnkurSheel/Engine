// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "ModelComponent.h"
#include "Model.hxx"

using namespace Graphics;
using namespace GameBase;
using namespace Base;

Base::cHashedString	cModelComponent::m_Name = cHashedString("modelcomponent");

// *****************************************************************************
cModelComponent::cModelComponent()
	: m_pModel(NULL)
	, m_pTransform(NULL)
{
}

cModelComponent::~cModelComponent()
{
	VCleanup();
}

// *****************************************************************************
void cModelComponent::VInitialize()
{
	m_pTransform = DEBUG_NEW cTransform3DComponent();
	if (!m_strModelName.IsEmpty())
	{
		m_pModel = IModel::CreateModel(m_strModelName);
		m_pModel->VRecalculateWorldMatrix(m_pTransform->m_vPosition,
					m_pTransform->m_vRotation, m_pTransform->m_vScale);
	}
}

// *****************************************************************************
void cModelComponent::VCleanup()
{
	SafeDelete(&m_pModel);
	SafeDelete(&m_pTransform);
}

// *****************************************************************************
void cModelComponent::UpdateTransform(const cTransform3DComponent * const pTransform)
{
	if(m_pTransform != NULL)
	{
		if(m_pTransform->m_vPosition != pTransform->m_vPosition
			|| m_pTransform->m_vRotation != pTransform->m_vRotation
			|| m_pTransform->m_vScale != pTransform->m_vScale)
		{
			*(m_pTransform) = *(pTransform);
			if(m_pModel != NULL)
			{
				m_pModel->VRecalculateWorldMatrix(m_pTransform->m_vPosition,
					m_pTransform->m_vRotation, m_pTransform->m_vScale);
			}
		}
	}
}

// *****************************************************************************
void cModelComponent::Render(const ICamera * const pCamera)
{
	if(m_pModel != NULL)
	{
		m_pModel->VRender(pCamera);
	}

}