#include "SystemFunc.h"

#include "../gamestate/PackIterator.h"
#include "../core/Func.h"

void SystemFunc_InitHelper(ComponentType ctype, ComponentType givenType, void(*initRoutine)(Entity owner, void* data), Entity owner)
{
	if (ctype != givenType)
	{
		return;
	}

	initRoutine(owner, GameStateManager_GetComponent(ctype, owner));
}
void SystemFunc_UpdateHelper(ComponentType ctype, void(*updateRoutine)(Entity entity, void* data))
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		if (!Is_UpdateDisabled(iter.mEntity))
		{
			updateRoutine(iter.mEntity, ComponentPack_GetComponentAtIndex(pack, iter.mIndex));
		}
	}
}
void SystemFunc_DrawHelper(ComponentType ctype, void(*drawRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch)
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		if (!Is_DrawDisabled(iter.mEntity))
		{
			drawRoutine(iter.mEntity, ComponentPack_GetComponentAtIndex(pack, iter.mIndex), spriteBatch);
		}
	}
}
void SystemFunc_DrawHudHelper(ComponentType ctype, void(*drawHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch)
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		drawHudRoutine(iter.mEntity, ComponentPack_GetComponentAtIndex(pack, iter.mIndex), spriteBatch);
	}
}
void SystemFunc_DrawDebugHudHelper(ComponentType ctype, void(*drawDebugHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch)
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		drawDebugHudRoutine(iter.mEntity, ComponentPack_GetComponentAtIndex(pack, iter.mIndex), spriteBatch);
	}
}
void SystemFunc_UpdateLastRenderPositionHelper(ComponentType ctype, GameState* gameState, void(*updateLastRenderPositionsRoutine)(void* data))
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		updateLastRenderPositionsRoutine(ComponentPack_GetComponentAtIndex(pack, iter.mIndex));
	}
}
void SystemFunc_ReceiveBroadcastHelper(ComponentType ctype, void(*receiveBroadcastRoutine)(Entity owner, void* data, int32_t broadcastType, int32_t packet1, int32_t packet2, int32_t packet3), int32_t broadcastType, int32_t packet1, int32_t packet2, int32_t packet3)
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		receiveBroadcastRoutine(iter.mEntity, ComponentPack_GetComponentAtIndex(pack, iter.mIndex), broadcastType, packet1, packet2, packet3);
	}
}