#pragma once

#include "RenderQueue.h"
#include "TextureBank.h"
#include "Messaging/MessageQueue.h"
#include "NetworkMessageQueue.h"

#include <SFML/System/Vector2.hpp>

struct SAppContext
{
public:
	SAppContext( 
		CRenderQueue& InRenderQueue,
		CTextureBank& InTextureBank,
		CMessageQueue& InMessageQueue,
		CNetworkMessageQueue& InNetworkQueue);

	sf::Vector2u WindowDimensions;
	CRenderQueue& RenderQueue;
	CTextureBank& TextureBank;
	CMessageQueue& MessageQueue;
	CNetworkMessageQueue& NetworkQueue;
};