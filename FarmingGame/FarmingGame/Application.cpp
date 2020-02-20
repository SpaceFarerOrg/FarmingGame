#include "Application.h"

// ----------------------------------------------------------------------

CApplication::CApplication()
{
	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 800;
	VideoMode.height = 800;

	Window.create(VideoMode, "FarmingGame");
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	Window.clear(sf::Color(50, 150, 250, 250));

	Window.display();
}

// ----------------------------------------------------------------------
