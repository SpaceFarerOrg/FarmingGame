#include "Client.h"
#include "NetworkMessage.h"
#include "SenderReceiverBridge.h"

Network::Client::Client(const std::string& aClientName, const sf::IpAddress& aServerIP, int aServerPort, SAppContext& appContext) :
name(aClientName),
serverIP(aServerIP),
serverPort(aServerPort),
context(appContext)
{
	socket.bind(sf::Socket::AnyPort);
	socket.setBlocking(false);

	auto bridge = std::make_shared<SenderReceiverBridge>();
	receiver = std::make_unique<Receiver>(socket, bridge, context, serverPort);
	sender = std::make_unique<Sender>(socket, bridge, context.NetworkQueue, serverPort);

	sf::Packet test;

	context.NetworkQueue.DispatchEvent<NetworkMessage>(Message::Category::Guaranteed, aServerIP, aClientName);
}

void Network::Client::Tick()
{
	receiver->Receive();

	for (auto& msg : receiver->GetReceivedMessages()) {
		
	}

	receiver->Clear();

	sender->Flush();
}
