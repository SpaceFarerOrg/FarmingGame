#pragma once
#include "SFML/Network/UdpSocket.hpp"
#include "SFML/Network/IpAddress.hpp"
#include "NetworkMessage.h"
#include "SenderReceiverBridge.h"
#include "NetworkMessageQueue.h"

#include "Messaging/Subscribing/Subscriptions.h"

#include <vector>
#include <set>
#include <map>
#include <unordered_map>

namespace Network {
	class Sender
	{
	public:
		Sender(sf::UdpSocket& aSocket, std::shared_ptr<SenderReceiverBridge> receiverBridge, CNetworkMessageQueue& aNetworkQueue, int aSendPort = sf::Socket::AnyPort);
		~Sender();

		void Flush();

	private:

		void SendMessageToSpecific(const sf::IpAddress& to, const sf::Packet& packet);
		void SendMessageToAll(const sf::Packet& packet);
		void SendGuaranteedMessage(const sf::IpAddress& to, const sf::Packet& packet, size_t uid);

		size_t getNextUID();

		size_t nexUID = 0;

		CSubscriptions subs;

		std::set<sf::IpAddress> allClients;

		std::map<sf::IpAddress, std::map<size_t, sf::Packet>> pendingGuaranteedMessages;
		std::vector<sf::Packet> pendingToAllMessages;
		std::map<sf::IpAddress, std::vector<sf::Packet>> pendingSpecificMessages;

		sf::UdpSocket& socket;
		int sendPort;

		std::shared_ptr<SenderReceiverBridge> receiverBridge;
	};
}