#pragma once

#include <map>
#include "SFML/Network/IpAddress.hpp"

namespace Network
{
	class SenderReceiverBridge
	{
	public:
		SenderReceiverBridge();
		~SenderReceiverBridge();

		const std::map<sf::IpAddress, size_t>& GetOutgoingAcknowledgements() { return outgoingAcknowledgements; };
		const std::map<sf::IpAddress, size_t>& GetIncomingAcknowledgements() { return incomingAcknowledgements; };

		void AddOutgoingAcknowledgement(size_t uid, const sf::IpAddress& to);
		void ClearOutgoingAcknowledgements();

		void AddIncomingAcknowledgement(size_t uid, const sf::IpAddress& to);
		void ClearIncomingAcknowledgements();

	private:

		std::map<sf::IpAddress, size_t> outgoingAcknowledgements;
		std::map<sf::IpAddress, size_t> incomingAcknowledgements;
	};
}