#include "stdafx.h"
#include "EventManager.h"
#include "EventFactory.h"

using namespace GameBase;
using namespace Base;
using namespace Utilities;

cEventManager * cEventManager::s_pEventManager = NULL;

// *****************************************************************************
cEventManager::cEventManager()
	: m_activeQueue(0)
{
}

// *****************************************************************************
cEventManager::~cEventManager()
{
}

// *****************************************************************************
void cEventManager::VInitializeEventFactory(shared_ptr<cEventFactory> pEventFactory)
{
	if(m_pEventFactory == NULL && pEventFactory != NULL)
	{
		m_pEventFactory = pEventFactory;
		m_pEventFactory->VRegisterEvents();
	}
}

// *****************************************************************************
void cEventManager::VAddListener(const EventListenerCallBackFn & fnListener,
	const EventType & eventType)
{
	Log_Write(ILogger::LT_EVENT, 2, "Attempting to add listener for event " + eventType.GetString());
	
	EventListenerList & eventListeners = m_eventListeners[eventType.GetHash()];

    for (auto it = eventListeners.begin(); it != eventListeners.end(); it++)
    {
		if (fnListener.target_type() == (*it).target_type())
        {
			Log_Write(ILogger::LT_WARNING, 2, "Attempting to double-register a listener for event " + eventType.GetString());
            return;
        }
    }

	eventListeners.push_back(fnListener);
	Log_Write(ILogger::LT_EVENT, 2, "Successfully added delegate for event type " + eventType.GetString());
}

// *****************************************************************************
void cEventManager::VRemoveListener(const EventListenerCallBackFn & fnListener,
	const EventType & eventType)
{
	bool success = false;
	Log_Write(ILogger::LT_EVENT, 2, "Attempting to remove delegate function from event type " + eventType.GetString());
	
	EventListenerList & eventListeners = m_eventListeners[eventType.GetHash()];

	auto findIt = m_eventListeners.find(eventType.GetHash());
    if (findIt != m_eventListeners.end())
	{
		EventListenerList & listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); it++)
		{
			if (fnListener == (*it))
			{
				listeners.erase(it);
				Log_Write(ILogger::LT_EVENT, 2, "Successfully removed delegate for event type " + eventType.GetString());
				return;
			}
		}
	}

	if(!success)
	{
		Log_Write(ILogger::LT_WARNING, 2, "Attempting to double-register a listener for event " + eventType.GetString());
	}
}

// *****************************************************************************
void cEventManager::VTriggerEvent(const IEventDataPtr & pEvent)
{
	Log_Write(ILogger::LT_EVENT, 2, "Attempting to trigger event  " + pEvent->VGetEventName());

    auto findIt = m_eventListeners.find(pEvent->VGetEventID());
	if (findIt != m_eventListeners.end())
    {
	    const EventListenerList& eventListenerList = findIt->second;
	    for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
	    {
		    EventListenerCallBackFn listener = (*it);
		    listener(pEvent);
	    }
    }
}

// *****************************************************************************
void cEventManager::VQueueEvent(const IEventDataPtr & pEvent)
{
    // make sure the event is valid
    if (!pEvent)
    {
        Log_Write(ILogger::LT_ERROR, 1, "Invalid event in VQueueEvent()");
        return;
    }

    Log_Write(ILogger::LT_EVENT, 2, "Attempting to queue event: " + pEvent->VGetEventName());

	auto findIt = m_eventListeners.find(pEvent->VGetEventID());
    if (findIt != m_eventListeners.end())
    {
        m_queues[m_activeQueue].push_back(pEvent);
    }
    else
    {
		Log_Write(ILogger::LT_EVENT, 2, "Skipping event since there are no delegates registered to receive it: " + pEvent->VGetEventName());
    }
}

// *****************************************************************************
void cEventManager::VAbortEvent(const EventType & eventType, const bool allEVents)
{
	EventListenerMap::iterator findIt = m_eventListeners.find(eventType.GetHash());

	if (findIt != m_eventListeners.end())
    {
        EventQueue& eventQueue = m_queues[m_activeQueue];
        auto it = eventQueue.begin();
        while (it != eventQueue.end())
        {
            // Removing an item from the queue will invalidate the iterator, so have it point to the next member.  All
            // work inside this loop will be done using thisIt.
            auto thisIt = it;
            ++it;

			if ((*thisIt)->VGetEventID() == eventType.GetHash())
	        {
		        eventQueue.erase(thisIt);
		        if (!allEVents)
			        break;
	        }
        }
    }
}

// *****************************************************************************
void cEventManager::VUpdate(const TICK tickCurrent, const float fElapsedTime)
{
	// swap active queues and clear the new queue after the swap
    int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % 2;
	m_queues[m_activeQueue].clear();

	// Process the queue
	while (!m_queues[queueToProcess].empty())
	{
        // pop the front of the queue
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
        m_queues[queueToProcess].pop_front();
		Log_Write(ILogger::LT_EVENT, 2 , "Processing Event : " + pEvent->VGetEventName());

        // find all the delegate functions registered for this event
		auto findIt = m_eventListeners.find(pEvent->VGetEventID());
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			// call each listener
			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
                EventListenerCallBackFn listener = (*it);
				listener(pEvent);
			}
		}
	}
}


// *****************************************************************************
IEventManager * IEventManager::Instance()
{
	if(cEventManager::s_pEventManager == NULL)
		cEventManager::s_pEventManager = DEBUG_NEW cEventManager();
	return cEventManager::s_pEventManager;

}

// *****************************************************************************
void IEventManager::Destroy()
{
	SafeDelete(&cEventManager::s_pEventManager);
}