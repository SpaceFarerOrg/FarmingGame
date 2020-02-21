#pragma once
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include "GameStates.h"
#include "AppContext.h"

// ----------------------------------------------------------------------

class CBoardSquareBase
{
public:
	CBoardSquareBase() = delete;

	void SetSquareSize(unsigned int InSquareSize)
	{
		SquareSize = InSquareSize;
	}

	void Load(SAppContext& InContext)
	{
		Sprite.setSize(sf::Vector2f(static_cast<float>(SquareSize), static_cast<float>(SquareSize)));
		Sprite.setTexture(&InContext.TextureBank.GetTexture(Name.c_str()));
	}

	void SetPosition(unsigned int InTileX, unsigned int InTileY)
	{
		Sprite.setPosition(sf::Vector2f(static_cast<float>(InTileX * SquareSize), static_cast<float>(InTileY * SquareSize) ));
	}

	void DrawAt(SAppContext& InContext)
	{
		InContext.RenderQueue.EnqueueCommand(Sprite);
	}

	virtual ESubState GetExecuteState() const = 0;
protected:
	CBoardSquareBase(const std::string& InName)
		: SquareSize(0)
		, Sprite()
		, Name(InName)
	{
	}

	unsigned int SquareSize;
	sf::RectangleShape Sprite;
	std::string Name;
};

// ----------------------------------------------------------------------

#define DEFINE_TILE_TYPE( TypeName, TileName, SubState ) class TypeName final : public CBoardSquareBase { public: TypeName() : CBoardSquareBase( TileName ) {} ESubState GetExecuteState() const override { return SubState; } };  

DEFINE_TILE_TYPE(CFarmTile, "FarmTile", ESubState::SetProduction)
DEFINE_TILE_TYPE(CChanceTile, "ChanceTile", ESubState::Chance)
DEFINE_TILE_TYPE(CEventTile, "EventTile", ESubState::Event)
DEFINE_TILE_TYPE(CAnimalTile, "AnimalTile", ESubState::BuyAnimal)
DEFINE_TILE_TYPE(CFieldTile, "FieldTile", ESubState::BuyField)
DEFINE_TILE_TYPE(CSeedTile, "SeedTile", ESubState::BuySeed)

// ----------------------------------------------------------------------
