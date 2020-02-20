#include "Game.h"

#include "AppContext.h"

// ----------------------------------------------------------------------

void CGame::Startup(SAppContext& InContext)
{
	GameBoard.Load(InContext);
}

// ----------------------------------------------------------------------

void CGame::Tick(SAppContext& InContext, float InTimeDelta)
{
	GameBoard.Draw(InContext);
}

// ----------------------------------------------------------------------
