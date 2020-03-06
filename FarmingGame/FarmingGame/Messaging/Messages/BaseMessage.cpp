#include "BaseMessage.h"
#include "../../NetworkMessage.h"

std::unordered_map<size_t, Message*> Message::MessageTypes;

void Message::RegisterNetworkMessages()
{
	//Network::Message::MessageTypes[typeid(ClientConnectMsg).hash_code()] = (new ClientConnectMsg());
	REGISTER_NETWORKMSG(Network::NetworkMessage);
}

