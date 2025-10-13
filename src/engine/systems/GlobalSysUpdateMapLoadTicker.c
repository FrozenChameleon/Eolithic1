#include "GlobalSysUpdateMapLoadTicker.h"

#include "../gamestate/GameStateManager.h"

static void Update(System* sys)
{
	GameStateManager_IncrementTicksSinceMapLoad();
}

System* GlobalSysUpdateMapLoadTicker_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
