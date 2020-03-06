#pragma once
#include "SFML/Config.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/IpAddress.hpp"

#include "Messaging/Messages/BaseMessage.h"

#include <iostream>
#include <type_traits>
#include <unordered_map>

namespace Network {

	class NetworkMessage : public Message
	{
	public:

		NetworkMessage() { id = typeid(NetworkMessage).hash_code(); }
		NetworkMessage(sf::Uint8 category, int to) { this->category = category; this->recipient = to; }

		virtual Message* Copy() override {
			return new std::remove_pointer<decltype(this)>::type(*this);
		};

		virtual void Pack(sf::Packet& aPacket) const override {
			aPacket << id;
			aPacket << category;
		}

		virtual void Unpack(sf::Packet& aPacket) override {
			aPacket >> category;
		};

		sf::Uint8 category;
		int recipient;
	};
}