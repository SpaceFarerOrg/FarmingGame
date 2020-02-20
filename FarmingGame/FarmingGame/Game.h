#pragma once

#include <SFML/Graphics/Sprite.hpp>

struct SAppContext;

// ----------------------------------------------------------------------

class CGame
{
public:
	CGame() = default;
	void Startup( SAppContext& InContext );
	void Tick(SAppContext& InContext, float InTimeDelta);

	sf::Sprite TestSprite;
};

// ----------------------------------------------------------------------