#pragma once

#include "../utils/Macros.h"

typedef struct GameStateData GameStateData;
typedef struct SpriteBatch SpriteBatch;
typedef struct ThingInstance ThingInstance;
typedef struct LevelData LevelData;
typedef struct Resource Resource;
typedef struct Camera Camera;
typedef struct Body Body;

//supposed to be protected
void GameHelper_DoDefaultSetupThingInstanceSettings(ThingInstance* instance, bool ignoreWarnings);
Resource* GameHelper_GetDefaultLevelDataResource();
LevelData* GameHelper_GetDefaultLevelData();
void GameHelper_UpdateLastRenderPositionNormally();
Camera* GameHelper_GetDefaultCameraForRender();
//void GameHelper_AddSound(std::vector<OeStringPair>& list, const std::string& key, const std::string& value);
float GameHelper_GetDefaultPostGameBrightness();
void GameHelper_UpdateGlobalSystemsNormally();
void GameHelper_DrawGlobalSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_DrawHudGlobalSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_DrawDebugHudGlobalSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_UpdateStateSystemsNormally();
void GameHelper_DrawStateSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_DrawHudStateSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_DrawDebugHudStateSystemsNormally(SpriteBatch* spriteBatch);
void GameHelper_CreateDefaultGameStates();
//void GameHelper_CreateGameStateDataHelper(OeGameStateData* gameStateData, std::unordered_map<std::string, int>& sizes);
//void GameHelper_CreateDefaultGlobalSystems(std::vector<OeSystem*>& systems);
//void GameHelper_CreateDefaultBindings(std::vector<std::string>& strings, std::vector<OeInputAction>& input);
void GameHelper_AddStringsHelper();

//supposed to be public
enum
{
	COMPONENT_SCAN_RANGE = 1000
};

extern const float GAME_HELPER_DEFAULT_GRAVITY_DECELERATION;
extern const float GAME_HELPER_DEFAULT_GRAVITY_DECELERATION_MAX;
extern const int GAME_HELPER_DEFAULT_MOVING_PLATFORM_LEEWAY;

extern int GAME_HELPER_PLATFORM_UP;
extern int GAME_HELPER_PLATFORM_DOWN;
extern int GAME_HELPER_PLATFORM_RIGHT;
extern int GAME_HELPER_PLATFORM_LEFT;

#if EDITOR
void GameHelper_OnDebugFastResetPlusMove();
#endif
void GameHelper_Initialize();
void GameHelper_OnLoadingStart();
void GameHelper_OnLoadingAfterResources();
//void GameHelper_WriteSessionData(std::shared_ptr<OeIniWriter> writer);
//void GameHelper_ReadSessionData(std::shared_ptr<OeIniReader> reader);
void GameHelper_SetupThingInstanceSettings(ThingInstance* instance, bool ignoreWarnings);
Resource* GameHelper_GetLevelDataResource();
LevelData* GameHelper_GetLevelData();
void GameHelper_UpdateLastRenderPosition();
Camera* GameHelper_GetCameraForRender();
void GameHelper_BuildAchievementList();
void GameHelper_OnNormalGameStateChange();
const char* GameHelper_DebugGiveNextLevel();
float GameHelper_GetMovingPlatformLeeway();
float GameHelper_GetPostGameBrightness();
void GameHelper_UpdateGlobalSystems();
void GameHelper_DrawGlobalSystems(SpriteBatch* spriteBatch);
void GameHelper_DrawHudGlobalSystems(SpriteBatch* spriteBatch);
void GameHelper_DrawDebugHudGlobalSystems(SpriteBatch* spriteBatch);
bool GameHelper_HandleRewindBeforeUpdatingStateSystems();
void GameHelper_UpdateStateSystems();
void GameHelper_DrawStateSystems(SpriteBatch* spriteBatch);
void GameHelper_DrawHudStateSystems(SpriteBatch* spriteBatch);
void GameHelper_DrawDebugHudStateSystems(SpriteBatch* spriteBatch);
void GameHelper_CreateGameStates();
GameStateData* GameHelper_CreateGameStateData(const char* name);
//GameSaveData* GameHelper_CreateGameSaveData();
//void GameHelper_InitGameState(const std::string& levelToLoad);
//void GameHelper_CreateStateSystems(std::vector<OeSystem*>& systems);
//void GameHelper_CreateGlobalSystems(std::vector<OeSystem*>& systems);
void GameHelper_InitPoolsForEngine();
void GameHelper_InitPoolsForGame();
float GameHelper_GetGravityDecelerationMax();
float GameHelper_GetGravityDeceleration();
//std::type_index GameHelper_BuildControllerComponent(int number, OeEntity entity);
//std::vector<std::string> GameHelper_GetControllerComponentStringArray();
//std::unordered_map<int, int> GameHelper_GetControllerComponentTypeMap();
void GameHelper_SetupPlatformTypes();
bool GameHelper_IsCollisionSolidForLineOfSight(int collision);
bool GameHelper_IsCollisionSolidForPathFinding(int collision, int currentX, int currentY, int newX, int newY);
//void GameHelper_DefaultBindings(std::vector<std::string>& strings, std::vector<OeInputAction>& input);
//void GameHelper_SetupMusicAndSfxList(std::vector<OeStringPair>& music, std::vector<OeStringPair>& sfx);
const char* GameHelper_ReturnInputDisplayMask(const char* displayName);
void GameHelper_AddStrings();
//void GameHelper_AddDefaultThingSettings(std::vector<OeStringPair>& pairs);
//const std::vector<std::string>& GameHelper_GetAllTheRecordings();
//void GameHelper_BakedCollisionCheck(float x, float y, int collisionToCheck, OeBody* bodyRef, bool vertical, OeCollisionCheckData* data);
void* GameHelper_CreateGameSaveData();