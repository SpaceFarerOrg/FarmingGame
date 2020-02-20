#include "GameBoard.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include "AppContext.h"

CGameBoard::CGameBoard()
	: BackgroundTile()
{
	TileSize = 124;
	sf::Vector2f TileSizeVector(static_cast<float>(TileSize), static_cast<float>(TileSize));

	GenerateBoard();

	BackgroundTile.setSize(TileSizeVector);
	FarmTile.setSize(TileSizeVector);
	ChanceTile.setSize(TileSizeVector);
	EventTile.setSize(TileSizeVector);
	AnimalTile.setSize(TileSizeVector);
	SeedTile.setSize(TileSizeVector);
	FieldTile.setSize(TileSizeVector);
	TileBG.setSize(TileSizeVector);
}

void CGameBoard::GenerateBoard()
{
	BoardLayout = {
	EBoardEntry::Farm, EBoardEntry::Seed, EBoardEntry::Animal, EBoardEntry::Event, EBoardEntry::Field, EBoardEntry::Chance, EBoardEntry::Farm,
	EBoardEntry::Seed, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::Animal,
	EBoardEntry::Chance, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::Event,
	EBoardEntry::Animal, EBoardEntry::None, EBoardEntry::None, EBoardEntry::VictoryFarm, EBoardEntry::None, EBoardEntry::None,  EBoardEntry::Field,
	EBoardEntry::Event,	EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::Chance,
	EBoardEntry::Field,	 EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::None, EBoardEntry::Seed,
	EBoardEntry::Farm, EBoardEntry::Field, EBoardEntry::Seed, EBoardEntry::Chance, EBoardEntry::Animal, EBoardEntry::Event, EBoardEntry::Farm
	};
}

void CGameBoard::Load(SAppContext& InAppContext)
{
	BackgroundTile.setTexture(&InAppContext.TextureBank.GetTexture("GrassTile"));
	FarmTile.setTexture(&InAppContext.TextureBank.GetTexture("FarmTile"));
	ChanceTile.setTexture(&InAppContext.TextureBank.GetTexture("ChanceTile"));
	EventTile.setTexture(&InAppContext.TextureBank.GetTexture("EventTile"));
	FieldTile.setTexture(&InAppContext.TextureBank.GetTexture("FieldTile"));
	AnimalTile.setTexture(&InAppContext.TextureBank.GetTexture("AnimalTile"));
	SeedTile.setTexture(&InAppContext.TextureBank.GetTexture("SeedTile"));
	TileBG.setTexture(&InAppContext.TextureBank.GetTexture("TileBackground"));

}

void CGameBoard::Draw(SAppContext& InAppContext)
{
	const unsigned int XDepth = 7;
	const unsigned int YDepth = 7;

	for (int X = 0; X < XDepth; ++X)
	{
		for (int Y = 0; Y < YDepth; ++Y)
		{
			sf::Vector2f TileVector(sf::Vector2f(static_cast<float>(X * TileSize), static_cast<float>(Y * TileSize)));

			sf::RectangleShape* TileContent = nullptr;

			switch (BoardLayout[Y][X])
			{
			case EBoardEntry::Farm:
				TileContent = &FarmTile;
				break;
			case EBoardEntry::Chance:
				TileContent = &ChanceTile;
				break;
			case EBoardEntry::Event:
				TileContent = &EventTile;
				break;
			case EBoardEntry::Animal:
				TileContent = &AnimalTile;
				break;
			case EBoardEntry::Field:
				TileContent = &FieldTile;
				break;
			case EBoardEntry::Seed:
				TileContent = &SeedTile;
				break;
			default:
				break;
			}

			if (TileContent)
			{
				TileBG.setPosition(TileVector);
				InAppContext.RenderQueue.EnqueueCommand(TileBG);

				TileContent->setPosition(TileVector);
				InAppContext.RenderQueue.EnqueueCommand(*TileContent);
			}

			BackgroundTile.setPosition(TileVector);
			InAppContext.RenderQueue.EnqueueCommand(BackgroundTile, ERenderLayer::Background);
		}
	}
}
