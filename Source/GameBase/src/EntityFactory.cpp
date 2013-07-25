// *****************************************************************************
//  EntityFactory   version:  1.0   Ankur Sheel  date: 2013/05/06
// *****************************************************************************
//  purpose:	
// *****************************************************************************

#include "StdAfx.h"
#include "EntityFactory.h"

using namespace GameBase;

cEntityFactory * cEntityFactory::m_pInstance = NULL;

// *****************************************************************************
cEntityFactory::cEntityFactory()
{
	if(m_pInstance == NULL)
		m_pInstance = this;
}

// *****************************************************************************
cEntityFactory::~cEntityFactory()
{
}
