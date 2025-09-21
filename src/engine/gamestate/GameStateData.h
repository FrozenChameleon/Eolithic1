#pragma once

#include "../utils/Macros.h"
#include "ComponentType.h"
#include "ComponentPack.h"

#define GAME_STATE_DATA_INITIAL_ENTITY_NUMBER 1

typedef struct GameStateData
{
	int32_t mEntityCounter;
	ComponentPack mComponentPacks[COMPONENT_TYPE_LEN];
} GameStateData;

void GameStateData_Init(GameStateData* gsd);
ComponentPack* GameStateData_GetComponentPack(GameStateData* gsd, ComponentType type);