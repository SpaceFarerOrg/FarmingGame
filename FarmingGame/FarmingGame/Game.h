#pragma once

struct SAppContext;

// ----------------------------------------------------------------------

class CGame
{
public:
	CGame() = default;
	void Tick(SAppContext& InContext, float InTimeDelta);
};

// ----------------------------------------------------------------------