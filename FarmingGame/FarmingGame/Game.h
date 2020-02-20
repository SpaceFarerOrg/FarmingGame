#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "GameBoard.h"

struct SAppContext;

// ----------------------------------------------------------------------

class CGame
{
public:
	CGame() = default;
	void Startup( SAppContext& InContext );
	void Tick(SAppContext& InContext, float InTimeDelta);
private:
	CGameBoard GameBoard;
};

// ----------------------------------------------------------------------