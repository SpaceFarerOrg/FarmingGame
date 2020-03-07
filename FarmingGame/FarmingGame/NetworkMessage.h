#pragma once
#include "SFML/Config.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/IpAddress.hpp"

#include "Messaging/Messages/BaseMessage.h"
#include "Networking.h"

#include <iostream>
#include <type_traits>
#include <unordered_map>

namespace Network {

	class NetworkMessage : public Message
	{
	public:

		NetworkMessage() { id = typeid(NetworkMessage).hash_code(); }
		NetworkMessage(Message::Category category, sf::IpAddress to, const std::string& name) { this->category = (sf::Uint8)category; this->recipient = to.toInteger(); this->name = name; }

		virtual Message* Copy() override {return new std::remove_pointer<decltype(this)>::type(*this);};

		virtual void Pack(sf::Packet& aPacket) const override {
			aPacket << id;
			aPacket << category;
			aPacket << name;
		}

		virtual void Unpack(sf::Packet& aPacket) override {
			aPacket >> category >> name;
		};

		sf::Uint8 category;
		std::string name;

		int recipient;
	};
}