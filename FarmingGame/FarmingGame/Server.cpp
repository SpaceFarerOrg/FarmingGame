#include "Server.h"

Network::Server::Server(int aPort)
{
	socket.bind(aPort);
	socket.setBlocking(false);

	receiver = std::make_unique<Receiver>(socket);
}

void Network::Server::Tick()
{
	receiver->Receive();

	for (auto& msg : receiver->GetReceivedMessages()) {
		if (auto client = dynamic_cast<ClientConnectMsg*>(msg)) {
			std::cout << "Client: \"" << client->name << "\" connected!" << std::endl;
		}
	}

	receiver->Flush();
}
