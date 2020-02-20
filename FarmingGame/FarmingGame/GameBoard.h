#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>

struct SAppContext;

enum class EBoardEntry
{
	None,
	Farm,
	VictoryFarm,
	Chance,
	Event,
	Animal,
	Field,
	Seed,
};

class CGameBoard
{
public:
	CGameBoard();

	void Load(SAppContext& InAppContext);
	void Draw(SAppContext& InAppContext);
private:
	void GenerateBoard();
	
	std::array< std::array<EBoardEntry, 7>, 7 > BoardLayout;

	unsigned int TileSize;
	sf::RectangleShape BackgroundTile;
	
	sf::RectangleShape FarmTile;
	sf::RectangleShape ChanceTile;
	sf::RectangleShape EventTile;
	sf::RectangleShape AnimalTile;
	sf::RectangleShape SeedTile;
	sf::RectangleShape FieldTile;
	sf::RectangleShape TileBG;
};