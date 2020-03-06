#include "Application.h"

#include "GameState.h"

#include <SFML/Window/Event.hpp>

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, Renderer()
	, TextureBank()
	, Context(Renderer.GetQueue(), TextureBank)
	, StateStack(Context)
	, ShouldRun(true)
{
	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 1920;
	VideoMode.height = 1080;

	Context.WindowDimensions = sf::Vector2u(VideoMode.width, VideoMode.height);

	Window.create(VideoMode, "FarmingGame");

	StateStack.PushState(new CGameState());

}

// ----------------------------------------------------------------------

bool CApplication::GetShouldRun() const
{
	return !StateStack.IsEmpty();
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	const float DeltaTime = TickTimer.getElapsedTime().asSeconds();
	TickTimer.restart();

	HandleWindowEvents();

	Window.clear(sf::Color(50, 150, 250, 250));

	StateStack.Tick(DeltaTime);
	StateStack.Draw();

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
