#pragma once

#include <SFML/Graphics/Sprite.hpp>
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
	using Queue = std::array<std::vector< sf::Drawable* >, static_cast<unsigned int>(ERenderLayer::Count)>;
	using DrawFunction = std::function< void(sf::Drawable&) >;

	CRenderQueue();
	void EnqueueCommand(const sf::Sprite& InSprite, ERenderLayer InLayer = ERenderLayer::Game);
	void EnqueueCommand(const sf::Text& InText, ERenderLayer InLayer = ERenderLayer::Game);
	
	void ForEachCommand(const DrawFunction& InDrawFunctor);
	void Clear();
private:
	Queue Commands;
	std::vector< sf::Sprite > SpriteCommands;
	std::vector< sf::Text > TextCommands;

};

// ----------------------------------------------------------------------
