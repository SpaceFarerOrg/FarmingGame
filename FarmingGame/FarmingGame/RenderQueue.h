#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <AccCtrl.h>
#include <array>
#include <vector>
#include <functional>

// ----------------------------------------------------------------------

enum class ERenderLayer
{
	Background,
	Game,
	UI,
	Count, // Do not use this!
};

// ----------------------------------------------------------------------

class CRenderQueue
{
public:
	using DrawFunction = std::function< void(sf::Drawable&) >;

	CRenderQueue();
	void EnqueueCommand(const sf::RectangleShape& InRectShape, ERenderLayer InLayer = ERenderLayer::Game);
	void EnqueueCommand(const sf::Sprite& InSprite, ERenderLayer InLayer = ERenderLayer::Game);
	void EnqueueCommand(const sf::Text& InText, ERenderLayer InLayer = ERenderLayer::Game);
	
	void ForEachCommand(const DrawFunction& InDrawFunctor);
	void Clear();
private:
	void BuildCommandsList( std::vector< sf::Drawable* >& OutCommandsList );

	std::vector< std::pair<sf::Sprite, ERenderLayer> > SpriteCommands;
	std::vector< std::pair<sf::RectangleShape, ERenderLayer> > RectangleCommands;
	std::vector< std::pair<sf::Text, ERenderLayer> > TextCommands;

};

// ----------------------------------------------------------------------
