#include "Game.h"

#include "AppContext.h"

// ----------------------------------------------------------------------

void CGame::Startup(SAppContext& InContext)
{
	TestSprite.setTexture(InContext.TextureBank.GetTexture("Test"));
}

// ----------------------------------------------------------------------

void CGame::Tick(SAppContext& InContext, float InTimeDelta)
{
	InContext.RenderQueue.EnqueueCommand(TestSprite);
}

// ----------------------------------------------------------------------
