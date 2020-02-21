#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "GameBoard.h"

struct SAppContext;

// ----------------------------------------------------------------------

class CGame
{
public:
	CGame();
	void Startup( SAppContext& InContext );
	void Tick(SAppContext& InContext, float InTimeDelta);
private:
	void DrawBackground(SAppContext& InContext);

	unsigned int TileSize;

	CGameBoard GameBoard;
	sf::RectangleShape BackgroundRect;
};

// ----------------------------------------------------------------------