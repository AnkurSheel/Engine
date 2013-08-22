#include "stdafx.h"
#include "EntityInitializedEventData.h"

using namespace GameBase;
using namespace Base;

cHashedString	cEntityInitializedEventData::m_Name = cHashedString("evententityinitialized");

// *****************************************************************************
cEntityInitializedEventData::cEntityInitializedEventData()
	: m_ActorID(0)
{
}

// *****************************************************************************
cEntityInitializedEventData::cEntityInitializedEventData(const cVector3 & position,
	const cVector3 & rotation, const Base::cVector3 & size, const int actorID)
	: m_ActorID(actorID)
	, m_Position(position)
	, m_Rotation(rotation)
	, m_Size(size)
{
}

// *****************************************************************************
cEntityInitializedEventData::~cEntityInitializedEventData()
{
}