#include "LevelFrameCounterSys.h"

#include "../core/Func.h"
#include "../gamestate/ComponentPack.h"
#include "../gamestate/GameStateManager.h"
#include "../gamestate/GameState.h"

static void Update(void* givenData)
{
	ComponentPack* pack = Get_ComponentPack(C_LevelFrameCounter);

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		((LevelFrameCounter*)iter.mComponent)->mCounter += 1;
	}
}

System* LevelFrameCounterSys_CreateSystem(void)
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
