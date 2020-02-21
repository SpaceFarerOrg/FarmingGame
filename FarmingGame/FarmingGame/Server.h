#pragma once

#include <string>
#include <unordered_map>

#include "SFML/Network.hpp"
#include "Receiver.h"

namespace Network {

	class Server
	{
	public:
		Server(int aPort);
		~Server() = default;

		void Tick();

	private:

		struct SClient {
			std::string name;
		};
		std::unordered_map<int, SClient> clients;

		sf::UdpSocket socket;

		std::unique_ptr<Receiver> receiver;
	};
}