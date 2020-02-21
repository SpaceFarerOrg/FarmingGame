#include "Application.h"

#include <SFML/Window/Event.hpp>

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, Renderer()
	, TextureBank()
	, Context(Renderer.GetQueue(), TextureBank)
	, Game()
	, ShouldRun(true)
{
	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 1920;
	VideoMode.height = 1080;

	Context.WindowDimensions = sf::Vector2u(VideoMode.width, VideoMode.height);

	Window.create(VideoMode, "FarmingGame");

	Game.Startup(Context);
}

// ----------------------------------------------------------------------

bool CApplication::GetShouldRun() const
{
	return ShouldRun;
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	const float DeltaTime = TickTimer.getElapsedTime().asSeconds();
	TickTimer.restart();

	HandleWindowEvents();

	Window.clear(sf::Color(50, 150, 250, 250));

	Game.Tick(Context, DeltaTime);

	Renderer.RunRender(Window);

	Window.display();
}

// ----------------------------------------------------------------------

void CApplication::HandleWindowEvents()
{
	sf::Event Event;
	while (Window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			ShouldRun = false;
		}
	}
}

// ----------------------------------------------------------------------
