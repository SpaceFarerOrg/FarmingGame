#include "AppContext.h"

// ----------------------------------------------------------------------

SAppContext::SAppContext(
	CRenderQueue& InRenderQueue,
	CTextureBank& InTextureBank,
	CMessageQueue& InMessageQueue,
	CNetworkMessageQueue& InNetworkQueue,
	IInputState& InInputState)
	: RenderQueue(InRenderQueue)
	, TextureBank(InTextureBank)
	, MessageQueue(InMessageQueue)
	, NetworkQueue(InNetworkQueue)
	, InputState(InInputState)
{
}

// ----------------------------------------------------------------------