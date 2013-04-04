// *****************************************************************************
//  ComponentCreator version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#include "stdafx.h"
#include "ComponentCreator.h"
#include "ModelComponent.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cComponentCreator * cComponentCreator::s_pComponentCreator = NULL;

// *****************************************************************************
cComponentCreator::cComponentCreator()
{
}

// *****************************************************************************
cComponentCreator::~cComponentCreator()
{
}

// *****************************************************************************
IBaseComponent * cComponentCreator::CreateComponent(const Base::cString & strComponentName)
{
	if(strComponentName.CompareInsensitive("ModelComponent"))
	{
		return DEBUG_NEW cModelComponent();
	}
	Log_Write(ILogger::LT_ERROR, 1, strComponentName + " : No component of this type");
	return NULL;
}


// *****************************************************************************
cComponentCreator * cComponentCreator::GetInstance()
{
	if(cComponentCreator::s_pComponentCreator == NULL)
		cComponentCreator::s_pComponentCreator = DEBUG_NEW cComponentCreator();
	return cComponentCreator::s_pComponentCreator;
}

// *****************************************************************************
void cComponentCreator::Destroy()
{
	SafeDelete(&cComponentCreator::s_pComponentCreator);
}