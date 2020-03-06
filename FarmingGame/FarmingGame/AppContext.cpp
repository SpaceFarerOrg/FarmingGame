#include "AppContext.h"

// ----------------------------------------------------------------------

SAppContext::SAppContext(
	CRenderQueue& InRenderQueue,
	CTextureBank& InTextureBank,
	CMessageQueue& InMessageQueue,
	CNetworkMessageQueue& InNetworkQueue)
	: RenderQueue(InRenderQueue)
	, TextureBank(InTextureBank)
	, MessageQueue(InMessageQueue)
	, NetworkQueue(InNetworkQueue)
{
}

// ----------------------------------------------------------------------