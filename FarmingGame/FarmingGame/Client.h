#pragma once
#include "SFML/Network.hpp"
#include "Receiver.h"
#include "Sender.h"

#include "ContextServiceProvider.h"

namespace Network {
	class Client
	{
	public:
		Client(const std::string& aClientName, const sf::IpAddress& aServerIP, int aServerPort, CContextServiceProvider& InServiceProvider);
		~Client() = default;

		void Tick();

	private:

		std::string name;
		sf::IpAddress serverIP;
		int serverPort;

		sf::UdpSocket socket;
		std::unique_ptr<Receiver> receiver;
		std::unique_ptr<Sender> sender;

		CContextServiceProvider& ServiceProvider;
	};
}