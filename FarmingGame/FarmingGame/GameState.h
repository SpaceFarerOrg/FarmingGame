#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BaseState.h"
#include "GameBoard.h"

class CContextServiceProvider;
class CRenderQueue;

// ----------------------------------------------------------------------

class CGameState final
	: public CBaseState
{
public:
	CGameState();

	EStateType GetType() override { return EStateType::Full; }

	void OnStart(CContextServiceProvider& InServiceProvider) override;

	EStateTickResult Tick(float InTimeDelta, CContextServiceProvider& InServiceProvider) override;
	void Render(CContextServiceProvider& InServiceProvider) override;
private:
	void DrawBackground(CContextServiceProvider& InServiceProvider);

	unsigned int TileSize;

	CGameBoard GameBoard;
	sf::RectangleShape BackgroundRect;
};

// ----------------------------------------------------------------------