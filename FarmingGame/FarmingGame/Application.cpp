#include "Application.h"

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, Renderer()
	, Context(Renderer.GetQueue())
	, Game()
{
	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 800;
	VideoMode.height = 800;

	Window.create(VideoMode, "FarmingGame");
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	const float DeltaTime = TickTimer.getElapsedTime().asSeconds();
	TickTimer.restart();

	Window.clear(sf::Color(50, 150, 250, 250));

	Game.Tick(Context, DeltaTime);

	Renderer.RunRender(Window);

	Window.display();
}

// ----------------------------------------------------------------------
