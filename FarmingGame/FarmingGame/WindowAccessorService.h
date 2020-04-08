#pragma once

#include "ContextServiceInterface.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// -----------------------------------------------------------------------

class CWindowAccessorService
	: public IContextService
{
public:
	CWindowAccessorService(sf::RenderWindow& InWindow)
		: WindowDimensions(static_cast<float>(InWindow.getSize().x), static_cast<float>(InWindow.getSize().y))
		, RenderWindow(InWindow)
	{
	}

	const sf::Vector2f WindowDimensions;
private:
	sf::RenderWindow& RenderWindow;
};

// -----------------------------------------------------------------------

