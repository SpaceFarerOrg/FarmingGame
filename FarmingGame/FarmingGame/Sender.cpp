#include "Sender.h"
#include <algorithm>

Network::Sender::Sender(sf::UdpSocket& aSocket, std::shared_ptr<SenderReceiverBridge> receiverBridge, CNetworkMessageQueue& aNetworkQueue, int aSendPort) :
socket(aSocket),
sendPort(aSendPort),
receiverBridge(receiverBridge)
{
	aNetworkQueue.Subscribe<NetworkMessage>([this](const auto& msg) {
		Message::ProtocolHeader header(static_cast<Message::Category>(msg.category), getNextUID());
		sf::Packet packet = header.AsPacket();
		msg.Pack(packet);
		switch (static_cast<Message::Category>(msg.category))
		{
		case Message::Category::NotGuaranteed:
			if (msg.recipient != -1) {
				SendMessageToSpecific((sf::IpAddress)msg.recipient, packet);
			}
			else {
				SendMessageToAll(packet);
			}
			break;
		case Message::Category::Guaranteed:
			SendGuaranteedMessage((sf::IpAddress)msg.recipient, packet, header.uid);
			break;
		}
	}, subs);
}

Network::Sender::~Sender()
{
}

void Network::Sender::SendMessageToSpecific(const sf::IpAddress& to, const sf::Packet& packet)
{
	pendingSpecificMessages[to].emplace_back(packet);
}

void Network::Sender::SendMessageToAll(const sf::Packet& packet)
{
	pendingToAllMessages.emplace_back(packet);
}

void Network::Sender::SendGuaranteedMessage(const sf::IpAddress& to, const sf::Packet& packet, size_t uid)
{
	pendingGuaranteedMessages[to][uid] = packet;
}

size_t Network::Sender::getNextUID()
{
	const size_t MAX_ID = 16384;
	nexUID = nexUID >= MAX_ID ? 0 : ++nexUID;

	return nexUID;
}

void Network::Sender::Flush()
{
	for (auto& a : receiverBridge->GetOutgoingAcknowledgements())
	{
		const sf::IpAddress& address = a.first;
		const size_t uid = a.second;

		sf::Packet pack;

		Message::ProtocolHeader header(Message::Category::Acknowledgement, uid);

		pack = header.AsPacket();

		socket.send(pack, address, sendPort);
	}
	receiverBridge->ClearOutgoingAcknowledgements();

	for (auto& messages : pendingSpecificMessages)
	{
		const sf::IpAddress& address = messages.first;
		for (auto& message : messages.second) 
		{
			socket.send(message, address, sendPort);
		}
	}

	for (auto& message : pendingToAllMessages)
	{
		for (auto& address : allClients)
		{
			socket.send(message, address, sendPort);
		}
	}

	pendingSpecificMessages.clear();
	pendingToAllMessages.clear();
	
	for (auto& a : receiverBridge->GetIncomingAcknowledgements())
	{
		const sf::IpAddress& address = a.first;
		const size_t uid = a.second;

		if (pendingGuaranteedMessages.find(address) != pendingGuaranteedMessages.end())
		{
			auto& uids = pendingGuaranteedMessages.at(address);
			if (!uids.empty())
			{
				auto it = uids.find(uid);
				if (it != uids.end())
				{
					uids.erase(it);
				}
			}
			else
			{
				pendingGuaranteedMessages.erase(address);
			}
		}
	}
	receiverBridge->ClearIncomingAcknowledgements();

	for (auto& addresses : pendingGuaranteedMessages)
	{
		for (auto& address : addresses.second)
		{
			socket.send(address.second, addresses.first, sendPort);
		}
	}
}