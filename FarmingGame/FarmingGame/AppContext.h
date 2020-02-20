#pragma once

#include "RenderQueue.h"

struct SAppContext
{
public:
	SAppContext( CRenderQueue& InRenderQueue );

	CRenderQueue& RenderQueue;
};