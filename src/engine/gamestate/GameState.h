#pragma once

#include "GameStateData.h"
#include "GameStateInputData.h"
#include "ReplayDataManager.h"

typedef struct ReplayDataManager ReplayDataManager;
typedef struct ParticleInstance ParticleInstance;
typedef struct SpriteBatch SpriteBatch;

typedef struct GameState
{
	uint64_t _mCurrentReplayFrame;
	bool _mIsRewinding;
	bool _mHasSavedForGameSaveState;
	bool _mDisableRewindTemporarily;
	bool _mDisableRewindingPermanently;
	bool _mClearReplayCacheNextFrame;
	const char* _mName;
	GameStateData _mData;
	GameStateData _mForGameState;
	ReplayDataManager _mReplayDataManager;
#if EDITOR
	bool _mHasSavedDebugSaveState;
	OeGameStateData _mDebugSaveState;
	bool _mIsRewindLooping;
#endif
} GameState;

void GameState_SaveComponentSizesHelper(bool isBinary);
void GameState_ClearReplayCache(GameState* gs);

void GameState_Ctor(GameState* gs, const char* name, bool disableRewinding);

GameStateData* GameState_GetGameStateData(GameState* gs);
const char* GameState_GetName(GameState* gs);
void GameState_SaveComponentSizes(GameState* gs);
ParticleInstance* GameState_GetParticleInstance(GameState* gs, const char* name, float x, float y);
void GameState_RemoveEntity(GameState* gs, Entity entity);
Entity* GameState_GetEntitiesInPlay(GameState* gs);
void GameState_Do_SendBroadcast(GameState* gs, int type, int packet1, int packet2, int packet3);
Entity GameState_BuildNewEntity(GameState* gs);
void GameState_Update(GameState* gs);
void GameState_SetDisableRewindTemporarily(GameState* gs, bool value);
void GameState_SetGameStateToNotRewinding(GameState* gs);
bool GameState_IsRewinding(GameState* gs);
bool GameState_Rewind(GameState* gs);
void GameState_GiveReplayInput(GameState* gs, const GameStateInputData* inputData);
const GameStateInputData* GameState_GetReplayInput(GameState* gs);
void GameState_ClearReplayCacheNextFrame(GameState* gs);
void GameState_Draw(GameState* gs, SpriteBatch* spriteBatch);
void GameState_DrawHud(GameState* gs, SpriteBatch* spriteBatch);
void GameState_DrawDebugHud(GameState* gs, SpriteBatch* spriteBatch);
void GameState_Load(GameState* gs, const char* levelDataToLoad);
Entity GameState_GetEntityInPlay(GameState* gs, int entityNumber);
void GameState_UpdateReplayFrame(GameState* gs);
bool GameState_HasCreatedForGameSaveState(GameState* gs);
void GameState_ClearForGameSaveState(GameState* gs);
void GameState_CreateForGameSaveState(GameState* gs);
void GameState_UseForGameSaveState(GameState* gs);
int GameState_GetRemainingRewindTime(GameState* gs);
bool GameState_IsThereAnyRewindTimeRemaining(GameState* gs);
float GameState_GetPercentageOfRemainingRewindTime(GameState* gs);
ComponentPack* GameState_GetComponentPack(GameState* gs, ComponentType ctype);
bool GameState_HasComponent(GameState* gs, ComponentType ctype, Entity entity);
void* GameState_GetComponent(GameState* gs, ComponentType ctype, Entity entity); //Just another name for Set
void* GameState_Set(GameState* gs, ComponentType ctype, Entity entity);
void* GameState_SetAndInit(GameState* gs, ComponentType ctype, Entity entity);
void GameState_Init(GameState* gs, ComponentType ctype, Entity entity);
void GameState_Unset(GameState* gs, ComponentType ctype, Entity entity);
void GameState_UnsetAll(GameState* gs, ComponentType ctype);
bool GameState_IsAnyEntityInPack(GameState* gs, ComponentType ctype);
void* GameState_GetFirstSetComponent(GameState* gs, ComponentType ctype);
Entity GameState_GetFirstSetEntity(GameState* gs, ComponentType ctype);
void* GameState_TryGetComponent(GameState* gs, ComponentType ctype, Entity entity, bool* wasSuccessful);
void* GameState_TryGetFirstSetComponent(GameState* gs, ComponentType ctype, bool* wasSuccessful);
#if EDITOR
bool GameState_HandleDebugRewindLooping(GameState* gs);
bool GameState_HandleDebugSaveStates(GameState* gs);
void GameState_CreateDebugSaveState(GameState* gs);
void GameState_UseDebugSaveState(GameState* gs);
#endif