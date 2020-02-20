#pragma once
#include "RenderQueue.h"

// ----------------------------------------------------------------------

namespace sf
{
	class RenderTarget;
}

// ----------------------------------------------------------------------

class CRenderer
{
public:
	CRenderer();
	CRenderQueue& GetQueue();
	void RunRender(sf::RenderTarget& InRenderTarget);
private:
	CRenderQueue RenderQueue;
};

// ----------------------------------------------------------------------