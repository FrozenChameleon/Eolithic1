#pragma once

#include "GameState.h"
#include "../utils/Macros.h"
#include "../systems/System.h"

typedef struct InputPlayer InputPlayer;
typedef struct SpriteBatch SpriteBatch;

enum GameStateManagerDebugInfo
{
	GAMESTATEMANAGER_DEBUG_INFO_SHOW_NOTHING = 0,
	GAMESTATEMANAGER_DEBUG_INFO_SHOW_QUICK_STATS = 1,
	GAMESTATEMANAGER_DEBUG_INFO_SHOW_THING_VIEWER = 2
};

enum GameStateManagerGameState
{
	GAMESTATEMANAGER_GAME_STATE_NORMAL = 0,
	GAMESTATEMANAGER_GAME_STATE_PAUSED = 1
};

//extern std::vector<OeSystem*> GlobalSystems;
//extern std::vector<OeSystem*> StateSystems;
//extern std::vector<OeGameState*> GameStates;

int32_t GameStateManager_GetGlobalSystemsLen();
System** GameStateManager_GetGlobalSystems();
void GameStateManager_AddGlobalSystem(System* sys);
int32_t GameStateManager_GetStateSystemsLen();
System** GameStateManager_GetStateSystems();
void GameStateManager_AddStateSystem(System* sys);
GameState* GameStateManager_GetGameState();
//GameState* GameStateManager_ActiveGameStateForRenderCamera();
void GameStateManager_UpdateLastRenderPosition();
void GameStateManager_Tick();
void GameStateManager_Draw(SpriteBatch* spriteBatch);
void GameStateManager_DrawHud(SpriteBatch* spriteBatch);
void GameStateManager_DrawDebugHud(SpriteBatch* spriteBatch);
void GameStateManager_InitDefaultNormalState();
void GameStateManager_InitDefaultPauseState();
void GameStateManager_SetGameState(int value);
void GameStateManager_SetGameState2(int value, bool forceNow);
void GameStateManager_DebugDrawInfoHelper(int* counter, SpriteBatch* spriteBatch, const char* text);
InputPlayer* GameStateManager_GetPlayerInput(Entity thing);
Camera* GameStateManager_GetCurrentRenderCamera();
void GameStateManager_DebugForceLoadMapNow(const char* map);
void GameStateManager_SetupLoadMap(const char* s);
void GameStateManager_SetupReloadMap();
const char* GameStateManager_GetCurrentFileName();
void GameStateManager_DebugForceReloadMapNow();
void GameStateManager_SetupLoadMapWithRecording(const char* recordingName);
void GameStateManager_LoadMap(const char* mapToLoad);
bool GameStateManager_IsNormalState();
bool GameStateManager_IsPausedState();
void GameStateManager_HandleGameStateChange();
void GameStateManager_HandleLoadNextMap();
bool GameStateManager_JustChangedGameStateThisFrame();
void GameStateManager_HandleJustChangedGameStateThisFrame();
void GameStateManager_SetCurrentGameStateForRenderCamera(int value);
int GameStateManager_GetCurrentGameState();
void GameStateManager_SetCurrentGameState(int value);
void GameStateManager_IncrementTicksSinceMapLoad();
uint64_t GameStateManager_GetTicksSinceMapLoad();
int GameStateManager_GetUniqueMapSeed();
void GameStateManager_SetUniqueMapSeed(int value);

ComponentPack* GameStateManager_GetComponentPack(ComponentType ctype);
bool GameStateManager_HasComponent(ComponentType ctype, Entity entity);
void* GameStateManager_GetComponent(ComponentType ctype, Entity entity); //Just another name for Set
void* GameStateManager_Set(ComponentType ctype, Entity entity);
void* GameStateManager_SetAndInit(ComponentType ctype, Entity entity);
void GameStateManager_Init(ComponentType ctype, Entity entity);
void GameStateManager_Unset(ComponentType ctype, Entity entity);
void GameStateManager_UnsetAll(ComponentType ctype);
bool GameStateManager_IsAnyEntityInPack(ComponentType ctype);
void* GameStateManager_GetFirstSetComponent(ComponentType ctype);
Entity GameStateManager_GetFirstSetEntity(ComponentType ctype);
void* GameStateManager_TryGetComponent(ComponentType ctype, Entity entity, bool* wasSuccessful);
void* GameStateManager_TryGetFirstSetComponent(ComponentType ctype, bool* wasSuccessful);

#if EDITOR
void GameStateManager_SaveComponentSizes();
#endif
