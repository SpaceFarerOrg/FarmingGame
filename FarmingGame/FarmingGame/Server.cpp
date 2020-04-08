#include "Server.h"
#include "SenderReceiverBridge.h"

#include "Messaging/MessageQueue.h"
#include "NetworkMessageQueue.h"

Network::Server::Server(int aPort, CContextServiceProvider& InServiceProvider) 
	: ServiceProvider(InServiceProvider)
{
	socket.bind(aPort);
	socket.setBlocking(false);

	auto bridge = std::make_shared<SenderReceiverBridge>();
	receiver = std::make_unique<Receiver>(socket, bridge, InServiceProvider);
	sender = std::make_unique<Sender>(socket, bridge, InServiceProvider.GetServiceRequired<CNetworkMessageQueue>());

	ServiceProvider.GetServiceRequired<CMessageQueue>().Subscribe<NetworkMessage>([this](const auto& msg) {
		std::cout << "HEllo " << msg.name << std::endl;
	}, subs);
}

void Network::Server::Tick()
{
	receiver->Receive();


	receiver->Clear();

	sender->Flush();
}
