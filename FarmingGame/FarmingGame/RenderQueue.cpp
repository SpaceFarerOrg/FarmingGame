#include "RenderQueue.h"

#define LAYER_TO_INDEX( InLayer ) static_cast<unsigned int>( InLayer )

// ----------------------------------------------------------------------

CRenderQueue::CRenderQueue()
	: SpriteCommands( new FSpriteCommandList() )
	, RectangleCommands( new FRectangleCommandsList() )
	, TextCommands( new FTextCommandsList() )
{
}

// ----------------------------------------------------------------------

CRenderQueue::CRenderQueue(CRenderQueue& InOther)
	: SpriteCommands( InOther.SpriteCommands )
	, RectangleCommands( InOther.RectangleCommands )
	, TextCommands( InOther.TextCommands )
{
}

// ----------------------------------------------------------------------

void CRenderQueue::EnqueueCommand(const sf::RectangleShape& InRectShape, ERenderLayer InLayer)
{
	RectangleCommands->push_back({ InRectShape, InLayer });
}

// ----------------------------------------------------------------------

void CRenderQueue::EnqueueCommand(const sf::Sprite& InSprite, ERenderLayer InLayer)
{
	SpriteCommands->push_back({ InSprite, InLayer });
}

// ----------------------------------------------------------------------

void CRenderQueue::EnqueueCommand(const sf::Text& InText, ERenderLayer InLayer)
{
	TextCommands->push_back({ InText, InLayer });
}

// ----------------------------------------------------------------------

void CRenderQueue::ForEachCommand(const DrawFunction& InDrawFunctor)
{
	std::vector< sf::Drawable* > Commands;
	BuildCommandsList(Commands);

	for (auto& Command : Commands)
	{
		InDrawFunctor(*Command);
	}
}

// ----------------------------------------------------------------------

void CRenderQueue::Clear()
{
	SpriteCommands->clear();
	RectangleCommands->clear();
	TextCommands->clear();
}

void CRenderQueue::BuildCommandsList(std::vector<sf::Drawable*>& OutCommandsList)
{
	std::array< std::vector<sf::Drawable*>, static_cast<unsigned int>(ERenderLayer::Count) > LayeredCommands;
	OutCommandsList.reserve(SpriteCommands->size() + RectangleCommands->size() + TextCommands->size());

	// Add sprite commands
	for (auto& Command : *SpriteCommands)
	{
		LayeredCommands[LAYER_TO_INDEX(Command.second)].push_back(&Command.first);
	}

	// Add rectangle commands
	for (auto& Command : *RectangleCommands)
	{
		LayeredCommands[LAYER_TO_INDEX(Command.second)].push_back(&Command.first);
	}

	// Add text commands
	for (auto& Command : *TextCommands)
	{
		LayeredCommands[LAYER_TO_INDEX(Command.second)].push_back(&Command.first);
	}

	// Add all in order of layer to the commands list
	for (unsigned int i = 0; i < LayeredCommands.size(); ++i)
	{
		OutCommandsList.insert(OutCommandsList.end(), LayeredCommands[i].begin(), LayeredCommands[i].end());
	}

}

// ----------------------------------------------------------------------