#pragma once

#include "RenderQueue.h"
#include "TextureBank.h"
#include <SFML/System/Vector2.hpp>

struct SAppContext
{
public:
	SAppContext( 
		CRenderQueue& InRenderQueue,
		CTextureBank& InTextureBank );

	sf::Vector2u WindowDimensions;
	CRenderQueue& RenderQueue;
	CTextureBank& TextureBank;
};