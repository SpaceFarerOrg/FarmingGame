#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "ContextServiceInterface.h"

// ----------------------------------------------------------------------

class CTextureBank
	: public IContextService
{
public:
	CTextureBank();
	sf::Texture& GetTexture(const char* InTextureName);
private:
	const std::string RootTexturePath;
	std::unordered_map< std::string, sf::Texture > Bank;
};

// ----------------------------------------------------------------------