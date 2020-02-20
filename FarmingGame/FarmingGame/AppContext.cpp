#include "AppContext.h"

// ----------------------------------------------------------------------

SAppContext::SAppContext(
	CRenderQueue& InRenderQueue,
	CTextureBank& InTextureBank)
	: RenderQueue(InRenderQueue)
	, TextureBank(InTextureBank)
{
}

// ----------------------------------------------------------------------