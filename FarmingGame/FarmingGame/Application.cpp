#include "Application.h"

#include "GameState.h"
#include "NetworkMessage.h"

#include <SFML/Window/Event.hpp>

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, Renderer()
	, TextureBank()
	, InputManager()
	, Context(Renderer.GetQueue(), TextureBank, MessageQueue, NetworkQueue, InputManager)
	, StateStack(Context)
	, ShouldRun(true)
{
	Message::RegisterNetworkMessages();

	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 1920;
	VideoMode.height = 1080;

	Context.WindowDimensions = sf::Vector2u(VideoMode.width, VideoMode.height);

	Window.create(VideoMode, "FarmingGame");

	StateStack.PushState(new CGameState());

	//Server = std::make_unique<Network::Server>(54000, Context);
	Client = std::make_unique<Network::Client>("Jokmokks Jocke", sf::IpAddress("81.231.243.157"), 54000, Context);
}

// ----------------------------------------------------------------------

bool CApplication::GetShouldRun() const
{
	return !StateStack.IsEmpty();
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	NetworkQueue.SendAllEvents();
	MessageQueue.SendAllEvents();

	const float DeltaTime = TickTimer.getElapsedTime().asSeconds();
	TickTimer.restart();

	InputManager.StartNewFrame();
	HandleWindowEvents();

	Window.clear(sf::Color(50, 150, 250, 250));

	StateStack.Tick(DeltaTime);
	StateStack.Draw();

	Renderer.RunRender(Window);

	Window.display();

	//Server->Tick();
	Client->Tick();
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
		else if (Event.type == sf::Event::KeyPressed)
		{
			InputManager.SetCurrentKeyState(Event.key.code, EKeyState::Down);
		}
		else if (Event.type == sf::Event::KeyReleased)
		{
			InputManager.SetCurrentKeyState(Event.key.code, EKeyState::Up);
		}
	}
}

// ----------------------------------------------------------------------
