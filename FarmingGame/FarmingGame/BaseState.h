#pragma once
#include "AppContext.h"

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

	virtual void OnStart(SAppContext& InAppContext) {};
	virtual void OnStop(SAppContext& InAppContext) {};

	virtual EStateTickResult Tick(float InTimeDelta, SAppContext& InAppContext) { return EStateTickResult::Pop; };
	virtual void Render(SAppContext& InAppContext) {};
};

// ----------------------------------------------------------------------