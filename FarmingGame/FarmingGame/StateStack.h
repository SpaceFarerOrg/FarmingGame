#pragma once
#include <vector>

class CBaseState;
class CContextServiceProvider;

// ----------------------------------------------------------------------

class CStateStack
{
public:
	CStateStack( CContextServiceProvider& InServiceProvider );

	void PushState(CBaseState* InState);
	void PopState();
	
	void Tick(float InDeltaTime);
	void Draw();

	bool IsEmpty() const;
private:
	void TickLayer(float InDeltaTime, unsigned int LayerToTick);
	void DrawLayer(unsigned int LayerToRender);

	std::vector< CBaseState* > States;
	CContextServiceProvider& ServiceProvider;
};

// ----------------------------------------------------------------------