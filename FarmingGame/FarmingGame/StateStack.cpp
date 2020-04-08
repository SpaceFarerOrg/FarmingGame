#include "StateStack.h"

#include "BaseState.h"

#include "ContextServiceProvider.h"

// ----------------------------------------------------------------------

CStateStack::CStateStack(CContextServiceProvider& InServiceProvider)
	: ServiceProvider(InServiceProvider)
{
}

// ----------------------------------------------------------------------

void CStateStack::PushState(CBaseState* InState)
{
	States.push_back(InState);
	States.back()->OnStart(ServiceProvider);
}

// ----------------------------------------------------------------------

void CStateStack::PopState()
{
	States.back()->OnStop(ServiceProvider);
	delete States.back();
	States.pop_back();
}

// ----------------------------------------------------------------------

bool CStateStack::IsEmpty() const
{
	return States.empty();
}

// ----------------------------------------------------------------------

void CStateStack::Tick(float InDeltaTime)
{
	TickLayer(InDeltaTime, States.size() - 1);
}

// ----------------------------------------------------------------------

void CStateStack::Draw()
{
	if (IsEmpty())
	{
		return;
	}

	DrawLayer(States.size() - 1);
}

// ----------------------------------------------------------------------

void CStateStack::TickLayer(float InDeltaTime, unsigned int LayerToTick)
{
	if (States[LayerToTick]->GetType() == EStateType::OverlayTickAndRenderUnderlying)
	{
		TickLayer(InDeltaTime, LayerToTick - 1);
	}

	if (States[LayerToTick]->Tick(InDeltaTime, ServiceProvider) == EStateTickResult::Pop)
	{
		PopState();
	}
}

// ----------------------------------------------------------------------

void CStateStack::DrawLayer(unsigned int LayerToRender)
{
	if (States[LayerToRender]->GetType() == EStateType::OverlayTickAndRenderUnderlying
		|| States[LayerToRender]->GetType() == EStateType::OverlayRenderUnderlying)
	{
		DrawLayer(LayerToRender - 1);
	}

	States[LayerToRender]->Render(ServiceProvider);
}

// ----------------------------------------------------------------------
