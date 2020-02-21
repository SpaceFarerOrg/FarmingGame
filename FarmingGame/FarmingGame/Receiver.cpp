#include "Receiver.h"
#include "SFML/Network.hpp"
#include <type_traits>


Network::Receiver::Receiver(sf::UdpSocket& aSocket) :
socket(aSocket)
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
		size_t id;

		packet >> id;

		if (Message::MessageTypes.find(id) != Message::MessageTypes.end()) {
			messages.push_back(Message::MessageTypes[id]->Copy());
			auto& msg = messages.back();
			msg->Unpack(packet);
			msg->sender = sender;
		}
	}
}

void Network::Receiver::Flush()
{
	messages.clear();
}
