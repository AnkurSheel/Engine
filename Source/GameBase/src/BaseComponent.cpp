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
cBaseComponent::cBaseComponent()
	: m_pOwner(NULL)
{
}

// *****************************************************************************
cBaseComponent::~cBaseComponent()
{
}

// *****************************************************************************
unsigned long cBaseComponent::VGetID() const
{
	return VGetHashedID();
}

// *****************************************************************************
void cBaseComponent::VSetOwner(const IBaseEntity * const pNewOwner)
{
	m_pOwner = pNewOwner;
}
