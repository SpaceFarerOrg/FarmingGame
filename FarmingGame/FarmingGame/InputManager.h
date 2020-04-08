#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <array>

#include "ContextServiceInterface.h"

// ----------------------------------------------------------------------

enum class EKeyState
{
	Down,
	Up
};

// ----------------------------------------------------------------------

class IInputState
	: public IContextService
{
public:
	virtual bool IsKeyPressed(sf::Keyboard::Key InKey) const = 0;
	virtual bool IsKeyDown(sf::Keyboard::Key InKey) const = 0;
	virtual bool IsKeyUp(sf::Keyboard::Key InKey) const = 0;
};

// ----------------------------------------------------------------------

class CInputManager final
	: public IInputState
{
public:
	CInputManager();

	void StartNewFrame();
	void SetCurrentKeyState(sf::Keyboard::Key InKey, EKeyState InState);

	virtual bool IsKeyPressed(sf::Keyboard::Key InKey) const override;
	virtual bool IsKeyDown(sf::Keyboard::Key InKey) const override;
	virtual bool IsKeyUp(sf::Keyboard::Key InKey) const override;

private:
	std::array< EKeyState, static_cast<unsigned int>(sf::Keyboard::Key::KeyCount) > PreviousState;
	std::array< EKeyState, static_cast<unsigned int>(sf::Keyboard::Key::KeyCount) > CurrentState;
};

// ----------------------------------------------------------------------