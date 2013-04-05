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

// *****************************************************************************
cModelComponent::cModelComponent()
	: cBaseComponent("Model Component")
	, m_strModelName("")
	, m_pModel(NULL)
{
}

cModelComponent::~cModelComponent()
{
	VCleanup();
}

// *****************************************************************************
void cModelComponent::VInitialize()
{
	if (!m_strModelName.IsEmpty())
	{
		m_pModel = IModel::CreateModel(m_strModelName);
	}
}

// *****************************************************************************
void cModelComponent::VCleanup()
{
	SafeDelete(&m_pModel);
}
