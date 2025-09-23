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
			updateRoutine(iter.mEntity, &pack->Components[iter.mIndex]);
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
			drawRoutine(iter.mEntity, &pack->Components[iter.mIndex], spriteBatch);
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
		drawHudRoutine(iter.mEntity, &pack->Components[iter.mIndex], spriteBatch);
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
		drawDebugHudRoutine(iter.mEntity, &pack->Components[iter.mIndex], spriteBatch);
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
		updateLastRenderPositionsRoutine(&pack->Components[iter.mIndex]);
	}
}
void SystemFunc_ReceiveBroadcastHelper(ComponentType ctype, void(*receiveBroadcastRoutine)(Entity owner, void* data, int broadcastType, int packet1, int packet2, int packet3), int broadcastType, int packet1, int packet2, int packet3)
{
	ComponentPack* pack = GameStateManager_GetComponentPack(ctype);
	if (!ComponentPack_IsAnyEntityInPack(pack))
	{
		return;
	}

	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		receiveBroadcastRoutine(iter.mEntity, &pack->Components[iter.mIndex], ctype, packet1, packet2, packet3);
	}
}