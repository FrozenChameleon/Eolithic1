#include "GameStateData.h"

#include "../utils/Utils.h"
#include "GameStateDataHelper.h"

void GameStateData_Init(GameStateData* gsd)
{
	Utils_memset(gsd, 0, sizeof(GameStateData));

	GameStateDataHelper_InitAllComponentPacks(gsd);
}
ComponentPack* GameStateData_GetComponentPack(GameStateData* gsd, ComponentType type)
{
	return &gsd->mComponentPacks[type];
}
