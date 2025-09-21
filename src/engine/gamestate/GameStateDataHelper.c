//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "GameStateDataHelper.h"
#include "ComponentType.h"

#include "../components/AnchorData.h"
#include "../components/BounceData.h"
#include "../components/Camera.h"

#define GSD_INITIAL_SIZE 4

void GameStateDataHelper_InitAllComponentPacks(GameStateData* gsd)
{
    ComponentPack_Init(&gsd->mComponentPacks[C_AnchorData], sizeof(AnchorData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_BounceData], sizeof(BounceData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Camera], sizeof(Camera), GSD_INITIAL_SIZE);
}
