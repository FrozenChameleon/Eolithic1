#pragma once

#include "../gamestate/ComponentType.h"
#include "../gamestate/GameStateManager.h"

typedef struct SpriteBatch SpriteBatch;

void SystemFunc_InitHelper(ComponentType ctype, ComponentType givenType, void (*initRoutine)(Entity owner, void* data), Entity owner);
void SystemFunc_UpdateHelper(ComponentType ctype, void (*updateRoutine)(Entity entity, void* data));
void SystemFunc_DrawHelper(ComponentType ctype, void (*drawRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch);
void SystemFunc_DrawHudHelper(ComponentType ctype, void (*drawHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch);
void SystemFunc_DrawDebugHudHelper(ComponentType ctype, void (*drawDebugHudRoutine)(Entity owner, void* data, SpriteBatch* spriteBatch), SpriteBatch* spriteBatch);
void SystemFunc_UpdateLastRenderPositionHelper(ComponentType ctype, GameState* gameState, void (*updateLastRenderPositionsRoutine)(void* data));
void SystemFunc_ReceiveBroadcastHelper(ComponentType ctype, void (*receiveBroadcastRoutine)(Entity owner, void* data, int broadcastType, int packet1, int packet2, int packet3), int broadcastType, int packet1, int packet2, int packet3);