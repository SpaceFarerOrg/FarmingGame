#pragma once
#include "ContextServiceProvider.h"

// ----------------------------------------------------------------------

enum class EStateTickResult
{
	Keep,
	Pop,
};

// ----------------------------------------------------------------------

enum class EStateType
{
	Full,
	OverlayRenderUnderlying,
	OverlayTickAndRenderUnderlying
};

// ----------------------------------------------------------------------

class CBaseState
{
public:
	virtual EStateType GetType() = 0;

	virtual void OnStart(CContextServiceProvider& InServiceProvider) {};
	virtual void OnStop(CContextServiceProvider& InServiceProvider) {};

	virtual EStateTickResult Tick(float InTimeDelta, CContextServiceProvider& InServiceProvider) { return EStateTickResult::Pop; };
	virtual void Render(CContextServiceProvider& InServiceProvider) {};
};

// ----------------------------------------------------------------------