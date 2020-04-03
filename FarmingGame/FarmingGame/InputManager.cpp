#include "InputManager.h"

// ----------------------------------------------------------------------

CInputManager::CInputManager()
	: PreviousState()
	, CurrentState()
{
	// Assume all keys to not be pressed on construct
	for (unsigned int i = 0; i < PreviousState.max_size(); ++i)
	{
		PreviousState[i] = EKeyState::Up;
		CurrentState[i] = EKeyState::Up;
	}
}

// ----------------------------------------------------------------------

void CInputManager::StartNewFrame()
{
	PreviousState = CurrentState;
}

// ----------------------------------------------------------------------

void CInputManager::SetCurrentKeyState(sf::Keyboard::Key InKey, EKeyState InState)
{
	CurrentState[static_cast<unsigned int>(InKey)] = InState;
}

// ----------------------------------------------------------------------

bool CInputManager::IsKeyPressed(sf::Keyboard::Key InKey) const
{
	const unsigned int KeyIndex = static_cast<unsigned int>(InKey);
	return  ( CurrentState[KeyIndex] == EKeyState::Down ) && ( PreviousState[KeyIndex] == EKeyState::Up );
}

// ----------------------------------------------------------------------

bool CInputManager::IsKeyDown(sf::Keyboard::Key InKey) const
{
	const unsigned int KeyIndex = static_cast<unsigned int>(InKey);
	return CurrentState[KeyIndex] == EKeyState::Down;
}

// ----------------------------------------------------------------------

bool CInputManager::IsKeyUp(sf::Keyboard::Key InKey) const
{
	const unsigned int KeyIndex = static_cast<unsigned int>(InKey);
	return CurrentState[KeyIndex] == EKeyState::Up;
}

// ----------------------------------------------------------------------