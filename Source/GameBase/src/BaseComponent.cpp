// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "BaseComponent.h"

using namespace GameBase;
using namespace Base;

// *****************************************************************************
cBaseComponent::cBaseComponent(const cString & strComponentName)
	: m_strComponentName(cHashedString(strComponentName))
	, m_pOwner(NULL)
{
}

// *****************************************************************************
cBaseComponent::~cBaseComponent()
{
}

// *****************************************************************************
cString cBaseComponent::GetName() const
{
	return m_strComponentName.GetString();
}

// *****************************************************************************
void cBaseComponent::VInitialize()
{

}

// *****************************************************************************
void cBaseComponent::VCleanup()
{

}

// *****************************************************************************
unsigned long cBaseComponent::VGetID() const
{
	return m_strComponentName.GetHash();
}

// *****************************************************************************
void cBaseComponent::VSetOwner(const IBaseEntity * const pNewOwner)
{
	m_pOwner = pNewOwner;
}
