#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")
#pragma comment(lib, "sfml-network-d")
#else
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-graphics")
#pragma comment(lib, "sfml-network")
#endif

#include "Application.h"
#include "Server.h"
#include "Client.h"

using namespace Network;

#define SERVER 0

int main()
{
	CApplication App;

	Network::Message::RegisterNetworkMessages();

#if SERVER
	Server server(54000);
#else
	Client client("Client", "81.231.243.157", 54000);
#endif

	while (App.GetShouldRun())
	{
#if SERVER
		server.Tick();
#endif
		App.Tick();
	}

	return 0;
}