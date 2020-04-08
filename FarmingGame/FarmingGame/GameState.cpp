#include "GameState.h"

#include "TextureBank.h"
#include "WindowAccessorService.h"
#include "RenderQueue.h"

#include <SFML/Window/Keyboard.hpp>

// ----------------------------------------------------------------------

CGameState::CGameState()
	: TileSize(80)
	, GameBoard(TileSize, sf::Vector2i(2,2))
	, BackgroundRect()
{
}

// ----------------------------------------------------------------------

void CGameState::OnStart(CContextServiceProvider& InServiceProvider)
{
	GameBoard.Load(InServiceProvider);

	CTextureBank& TextureBank = InServiceProvider.GetServiceRequired<CTextureBank>();

	BackgroundRect.setTexture(&TextureBank.GetTexture("GrassTile"));
	BackgroundRect.setSize(sf::Vector2f(static_cast<float>(TileSize), static_cast<float>(TileSize)));

	GameBoard.SetPlayerCount(4);

	GameBoard.SetPlayerTexture(0, TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(1, TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(2, TextureBank.GetTexture("PlayerSprite"));
	GameBoard.SetPlayerTexture(3, TextureBank.GetTexture("PlayerSprite"));
}

// ----------------------------------------------------------------------

EStateTickResult CGameState::Tick(float InTimeDelta, CContextServiceProvider& InServiceProvider)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return EStateTickResult::Pop;
	}

	return EStateTickResult::Keep;
}

// ----------------------------------------------------------------------

void CGameState::Render(CContextServiceProvider& InServiceProvider)
{
	GameBoard.Draw(InServiceProvider);
	DrawBackground(InServiceProvider);
}

// ----------------------------------------------------------------------

void CGameState::DrawBackground(CContextServiceProvider& InServiceProvider)
{
	CWindowAccessorService& WindowAccessor = InServiceProvider.GetServiceRequired< CWindowAccessorService >();
	CRenderQueue& RenderQueue = InServiceProvider.GetServiceRequired< CRenderQueue >();

	const unsigned int XTilesToDraw = WindowAccessor.WindowDimensions.x / TileSize + 1;
	const unsigned int YTilesToDraw = WindowAccessor.WindowDimensions.y / TileSize + 1;

	for (unsigned int X = 0; X < XTilesToDraw; ++X)
	{
		for (unsigned int Y = 0; Y < YTilesToDraw; ++Y)
		{
			const sf::Vector2f DrawPos(static_cast<float>(X * TileSize), static_cast<float>(Y * TileSize));
			BackgroundRect.setPosition(DrawPos);

			RenderQueue.EnqueueCommand(BackgroundRect, ERenderLayer::Background);
		}
	}
}

// ----------------------------------------------------------------------
