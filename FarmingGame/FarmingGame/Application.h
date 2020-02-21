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
	
	bool GetShouldRun() const;

	void Tick();
private:
	void HandleWindowEvents();

	sf::RenderWindow Window;
	sf::Clock TickTimer;

	// Rendering
	CRenderer Renderer;
	CTextureBank TextureBank;

	SAppContext Context;
	CGame Game;

	bool ShouldRun;
};

// ----------------------------------------------------------------------