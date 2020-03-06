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


#define DEFINE_MSG(NAME) struct NAME : public SS::SBaseMessage { NAME(){} };
#define DEFINE_MSG_ONEPARAM(NAME, PARAMTYPE) struct NAME : public SS::SBaseMessage { NAME(const PARAMTYPE& InParam) : Param(InParam) {} PARAMTYPE Param; };
#define DEFINE_MSG_TWOPARAM(NAME, PARAMTYPE, PARAMTYPETWO) struct NAME : public SS::SBaseMessage { NAME(const PARAMTYPE& InParam, const PARAMTYPETWO& InParamTwo) : Param(InParam), ParamTwo(InParamTwo) {} PARAMTYPE Param; PARAMTYPETWO ParamTwo; };
#define DEFINE_MSG_THREEPARAM(NAME, PARAMTYPE, PARAMTYPETWO, PARAMTYPETHREE) struct NAME : public SS::SBaseMessage { NAME(const PARAMTYPE& InParam, const PARAMTYPETWO& InParamTwo, const PARAMTYPETHREE& InParamThree) : Param(InParam), ParamTwo(InParamTwo), ParamThree(InParamThree) {} PARAMTYPE Param; PARAMTYPETWO ParamTwo; PARAMTYPETHREE ParamThree; };
