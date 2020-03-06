#pragma once

class CMessageQueue;

struct SSubscriptionHandle
{
public:
	SSubscriptionHandle();
	SSubscriptionHandle(size_t InIdentifier, size_t InMessageType, CMessageQueue* InParent);
	void operator=(const SSubscriptionHandle& InRHS);

	void Unregister();

	size_t GetIdentifier() const;
	size_t GetMessageType() const;
private:
	CMessageQueue* Parent;
	size_t Identifier;
	size_t MessageType;
};