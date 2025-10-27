#pragma once

#include "../utils/Macros.h"
#include "../gamestate/ComponentType.h"

typedef struct SpriteBatch SpriteBatch;
typedef struct GameState GameState;
typedef struct System System;

typedef void (*System_InitStringSettingsHereFunc)(System* sys);
typedef void (*System_InitFunc)(System* sys, ComponentType givenType, Entity owner);
typedef void (*System_UpdateFunc)(System* sys);
typedef void (*System_DrawFunc)(System* sys, SpriteBatch* spriteBatch);
typedef void (*System_UpdateLastRenderPositionFunc)(System* sys, GameState* gameState);
typedef void (*System_ReceiveBroadcastFunc)(System* sys, int broadcastType, int packet1, int packet2, int packet3);

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