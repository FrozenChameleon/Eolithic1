#include "Func.h"

#include "../gamestate/GameStateManager.h"

bool Is_UpdateDisabled(Entity entity)
{
	//TODO C99
	return false;
}

bool Is_DrawDisabled(Entity entity)
{
	//TODO C99
	return false;
}



Body* Get_Body(Entity entity)
{
	//TODO
	return NULL;
}

GameState* Get_ActiveGameState()
{
	return GameStateManager_GetGameState();
}

void* Get_Component(ComponentType ctype, Entity entity)
{
	return GameStateManager_Set(ctype, entity);
}
void* Do_InitComponent(ComponentType ctype, Entity entity)
{
	return GameStateManager_SetAndInit(ctype, entity);
}
Entity Get_ChildByComponent(ComponentType ctype, Entity entity)
{
	return ENTITY_NOTHING;
	//TODO C99return Get_ChildByComponent<T>(entity, 0);
}
