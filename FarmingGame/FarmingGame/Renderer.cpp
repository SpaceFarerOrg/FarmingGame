#include "Renderer.h"

#include <SFML/Graphics/RenderTarget.hpp>

// ----------------------------------------------------------------------

CRenderer::CRenderer()
{
}

// ----------------------------------------------------------------------

CRenderQueue& CRenderer::GetQueue()
{
	return RenderQueue;
}

// ----------------------------------------------------------------------

void CRenderer::RunRender(sf::RenderTarget& InRenderTarget)
{
	auto DrawFunctor = [&InRenderTarget](sf::Drawable& InDrawable) { InRenderTarget.draw(InDrawable); };
	RenderQueue.ForEachCommand(DrawFunctor);
	RenderQueue.Clear();
}

// ----------------------------------------------------------------------
