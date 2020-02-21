#include "Game.h"

#include "AppContext.h"

// ----------------------------------------------------------------------

CGame::CGame()
	: GameBoard(64)
{
}

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
