#include "GameBoard.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "AppContext.h"

// ----------------------------------------------------------------------

CGameBoard::CGameBoard(unsigned int InBoardSquareDimension, const sf::Vector2i& InBoardTileOffset)
	: BoardRows()
	, BoardTileOffset(InBoardTileOffset)
	, PlayerTilePosition()
	, PlayerCount(4)
	, BoardTileSize(InBoardSquareDimension)
{
}

// ----------------------------------------------------------------------

void CGameBoard::SetPlayerCount(unsigned short InPlayerCount)
{
	PlayerCount = InPlayerCount;
}

// ----------------------------------------------------------------------

void CGameBoard::SetPlayerTexture(unsigned int InPlayerID, const sf::Texture& InTexture)
{
	PlayerSprites[InPlayerID].setTexture(&InTexture);
	PlayerSprites[InPlayerID].setSize({ (float)BoardTileSize, (float)BoardTileSize });
}

// ----------------------------------------------------------------------

void CGameBoard::MovePlayer(unsigned int InPlayerID, unsigned int InMoveAmount)
{
	const unsigned int CurrentPlayerPosition = PlayerTilePosition[InPlayerID];
	const unsigned int NewPlayerPosition = (CurrentPlayerPosition + InMoveAmount) % TileCount;
	PlayerTilePosition[InPlayerID] = NewPlayerPosition;
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

	for (unsigned int PlayerID = 0; PlayerID < PlayerCount; ++PlayerID)
	{
		PlayerSprites[PlayerID].setPosition(BoardRows[PlayerTilePosition[PlayerID]]->GetPosition());
		InAppContext.RenderQueue.EnqueueCommand(PlayerSprites[PlayerID]);
	}
}

// ----------------------------------------------------------------------

void CGameBoard::SetUpBoard(SAppContext& InAppContext)
{
	// Set up squares
	BoardRows = {
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile(),
		new CFarmTile(), new CChanceTile(), new CEventTile(), new CAnimalTile(), new CSeedTile(), new CFieldTile() };
	
	// Set up player start positions
	for (unsigned int PlayerIndex = 0; PlayerIndex < PlayerCount; ++PlayerIndex)
	{
		PlayerTilePosition[PlayerIndex] = RowLen * PlayerIndex;
	}

	// Set up board square positions
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