#include "Receiver.h"

#include "NetworkMessage.h"

#include "SFML/Network.hpp"
#include <type_traits>

#include <iostream>
#include <chrono>
#include <utility>

/*
	Packet structure:
	--HEADER-- 
	Category : sf::Uint8
	UID		 : size_t

	--MESSAGE--
	TypeID	 : size_t
	Rest is up to the converted Message to handle
*/


Network::Receiver::Receiver(sf::UdpSocket& aSocket, std::shared_ptr<SenderReceiverBridge> senderBridge, int aResponsePort) :
socket(aSocket),
responsePort(aResponsePort),
senderBridge(senderBridge)
{
}

Network::Receiver::~Receiver()
{
}

void Network::Receiver::Receive()
{
	sf::IpAddress sender;
	unsigned short port;
	sf::Packet packet;

	while (socket.receive(packet, sender, port) == sf::Socket::Done)
	{
		Message::ProtocolHeader header(packet);

		switch (header.category)
		{
		case Message::Category::Guaranteed:
			if (HandleGuaranteedMessage(header.uid, sender)) {
				return; // Already received
			}
			break;
		case Message::Category::Acknowledgement:
			senderBridge->AddIncomingAcknowledgement(header.uid, sender);
			return; // Acknowledgement
			break;
		case Message::Category::NotGuaranteed:
			break;
		default:
			std::cout << "RECEIVED A MESSAGE WITH AN UNKOWN CATEGORY: " << (sf::Uint8)header.category << std::endl;
			break;
		}

		size_t typeID;

		packet >> typeID;

		if (Message::MessageTypes.find(typeID) != Message::MessageTypes.end()) {
			messages.push_back(Message::MessageTypes[typeID]->Copy());
			auto& msg = messages.back();
			msg->Unpack(packet);
			msg->sender = sender;
		}
	}
}

void Network::Receiver::Clear()
{
	messages.clear();
}

bool Network::Receiver::HandleGuaranteedMessage(size_t uid, const sf::IpAddress& sender)
{
	senderBridge->AddOutgoingAcknowledgement(uid, sender);

	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	
	if (receivedGuaranteedBuffer.find(uid) != receivedGuaranteedBuffer.end())
	{
		auto latestReceivedTime = receivedGuaranteedBuffer.at(uid);
		if (timestamp.count() - latestReceivedTime < std::chrono::seconds(60).count()) {
			return true; // Has received this id within 60 seconds.
		}

	}

	receivedGuaranteedBuffer[uid] = timestamp.count();

	return false;
}