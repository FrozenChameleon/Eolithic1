#include "GlobalSysUpdateMapLoadTicker.h"

#include "../gamestate/GameStateManager.h"

static void Update(void* givenData)
{
	GameStateManager_IncrementTicksSinceMapLoad();
}

System* GlobalSysUpdateMapLoadTicker_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
