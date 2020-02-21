#pragma once
#include "SFML/Network/UdpSocket.hpp"
#include "NetworkMessage.h"

#include <unordered_map>

namespace Network {
	class Receiver
	{
	public:
		Receiver(sf::UdpSocket& aSocket);
		~Receiver();

		std::vector<Message*>& GetReceivedMessages() { return messages; }

		void Receive();
		void Flush();

	private:

		enum MessageType {
			INTEGER,
			STRING,
			FLOAT,
			// Add more as needed, e.g. 2FLOAT etc..
		};

		sf::UdpSocket& socket;
		std::vector<Message*> messages;
	};
}