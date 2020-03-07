#include "Server.h"
#include "SenderReceiverBridge.h"

Network::Server::Server(int aPort, SAppContext& appContext) : 
	context(appContext)
{
	socket.bind(aPort);
	socket.setBlocking(false);

	auto bridge = std::make_shared<SenderReceiverBridge>();
	receiver = std::make_unique<Receiver>(socket, bridge, appContext);
	sender = std::make_unique<Sender>(socket, bridge, appContext.NetworkQueue);

	context.MessageQueue.Subscribe<NetworkMessage>([this](const auto& msg) {
		std::cout << "HEllo " << msg.name << std::endl;
	}, subs);
}

void Network::Server::Tick()
{
	receiver->Receive();

	for (auto& msg : receiver->GetReceivedMessages()) {
		if (auto client = dynamic_cast<NetworkMessage*>(msg)) {
			//std::cout << "Client: \"" << client-> << "\" connected!" << std::endl;
		}
	}

	receiver->Clear();

	sender->Flush();
}
