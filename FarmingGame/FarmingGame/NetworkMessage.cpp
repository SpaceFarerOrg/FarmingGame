#include "NetworkMessage.h"

using namespace Network;

std::unordered_map<size_t, Message*> Network::Message::MessageTypes;

void Network::Message::RegisterNetworkMessages()
{
	//Network::Message::MessageTypes[typeid(ClientConnectMsg).hash_code()] = (new ClientConnectMsg());
	REGISTER_NETWORKMSG(ClientConnectMsg);
}
