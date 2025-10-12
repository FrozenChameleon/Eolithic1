#pragma once

#include "../utils/Macros.h"
#include "../gamestate/ComponentType.h"

typedef struct SpriteBatch SpriteBatch;
typedef struct GameState GameState;

typedef void (*System_InitStringSettingsHereFunc)(void* sys);
typedef void (*System_InitFunc)(void* sys, ComponentType givenType, Entity owner);
typedef void (*System_UpdateFunc)(void* sys);
typedef void (*System_DrawFunc)(void* sys, SpriteBatch* spriteBatch);
typedef void (*System_UpdateLastRenderPositionFunc)(void* sys, GameState* gameState);
typedef void (*System_ReceiveBroadcastFunc)(void* sys, int broadcastType, int packet1, int packet2, int packet3);

typedef struct System
{
	void* _mData;
	System_InitStringSettingsHereFunc _mInitStringSettingsHere;
	System_InitFunc _mInit;
	System_UpdateFunc _mUpdate;
	System_DrawFunc _mDraw;
	System_DrawFunc _mDrawHud;
	System_DrawFunc _mDrawDebugHud;
	System_UpdateLastRenderPositionFunc _mUpdateLastRenderPosition;
	System_ReceiveBroadcastFunc _mReceiveBroadcast;
} System;

System* System_Create();