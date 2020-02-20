#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "AppContext.h"
#include "Renderer.h"
#include "Game.h"

// ----------------------------------------------------------------------

class CApplication
{
public:
	CApplication();
	void Tick();
private:
	sf::RenderWindow Window;
	sf::Clock TickTimer;
	CRenderer Renderer;
	SAppContext Context;
	CGame Game;
};

// ----------------------------------------------------------------------