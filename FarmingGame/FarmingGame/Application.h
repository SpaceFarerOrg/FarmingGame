#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "StateStack.h"

#include "Renderer.h"

#include "Server.h"
#include "Client.h"

#include "ContextServiceProvider.h"

// ----------------------------------------------------------------------

class CApplication
{
public:
	CApplication();
	
	bool GetShouldRun() const;

	void Tick();
private:
	void HandleWindowEvents();

	void RegisterServices();

	sf::RenderWindow Window;
	sf::Clock TickTimer;

	CContextServiceProvider ServiceProvider;

	std::unique_ptr<Network::Server> Server;
	std::unique_ptr<Network::Client> Client;

	CRenderer Renderer;

	CStateStack StateStack;

	bool ShouldRun;
};

// ----------------------------------------------------------------------