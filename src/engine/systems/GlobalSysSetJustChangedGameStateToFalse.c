#include "GlobalSysSetJustChangedGameStateToFalse.h"

#include "../gamestate/GameStateManager.h"

static void Update(System* sys)
{
	GameStateManager_HandleJustChangedGameStateThisFrame();
}

System* GlobalSysSetJustChangedGameStateToFalse_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
