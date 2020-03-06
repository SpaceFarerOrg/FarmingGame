#include "Application.h"

#include "GameState.h"
#include "NetworkMessage.h"

#include <SFML/Window/Event.hpp>

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, Renderer()
	, TextureBank()
	, StateStack(Context)
	, Context(Renderer.GetQueue(), TextureBank, MessageQueue, NetworkQueue)
	, ShouldRun(true)
{
	Message::RegisterNetworkMessages();

	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 1920;
	VideoMode.height = 1080;

	Context.WindowDimensions = sf::Vector2u(VideoMode.width, VideoMode.height);

	Window.create(VideoMode, "FarmingGame");

	StateStack.PushState(new CGameState());

	Server = std::make_unique<Network::Server>(54000, Context);
	Client = std::make_unique<Network::Client>("Pikachu", sf::IpAddress("192.168.1.1"), 54000, Context);
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

	HandleWindowEvents();

	Window.clear(sf::Color(50, 150, 250, 250));

	StateStack.Tick(DeltaTime);
	StateStack.Draw();

	Renderer.RunRender(Window);

	Window.display();

	NetworkQueue.DispatchEvent<Network::NetworkMessage>(1, sf::IpAddress("localhost").toInteger());
	MessageQueue.DispatchEvent<Network::NetworkMessage>(0, 0);

	Server->Tick();
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
	}
}

// ----------------------------------------------------------------------
