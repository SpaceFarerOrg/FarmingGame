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

#define SERVER 1

int main()
{
	CApplication App;

	while (App.GetShouldRun())
	{
		App.Tick();
	}

	return 0;
}