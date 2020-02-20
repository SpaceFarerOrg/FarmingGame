#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

// ----------------------------------------------------------------------

class CApplication
{
public:
	CApplication();
	void Tick();
private:
	sf::RenderWindow Window;
};

// ----------------------------------------------------------------------