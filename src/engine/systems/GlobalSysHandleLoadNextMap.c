#include "GlobalSysHandleLoadNextMap.h"

#include "../gamestate/GameStateManager.h"
#include "GlobalSysHandleLoadNextMap.h"

static void Update(void* givenData)
{
	GameStateManager_HandleLoadNextMap();
}

System* GlobalSysHandleLoadNextMap_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
