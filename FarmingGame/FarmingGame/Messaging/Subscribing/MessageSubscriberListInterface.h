#pragma once

#include "../Messages/BaseMessage.h"
#include <functional>

struct SSubscriptionHandle;

class IMessageSubscriberList
{
public:
	virtual void Unsubscribe(const SSubscriptionHandle& InHandle) = 0;
	virtual void DispatchToAllSubscribers(const Message* InEvent) = 0;
};