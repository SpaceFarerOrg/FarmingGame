#include "Client.h"
#include "NetworkMessage.h"
#include "SenderReceiverBridge.h"

Network::Client::Client(const std::string& aClientName, const sf::IpAddress& aServerIP, int aServerPort, CContextServiceProvider& InServiceProvider) :
	name(aClientName),
	serverIP(aServerIP),
	serverPort(aServerPort),
	ServiceProvider(InServiceProvider)
{
	CNetworkMessageQueue& NetworkMessageQueue = ServiceProvider.GetServiceRequired<CNetworkMessageQueue>();

	socket.bind(sf::Socket::AnyPort);
	socket.setBlocking(false);

	auto bridge = std::make_shared<SenderReceiverBridge>();
	receiver = std::make_unique<Receiver>(socket, bridge, ServiceProvider, serverPort);
	sender = std::make_unique<Sender>(socket, bridge, NetworkMessageQueue, serverPort);

	sf::Packet test;

	NetworkMessageQueue.DispatchEvent<NetworkMessage>(Message::Category::Guaranteed, aServerIP, aClientName);
}

void Network::Client::Tick()
{
	receiver->Receive();

	receiver->Clear();

	sender->Flush();
}
