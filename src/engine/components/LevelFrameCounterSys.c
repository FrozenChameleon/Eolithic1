#include "LevelFrameCounterSys.h"

#include "../core/Func.h"
#include "../gamestate/ComponentPack.h"
#include "../gamestate/GameStateManager.h"
#include "../gamestate/GameState.h"

static void Update(System* sys)
{
	ComponentPack* pack = Get_ComponentPack(C_LevelFrameCounter);

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		((LevelFrameCounter*)ComponentPack_GetComponentAtIndex(pack, iter.mIndex))->mCounter += 1;
	}
}

System* LevelFrameCounterSys_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
