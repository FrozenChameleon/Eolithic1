#include "GameStateData.h"

#include "../utils/Utils.h"
#include "GameStateDataHelper.h"

static const int32_t ENTITY_COUNTER_MAX = 2000000000;

void GameStateData_Ctor(GameStateData* gsd)
{
	Utils_memset(gsd, 0, sizeof(GameStateData));

	GameStateDataHelper_InitAllComponentPacks(gsd);
}
ComponentPack* GameStateData_GetComponentPack(GameStateData* gsd, ComponentType ctype)
{
	return &gsd->mComponentPacks[ctype];
}
void GameStateData_Reset(GameStateData* gsd)
{
	gsd->mEntityCounter = GAME_STATE_DATA_INITIAL_ENTITY_NUMBER;
	for (int i = 0; i < COMPONENT_TYPE_LEN; i += 1)
	{
		ComponentPack_UnsetAll(&gsd->mComponentPacks[i]);
	}
}
Entity GameStateData_GetEntityInPlay(GameStateData* gsd, Entity entityNumber)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, C_TagIsInPlay);
	int loc = ComponentPack_GetEntityLocation(pack, entityNumber);
	if (loc == -1)
	{
		return ENTITY_NOTHING;
	}
	return pack->Entities[loc];
}
void GameStateData_RemoveEntity(GameStateData* gsd, Entity entity)
{
	for (int i = 0; i < COMPONENT_TYPE_LEN; i += 1)
	{
		ComponentPack_Unset(&gsd->mComponentPacks[i], entity);
	}
}
void GameStateData_FillListWithEntitiesInPlay(GameStateData* gsd, Entity* list)
{
	//TODO C99
}
Entity GameStateData_BuildNewEntity(GameStateData* gsd)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, C_TagIsInPlay);
	Entity newEntity = gsd->mEntityCounter;
	ComponentPack_Set(pack, newEntity);
	gsd->mEntityCounter += 1;
	if ((gsd->mEntityCounter >= ENTITY_COUNTER_MAX) || (gsd->mEntityCounter < 0))
	{
		gsd->mEntityCounter = GAME_STATE_DATA_INITIAL_ENTITY_NUMBER;
	}
	return newEntity;
}
void GameStateData_CopyTo(GameStateData* from, GameStateData* to)
{
	to->mEntityCounter = from->mEntityCounter;
	for (int i = 0; i < COMPONENT_TYPE_LEN; i += 1)
	{
		ComponentPack_CopyTo(&from->mComponentPacks[i], &to->mComponentPacks[i]);
	}
}
bool GameStateData_IsAnyEntityInPack(GameStateData* gsd, ComponentType ctype)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_IsAnyEntityInPack(pack);
}
void* GameStateData_GetFirstSetComponent(GameStateData* gsd, ComponentType ctype)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_GetFirstSetComponent(pack);
}
Entity GameStateData_GetFirstSetEntity(GameStateData* gsd, ComponentType ctype)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_GetFirstSetEntity(pack);
}
bool GameStateData_HasComponent(GameStateData* gsd, ComponentType ctype, Entity entity)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_HasComponent(pack, entity);
}
void* GameStateData_Set(GameStateData* gsd, ComponentType ctype, Entity entity)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_Set(pack, entity);
}
void* GameStateData_SetAndInit(GameStateData* gsd, ComponentType ctype, Entity entity)
{
	void* component = GameStateData_Set(gsd, ctype, entity);
	if (entity != ENTITY_NOTHING)
	{
		GameStateData_Init(gsd, ctype, entity);
	}
	return component;
}
void GameStateData_Init(GameStateData* gsd, ComponentType ctype, Entity entity)
{
	//TODO C99
	/*
	std::type_index componentType = std::type_index(typeid(T));
	for (int i = 0; i < OeGameStateManager::StateSystems.size(); i++)
	{
		OeGameStateManager::StateSystems[i]->Init(componentType, entity);
	}
	*/
}
void GameStateData_Unset(GameStateData* gsd, ComponentType ctype, Entity entity)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	ComponentPack_Unset(pack, entity);
}
void GameStateData_UnsetAll(GameStateData* gsd, ComponentType ctype)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	ComponentPack_UnsetAll(pack);
}
void* GameStateData_TryGetFirstSetComponent(GameStateData* gsd, ComponentType ctype, bool* wasSuccessful)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_TryGetFirstSetComponent(pack, wasSuccessful);
}
void* GameStateData_TryGetComponent(GameStateData* gsd, ComponentType ctype, Entity entity, bool* wasSuccessful)
{
	ComponentPack* pack = GameStateData_GetComponentPack(gsd, ctype);
	return ComponentPack_TryGetComponent(pack, entity, wasSuccessful);
}