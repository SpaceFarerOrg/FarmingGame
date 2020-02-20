#include "TextureBank.h"

// ----------------------------------------------------------------------

CTextureBank::CTextureBank()
	: RootTexturePath("Textures/")
{
}

// ----------------------------------------------------------------------

sf::Texture& CTextureBank::GetTexture(const char* InTextureName)
{
	if (Bank.find(InTextureName) == Bank.end())
	{
		// Texture not loaded. Load it :D
		Bank[InTextureName].loadFromFile(RootTexturePath + std::string(InTextureName) + ".png");
	}

	return Bank[InTextureName];
}

// ----------------------------------------------------------------------
