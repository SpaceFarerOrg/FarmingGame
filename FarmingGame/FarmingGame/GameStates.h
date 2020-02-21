#pragma once

enum class EPrimaryState
{
	MainMenu,
	Board,
	Market,
};

enum class ESubState
{
	// Main Menu
	Options,
	JoinGame,
	CreateGame,

	// Board
	SetProduction,
	Chance,
	Event,
	BuyAnimal,
	BuyField,
	BuySeed,
	Trade,

	// Market
	PriceRoll,
	Sales,
};