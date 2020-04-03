#include "BaseMessage.h"
#include "../../NetworkMessage.h"
#include "../../SharedGameplayMessages.h"

std::unordered_map<size_t, Message*> Message::MessageTypes;

void Message::RegisterNetworkMessages()
{
	//Network::Message::MessageTypes[typeid(ClientConnectMsg).hash_code()] = (new ClientConnectMsg());
	REGISTER_NETWORKMSG(Network::NetworkMessage);

	REGISTER_NETWORKMSG(DiceRoll); //Message for dice roll requests and completions, holds unsigned short for dice roll value
}

