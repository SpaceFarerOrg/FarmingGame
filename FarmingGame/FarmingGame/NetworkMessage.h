#pragma once
#include "SFML/Config.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/IpAddress.hpp"

#include <iostream>
#include <type_traits>
#include <unordered_map>

#define REGISTER_NETWORKMSG(name) Network::Message::MessageTypes[typeid(name).hash_code()] = (new name())

namespace Network {

	class Message
	{
	public:

		static std::unordered_map<size_t, Message*> MessageTypes;
		static void RegisterNetworkMessages();

		virtual Message* Copy() = 0;

		virtual void Pack(sf::Packet& aPacket) = 0;
		virtual void Unpack(sf::Packet& aPacket) = 0;

		sf::IpAddress sender;

		size_t id = 0;
	};

	class ClientConnectMsg : public Message
	{
	public:

		ClientConnectMsg() { id = typeid(ClientConnectMsg).hash_code(); }

		virtual Message* Copy() override {
			return new std::remove_pointer<decltype(this)>::type(*this);
		};

		virtual void Pack(sf::Packet& aPacket) override {
			aPacket << id;
			aPacket << name;
		}

		virtual void Unpack(sf::Packet& aPacket) override {
			aPacket >> name;
			//auto err = (aPacket >> name);
			std::cout << "Hello" << std::endl;
		};

		std::string name;
	};
}