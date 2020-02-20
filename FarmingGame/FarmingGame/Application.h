#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "AppContext.h"
#include "Renderer.h"
#include "TextureBank.h"
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

	// Rendering
	CRenderer Renderer;
	CTextureBank TextureBank;

	SAppContext Context;
	CGame Game;
};

// ----------------------------------------------------------------------