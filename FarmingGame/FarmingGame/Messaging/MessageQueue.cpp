#include "MessageQueue.h"

//------------------------------------------------------------------

void CMessageQueue::Unsubscribe(const SSubscriptionHandle& InHandle)
{
	if (ContainsSubscriberListOfType(InHandle.GetMessageType()))
	{
		PerEventSubscribers[InHandle.GetMessageType()]->Unsubscribe(InHandle);
	}
}

//------------------------------------------------------------------

void CMessageQueue::DispatchEvent(Message* InMessage)
{
	EventQueue.push(InMessage);
}

void CMessageQueue::SendAllEvents()
{
	while (!EventQueue.empty())
	{
		Message* Event = EventQueue.front();
		if (ContainsSubscriberListOfType(Event->id))
		{
			PerEventSubscribers[Event->id]->DispatchToAllSubscribers(Event);
		}
		delete Event;
		EventQueue.pop();
	}
}

//------------------------------------------------------------------

bool CMessageQueue::ContainsSubscriberListOfType(size_t InTypeHash) const
{
	if (PerEventSubscribers.size() == 0)
	{
		return false;
	}

	const auto& NotFound = PerEventSubscribers.end();
	return (PerEventSubscribers.find(InTypeHash) != NotFound);
}