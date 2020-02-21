#include "Client.h"
#include "NetworkMessage.h"

Network::Client::Client(const std::string aClientName, const sf::IpAddress& aServerIP, int aServerPort) :
name(aClientName),
serverIP(aServerIP),
serverPort(aServerPort)
{
	socket.bind(sf::Socket::AnyPort);
	socket.setBlocking(false);
	receiver = std::make_unique<Receiver>(socket);

	sf::Packet test;

	ClientConnectMsg msg;
	msg.name = "Joknom";
	msg.Pack(test);
	socket.send(test, aServerIP, aServerPort);
}

void Network::Client::Tick()
{
	receiver->Receive();

	for (auto& msg : receiver->GetReceivedMessages()) {

	}

	receiver->Flush();
}
