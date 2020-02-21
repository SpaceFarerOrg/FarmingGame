#include "GameBoard.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "AppContext.h"

// ----------------------------------------------------------------------

CGameBoard::CGameBoard(unsigned int InBoardSquareDimension, const sf::Vector2i& InBoardTileOffset)
	: BoardRows()
	, BoardTileOffset(InBoardTileOffset)
	, PlayerTilePosition()
	, BoardTileSize(InBoardSquareDimension)
{
}

// ----------------------------------------------------------------------

void CGameBoard::MovePlayer(unsigned int InPlayerID, unsigned int InMoveAmount)
{
	const unsigned int CurrentPlayerPosition = PlayerTilePosition[InPlayerID];
	const unsigned int NewPlayerPosition = (CurrentPlayerPosition + InMoveAmount) % TileCount;
}

// ----------------------------------------------------------------------

const CBoardSquareBase& CGameBoard::GetPlayerBoardSquare(unsigned int InPlayerID) const
{
	return *BoardRows[PlayerTilePosition[InPlayerID]];
}

// ----------------------------------------------------------------------

void CGameBoard::Load(SAppContext& InAppContext)
{
	SetUpBoard(InAppContext);
}

// ----------------------------------------------------------------------

void CGameBoard::Draw(SAppContext& InAppContext)
{
	for (CBoardSquareBase* Tile : BoardRows)
	{
		Tile->DrawAt(InAppContext);
	}
}

// ----------------------------------------------------------------------

void CGameBoard::SetUpBoard(SAppContext& InAppContext)
{
	BoardRows = {
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile() };

	unsigned int TileX = 0;
	unsigned int TileY = 0;

	for (unsigned int i = 0; i < TileCount; ++i)
	{
		CBoardSquareBase* BoardSquare = BoardRows[i];
		
		BoardSquare->SetSquareSize(BoardTileSize);
		BoardSquare->Load(InAppContext);

		if (i / RowLen == 0)
		{
			BoardSquare->SetPosition(BoardTileOffset.x + TileX++, BoardTileOffset.y + TileY);
		}
		if (i / RowLen == 1)
		{
			BoardSquare->SetPosition(BoardTileOffset.x + TileX, BoardTileOffset.y + TileY++);
		}
		if (i / RowLen == 2)
		{
			BoardSquare->SetPosition(BoardTileOffset.x + TileX--, BoardTileOffset.y + TileY);
		}
		if (i / RowLen == 3)
		{
			BoardSquare->SetPosition(BoardTileOffset.x + TileX, BoardTileOffset.y + TileY--);
		}
	}

	
}

// ----------------------------------------------------------------------