// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "ModelComponent.h"
#include "Model.hxx"
#include "TransformComponent.h"

using namespace Graphics;
using namespace GameBase;
using namespace Base;
using namespace Utilities;

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
void cModelComponent::VInitialize(const IXMLNode * const pXMLNode)
{
	m_pTransform = DEBUG_NEW cTransformComponent();
	if (!m_strModelName.IsEmpty())
	{
		m_pModel = IModel::CreateModel(m_strModelName);
		m_pModel->VRecalculateWorldMatrix(m_pTransform->m_Position,
					m_pTransform->m_Rotation, m_pTransform->m_Size);
	}
}

// *****************************************************************************
void cModelComponent::VCleanup()
{
	SafeDelete(&m_pModel);
	SafeDelete(&m_pTransform);
}

// *****************************************************************************
void cModelComponent::UpdateTransform(const cTransformComponent * const pTransform)
{
	if(m_pTransform != NULL)
	{
		if(m_pTransform->m_Position != pTransform->m_Position
			|| m_pTransform->m_Rotation != pTransform->m_Rotation
			|| m_pTransform->m_Size != pTransform->m_Size)
		{
			*(m_pTransform) = *(pTransform);
			if(m_pModel != NULL)
			{
				m_pModel->VRecalculateWorldMatrix(m_pTransform->m_Position,
					m_pTransform->m_Rotation, m_pTransform->m_Size);
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