#pragma once

#include "RenderQueue.h"
#include "TextureBank.h"

struct SAppContext
{
public:
	SAppContext( 
		CRenderQueue& InRenderQueue,
		CTextureBank& InTextureBank );

	CRenderQueue& RenderQueue;
	CTextureBank& TextureBank;
};