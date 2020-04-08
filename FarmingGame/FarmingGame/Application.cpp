#include "Application.h"

#include "GameState.h"
#include "NetworkMessage.h"

#include "Renderer.h"
#include "TextureBank.h"
#include "InputManager.h"
#include "WindowAccessorService.h"

#include <SFML/Window/Event.hpp>

// ----------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, ServiceProvider()
	, StateStack( ServiceProvider )
	, Renderer()
	, ShouldRun(true)
{
	Message::RegisterNetworkMessages();


	sf::VideoMode VideoMode = sf::VideoMode::getDesktopMode();
	VideoMode.width = 1920;
	VideoMode.height = 1080;

	Window.create(VideoMode, "FarmingGame");

	RegisterServices();

	StateStack.PushState(new CGameState());

	Server = std::make_unique<Network::Server>(54000, ServiceProvider);
	Client = std::make_unique<Network::Client>("Jokmokks Jocke", sf::IpAddress("localhost"), 54000, ServiceProvider);
}

// ----------------------------------------------------------------------

void CApplication::RegisterServices()
{
	ServiceProvider.RegisterService< CTextureBank >();
	ServiceProvider.RegisterService< CInputManager >();
	ServiceProvider.RegisterService< CMessageQueue >();
	ServiceProvider.RegisterService< CNetworkMessageQueue >();
	ServiceProvider.RegisterService<CRenderQueue>(Renderer.GetQueue());
	ServiceProvider.RegisterService<CWindowAccessorService>(Window);
}

// ----------------------------------------------------------------------

bool CApplication::GetShouldRun() const
{
	return !StateStack.IsEmpty();
}

// ----------------------------------------------------------------------

void CApplication::Tick()
{
	ServiceProvider.GetServiceRequired<CNetworkMessageQueue>().SendAllEvents(); // Send all network events
	ServiceProvider.GetServiceRequired<CMessageQueue>().SendAllEvents(); // Send all internal events

	const float DeltaTime = TickTimer.getElapsedTime().asSeconds();
	TickTimer.restart();

	ServiceProvider.GetServiceRequired<CInputManager>().StartNewFrame();
	HandleWindowEvents();

	Window.clear(sf::Color(50, 150, 250, 250));

	StateStack.Tick(DeltaTime);
	StateStack.Draw();

	Renderer.RunRender(Window);

	Window.display();

	Server->Tick();
	Client->Tick();
}

// ----------------------------------------------------------------------

void CApplication::HandleWindowEvents()
{
	CInputManager& InputManager = ServiceProvider.GetServiceRequired<CInputManager>();

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
