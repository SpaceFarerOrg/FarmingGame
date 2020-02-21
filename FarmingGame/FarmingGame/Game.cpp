#include "Game.h"

#include "AppContext.h"

// ----------------------------------------------------------------------

CGame::CGame()
	: TileSize(64)
	, GameBoard(TileSize, sf::Vector2i(2,2))
	, BackgroundRect()
{
}

// ----------------------------------------------------------------------

void CGame::Startup(SAppContext& InContext)
{
	GameBoard.Load(InContext);
	BackgroundRect.setTexture(&InContext.TextureBank.GetTexture("GrassTile"));
	BackgroundRect.setSize(sf::Vector2f(static_cast<float>(TileSize), static_cast<float>(TileSize)));
}

// ----------------------------------------------------------------------

void CGame::Tick(SAppContext& InContext, float InTimeDelta)
{
	GameBoard.Draw(InContext);
	DrawBackground(InContext);
}

// ----------------------------------------------------------------------

void CGame::DrawBackground(SAppContext& InContext)
{
	const unsigned int XTilesToDraw = InContext.WindowDimensions.x / TileSize + 1;
	const unsigned int YTilesToDraw = InContext.WindowDimensions.y / TileSize + 1;

	for (unsigned int X = 0; X < XTilesToDraw; ++X)
	{
		for (unsigned int Y = 0; Y < YTilesToDraw; ++Y)
		{
			const sf::Vector2f DrawPos(static_cast<float>(X * TileSize), static_cast<float>(Y * TileSize));
			BackgroundRect.setPosition(DrawPos);

			InContext.RenderQueue.EnqueueCommand(BackgroundRect, ERenderLayer::Background);
		}
	}
}

// ----------------------------------------------------------------------
