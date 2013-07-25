#include "stdafx.h"
#include "ActorMovedEventData.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

Base::cHashedString	cActorMovedEventData::m_Name = cHashedString("eventactormoved");

// *****************************************************************************
cActorMovedEventData::cActorMovedEventData()
	: m_ActorID(0)
{
}

// *****************************************************************************
cActorMovedEventData::cActorMovedEventData(const Base::cVector3 & position,
	const int actorID)
	: m_ActorID(actorID)
	, m_Position(position)
{
}

// *****************************************************************************
cActorMovedEventData::~cActorMovedEventData()
{
}

