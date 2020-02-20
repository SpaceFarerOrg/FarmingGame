#include "RenderQueue.h"

#define LAYER_TO_INDEX( InLayer ) static_cast<unsigned int>( InLayer )

// ----------------------------------------------------------------------

CRenderQueue::CRenderQueue()
	: Commands()
	, SpriteCommands()
	, TextCommands()
{
}

// ----------------------------------------------------------------------

void CRenderQueue::EnqueueCommand(const sf::Sprite& InSprite, ERenderLayer InLayer)
{
	SpriteCommands.push_back(InSprite);
	Commands[LAYER_TO_INDEX(InLayer)].push_back(&SpriteCommands.back());
}

// ----------------------------------------------------------------------

void CRenderQueue::EnqueueCommand(const sf::Text& InText, ERenderLayer InLayer)
{
	TextCommands.push_back(InText);
	Commands[LAYER_TO_INDEX(InLayer)].push_back(&TextCommands.back());
}

// ----------------------------------------------------------------------

void CRenderQueue::ForEachCommand(const DrawFunction& InDrawFunctor)
{
	for (auto& LayerCommands : Commands)
	{
		for (auto& Command : LayerCommands)
		{
			InDrawFunctor(*Command);
		}
	}
}

// ----------------------------------------------------------------------

void CRenderQueue::Clear()
{
	for (auto& Layer : Commands)
	{
		Layer.clear();
	}
}

// ----------------------------------------------------------------------