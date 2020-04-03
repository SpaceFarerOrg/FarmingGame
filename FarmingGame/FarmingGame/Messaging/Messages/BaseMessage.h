#pragma once

#include <SFML/Network.hpp>

#include <unordered_map>
#include <typeinfo>

#define REGISTER_NETWORKMSG(name) Message::MessageTypes[typeid(name).hash_code()] = (new name())

class Message
{
public:

	template<typename T>
	size_t GetHash()
	{
		return typeid(T).hash_code();
	}

	void SetHash(size_t hash)
	{
		id = hash;
	}

	enum class Category : sf::Uint8
	{
		NotGuaranteed = 0,
		Guaranteed = 1,
		Acknowledgement = 2
	};

	enum class Recipient : int
	{
		All = -1,
		SPECIFIC
	};

	struct ProtocolHeader
	{
		ProtocolHeader(sf::Packet& aPacket)
		{
			sf::Uint8 c;
			aPacket >> c;
			category = static_cast<Category>(c);
			aPacket >> uid;
		}

		ProtocolHeader(Category aCategory, size_t aUID)
		{
			category = aCategory;
			uid = aUID;
		}

		sf::Packet AsPacket()
		{
			sf::Packet packet;
			sf::Uint8 c = (sf::Uint8)category;
			packet << c << uid;
			return packet;
		}

		Category category;
		size_t uid;
	};

	static std::unordered_map<size_t, Message*> MessageTypes;
	static void RegisterNetworkMessages();

	virtual Message* Copy() = 0;

	virtual void Pack(sf::Packet& aPacket) const = 0;
	virtual void Unpack(sf::Packet& aPacket) = 0;

	sf::IpAddress sender;

	size_t id = 0;
};


// Internal Defines
#define MSG_DEFINE_SET_ID(name) id=typeid(name).hash_code()
#define MSG_DEFINE_COPY_FUNC(name) virtual Message* Copy() override { return new name(*this); }

/*
Define a message with no members
@name : The type name of the message
*/
#define DEFINE_MSG(name) class name : public Message \
{ public: \
name() { MSG_DEFINE_SET_ID(name); } \
MSG_DEFINE_COPY_FUNC(name) \
virtual void Pack( sf::Packet& OutPacket ) const override { OutPacket << id; } \
virtual void Unpack( sf::Packet& InPacket ) override {} \
}; \

/*
Define a message with one member
@name : The type name of the message
@type01 : The type of the member
@var01 : The name of the member
*/
#define DEFINE_MSG_ONE_PARAM(name, type01, var01) class name : public Message \
{ public: \
name() { MSG_DEFINE_SET_ID(name); } \
name(const type01& arg01) { MSG_DEFINE_SET_ID(name); var01=arg01; } \
type01 var01; \
MSG_DEFINE_COPY_FUNC(name) \
virtual void Pack(sf::Packet& aPacket) const override { aPacket << id << var01; } \
virtual void Unpack(sf::Packet& aPacket) override { aPacket >> var01; } \
}; \


/*
Define a message with two members
@name : The type name of the message
@type01 : The type of the first member
@var01 : The name of the first member
@type02 : The type of the second member
@var02 : The name of the second member
*/
#define DEFINE_MSG_TWO_PARAM( name, type01, var01, type02, var02 ) class name : public Message \
{ public: \
name() { MSG_DEFINE_SET_ID(name); } \
name( const type01& arg01, const type02& arg02 ) { MSG_DEFINE_SET_ID(name); var01=arg01; var02 = arg02; } \
type01 var01; \
type02 var02; \
MSG_DEFINE_COPY_FUNC(name) \
virtual void Pack( sf::Packet& OutPacket ) const override { OutPacket << id << var01 << var02; } \
virtual void Unpack( sf::Packet& InPacket ) override { InPacket >> var01 >> var02; } \
}; \

