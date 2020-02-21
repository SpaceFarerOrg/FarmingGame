#pragma once

#include "BoardSquare.h"
#include <array>

#include <SFML/System/Vector2.hpp>

// ----------------------------------------------------------------------

struct SAppContext;

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

	void MovePlayer(unsigned int InPlayerID, unsigned int InMoveAmount);
	const CBoardSquareBase& GetPlayerBoardSquare( unsigned int InPlayerID ) const;

	void Load(SAppContext& InAppContext);
	void Draw(SAppContext& InAppContext);
private:
	void SetUpBoard(SAppContext& InAppContext);

	constexpr static unsigned int RowLen = 6;
	constexpr static unsigned int RowCount = 4;
	constexpr static unsigned int TileCount = CalculateTileCount(RowLen, RowCount);

	std::array<CBoardSquareBase*, TileCount> BoardRows;
	sf::Vector2i BoardTileOffset;
	unsigned int PlayerTilePosition[4];
	const unsigned int BoardTileSize;
};

// ----------------------------------------------------------------------