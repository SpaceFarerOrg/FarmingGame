#pragma once

#include "SubscriptionHandle.h"
#include <vector>

class CSubscriptions
{
public:
	CSubscriptions();
	~CSubscriptions();
	void AddSubscription(const SSubscriptionHandle& InHandle);
private:
	std::vector<SSubscriptionHandle> Handles;

};