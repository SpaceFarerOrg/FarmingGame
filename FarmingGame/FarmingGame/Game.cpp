#include "Game.h"

#include "AppContext.h"

#include <SFML/Window/Keyboard.hpp>

// ----------------------------------------------------------------------

CGame::CGame()
	: TileSize(80)
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

	GameBoard.SetPlayerCount(4);

	GameBoard.SetPlayerTexture(0, InContext.TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(1, InContext.TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(2, InContext.TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(3, InContext.TextureBank.GetTexture("PlayerSprite"));
}

// ----------------------------------------------------------------------

float SecondNextTime = 0.f;

void CGame::Tick(SAppContext& InContext, float InTimeDelta)
{
	SecondNextTime += InTimeDelta;

	if (SecondNextTime >= 1.f)
	{
		GameBoard.MovePlayer(0, 1);
		GameBoard.MovePlayer(1, 1);
		GameBoard.MovePlayer(2, 1);
		GameBoard.MovePlayer(3, 1);
		SecondNextTime = 0.f;
	}


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
