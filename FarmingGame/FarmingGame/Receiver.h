#pragma once
#include "SFML/Network/UdpSocket.hpp"
#include "NetworkMessage.h"
#include "SenderReceiverBridge.h"
#include "AppContext.h"

#include <map>
#include <set>

namespace Network {
	class Receiver
	{
	public:
		Receiver(sf::UdpSocket& aSocket, std::shared_ptr<SenderReceiverBridge> senderBridge, SAppContext& appContext, int aResponsePort = sf::Socket::AnyPort);
		~Receiver();

		std::vector<Message*>& GetReceivedMessages() { return messages; }

		void Receive();
		void Clear();

	private:

		bool HandleGuaranteedMessage(size_t uid, const sf::IpAddress& sender);

		SAppContext& context;
		sf::UdpSocket& socket;
		std::vector<Message*> messages;
		int responsePort;

		//				  <uid, timestamp>
		std::map<size_t, long long> receivedGuaranteedBuffer;

		std::shared_ptr<SenderReceiverBridge> senderBridge;
	};
}