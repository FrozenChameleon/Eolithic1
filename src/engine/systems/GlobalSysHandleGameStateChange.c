#include "GlobalSysHandleGameStateChange.h"

#include "../gamestate/GameStateManager.h"
#include "GlobalSysHandleGameStateChange.h"

static void Update(System* sys)
{
	GameStateManager_HandleGameStateChange();
}

System* GlobalSysHandleGameStateChange_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
