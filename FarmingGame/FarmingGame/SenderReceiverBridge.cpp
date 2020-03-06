#include "SenderReceiverBridge.h"

Network::SenderReceiverBridge::SenderReceiverBridge()
{
}

Network::SenderReceiverBridge::~SenderReceiverBridge()
{
}

void Network::SenderReceiverBridge::AddOutgoingAcknowledgement(size_t uid, const sf::IpAddress& to)
{
	outgoingAcknowledgements.insert(std::make_pair(to, uid));
}

void Network::SenderReceiverBridge::ClearOutgoingAcknowledgements()
{
	outgoingAcknowledgements.clear();
}

void Network::SenderReceiverBridge::AddIncomingAcknowledgement(size_t uid, const sf::IpAddress& to)
{
	incomingAcknowledgements.insert(std::make_pair(to, uid));
}

void Network::SenderReceiverBridge::ClearIncomingAcknowledgements()
{
	incomingAcknowledgements.clear();
}
