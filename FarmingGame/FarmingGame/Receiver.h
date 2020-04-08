#pragma once
#include "SFML/Network/UdpSocket.hpp"
#include "NetworkMessage.h"
#include "SenderReceiverBridge.h"
#include "ContextServiceProvider.h"

#include <map>
#include <set>

namespace Network {
	class Receiver
	{
	public:
		Receiver(sf::UdpSocket& aSocket, std::shared_ptr<SenderReceiverBridge> senderBridge, CContextServiceProvider& InServiceProvider, int aResponsePort = sf::Socket::AnyPort);
		~Receiver();

		std::vector<Message*>& GetReceivedMessages() { return messages; }

		void Receive();
		void Clear();

	private:

		bool HandleGuaranteedMessage(size_t uid, const sf::IpAddress& sender);

		CContextServiceProvider& ServiceProvider;
		sf::UdpSocket& socket;
		std::vector<Message*> messages;
		int responsePort;

		//				  <uid, timestamp>
		std::map<size_t, long long> receivedGuaranteedBuffer;

		std::shared_ptr<SenderReceiverBridge> senderBridge;
	};
}