#include "Subscriptions.h"

//------------------------------------------------------------------

CSubscriptions::CSubscriptions()
	: Handles()
{
}

//------------------------------------------------------------------

CSubscriptions::~CSubscriptions()
{
	for (SSubscriptionHandle& Handle : Handles)
	{
		Handle.Unregister();
	}
}

//------------------------------------------------------------------

void CSubscriptions::AddSubscription(const SSubscriptionHandle& InHandle)
{
	Handles.push_back(InHandle);
}

//------------------------------------------------------------------