#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "AppContext.h"
#include "Renderer.h"
#include "TextureBank.h"
#include "StateStack.h"

#include "Server.h"
#include "Client.h"

// ----------------------------------------------------------------------

class CApplication
{
public:
	CApplication();
	
	bool GetShouldRun() const;

	void Tick();
private:
	void HandleWindowEvents();

	sf::RenderWindow Window;
	sf::Clock TickTimer;

	// Rendering
	CRenderer Renderer;
	CTextureBank TextureBank;

	// Messaging
	CMessageQueue MessageQueue;

	// Networking
	CNetworkMessageQueue NetworkQueue;
	std::unique_ptr<Network::Server> Server;
	std::unique_ptr<Network::Client> Client;

	SAppContext Context;

	CStateStack StateStack;



	bool ShouldRun;
};

// ----------------------------------------------------------------------