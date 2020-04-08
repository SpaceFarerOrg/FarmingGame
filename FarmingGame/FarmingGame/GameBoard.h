#pragma once

#include "BoardSquare.h"
#include <array>

#include <SFML/System/Vector2.hpp>

// ----------------------------------------------------------------------

class CContextServiceProvider;

// ----------------------------------------------------------------------

constexpr static unsigned int CalculateTileCount(unsigned int InRowLen, unsigned int InRowCount)
{
	unsigned int Val = 0;
	for (unsigned int i = 0; i < InRowCount; ++i)
	{
		Val += InRowLen;
	}

	return Val;
}

// ----------------------------------------------------------------------

class CGameBoard
{
public:
	explicit CGameBoard(unsigned int InBoardSquareDimension, const sf::Vector2i& InBoardTileOffset);

	void SetPlayerCount(unsigned short InPlayerCount);
	void SetPlayerTexture(unsigned int InPlayerID, const sf::Texture& InTexture);

	void MovePlayer(unsigned int InPlayerID, unsigned int InMoveAmount);
	const CBoardSquareBase& GetPlayerBoardSquare( unsigned int InPlayerID ) const;

	void Load(CContextServiceProvider& InServiceProvider);
	void Draw(CContextServiceProvider& InServiceProvider);
private:
	void SetUpBoard(CContextServiceProvider& InServiceProvider);

	constexpr static unsigned int RowLen = 6;
	constexpr static unsigned int RowCount = 4;
	constexpr static unsigned int TileCount = CalculateTileCount(RowLen, RowCount);

	std::array<CBoardSquareBase*, TileCount> BoardRows;
	sf::Vector2i BoardTileOffset;

	unsigned int PlayerTilePosition[4];
	sf::RectangleShape PlayerSprites[4];

	unsigned short PlayerCount;
	const unsigned int BoardTileSize;
};

// ----------------------------------------------------------------------