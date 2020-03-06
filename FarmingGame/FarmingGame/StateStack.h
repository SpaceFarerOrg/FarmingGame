#pragma once
#include <vector>

class CBaseState;
struct SAppContext;

// ----------------------------------------------------------------------

class CStateStack
{
public:
	CStateStack( SAppContext& InAppContext );

	void PushState(CBaseState* InState);
	void PopState();
	
	void Tick(float InDeltaTime);
	void Draw();

	bool IsEmpty() const;
private:
	void TickLayer(float InDeltaTime, unsigned int LayerToTick);
	void DrawLayer(unsigned int LayerToRender);

	std::vector< CBaseState* > States;
	SAppContext& AppContext;
};

// ----------------------------------------------------------------------