#include "stdafx.h"
#include "EntityMovedEventData.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cEntityMovedEventData::m_Name = cHashedString("eventactormoved");

// *****************************************************************************
cEntityMovedEventData::cEntityMovedEventData()
	: m_ActorID(0)
{
}

// *****************************************************************************
cEntityMovedEventData::cEntityMovedEventData(const Base::cVector3 & position,
	const int actorID)
	: m_ActorID(actorID)
	, m_Position(position)
{
}

// *****************************************************************************
cEntityMovedEventData::~cEntityMovedEventData()
{
}

