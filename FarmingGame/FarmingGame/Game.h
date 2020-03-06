#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "BaseState.h"
#include "GameBoard.h"

struct SAppContext;

// ----------------------------------------------------------------------

class CGame final
	: public CBaseState
{
public:
	CGame();

	EStateType GetType() override { return EStateType::Full; }

	void OnStart(SAppContext& InContext) override;

	EStateTickResult Tick(float InTimeDelta, SAppContext& InAppContext) override;
	void Render(SAppContext& InAppContext) override;
private:
	void DrawBackground(SAppContext& InContext);

	unsigned int TileSize;

	CGameBoard GameBoard;
	sf::RectangleShape BackgroundRect;
};

// ----------------------------------------------------------------------