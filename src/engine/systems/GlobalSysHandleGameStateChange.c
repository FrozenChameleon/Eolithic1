#include "GlobalSysHandleGameStateChange.h"

#include "../gamestate/GameStateManager.h"
#include "GlobalSysHandleGameStateChange.h"

static void Update(void* givenData)
{
	GameStateManager_HandleGameStateChange();
}

System* GlobalSysHandleGameStateChange_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
