#pragma once

#include <string>
#include <unordered_map>

#include "SFML/Network.hpp"
#include "Receiver.h"
#include "Sender.h"
#include "AppContext.h"

namespace Network {

	class Server
	{
	public:
		Server(int aPort, SAppContext& appContext);
		~Server() = default;

		void Tick();

	private:

		struct SClient {
			std::string name;
		};
		std::unordered_map<int, SClient> clients;

		sf::UdpSocket socket;

		std::unique_ptr<Receiver> receiver;
		std::unique_ptr<Sender> sender;

		SAppContext& context;
	};
}