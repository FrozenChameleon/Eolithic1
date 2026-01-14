#pragma once

#include "../utils/Macros.h"
#include "../input/InputAction.h"
#include "../resources/Resource.h"
#include "../utils/StringPair.h"
#include "../systems/System.h"
#include "../collision/Body.h"
#include "../collision/CollisionCheckData.h"
#include "../components/Camera.h"
#include "../gamestate/GameStateData.h"

typedef struct IntIntPair
{
	int key;
	int value;
} IntIntPair;

typedef struct CharIntPair
{
	char* key;
	int value;
} CharIntPair;

typedef struct SpriteBatch SpriteBatch;
typedef struct LevelData LevelData;
typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;
typedef struct ThingInstance ThingInstance;
typedef struct IStringArray IStringArray;
typedef struct DynamicByteBuffer DynamicByteBuffer;

//supposed to be protected
void GameHelper_DoDefaultSetupThingInstanceSettings(ThingInstance* instance, bool ignoreWarnings);
Resource* GameHelper_GetDefaultLevelDataResource();
LevelData* GameHelper_GetDefaultLevelData();
void GameHelper_UpdateLastRenderPositionNormally();
Camera* GameHelper_GetDefaultCameraForRender();
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
void GameHelper_CreateGameStateDataHelper(GameStateData* gameStateData, CharIntPair* sizes);
void GameHelper_CreateDefaultGlobalSystems();
void GameHelper_CreateDefaultBindings(IStringArray* strings, InputAction* input);
void GameHelper_AddStringsHelper();

//supposed to be public
enum
{
	GAMEHELPER_COMPONENT_SCAN_RANGE = 1000
};

extern const float GAMEHELPER_DEFAULT_GRAVITY_DECELERATION;
extern const float GAMEHELPER_DEFAULT_GRAVITY_DECELERATION_MAX;
extern const int32_t GAMEHELPER_DEFAULT_MOVING_PLATFORM_LEEWAY;

extern int32_t GAMEHELPER_PLATFORM_UP;
extern int32_t GAMEHELPER_PLATFORM_DOWN;
extern int32_t GAMEHELPER_PLATFORM_RIGHT;
extern int32_t GAMEHELPER_PLATFORM_LEFT;

#if EDITOR
void GameHelper_OnDebugFastResetPlusMove();
#endif
void GameHelper_Initialize();
void GameHelper_OnLoadingStart();
void GameHelper_OnLoadingAfterResources();
void GameHelper_WriteSessionData(BufferWriter* writer);
void GameHelper_ReadSessionData(BufferReader* reader);
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
void GameHelper_InitGameStateData(const char* name, GameStateData* initThis);
void* GameHelper_CreateGameSaveData();
void GameHelper_InitGameState(const char* levelToLoad);
void GameHelper_CreateStateSystems();
void GameHelper_CreateGlobalSystems();
void GameHelper_InitPoolsForEngine();
void GameHelper_InitPoolsForGame();
float GameHelper_GetGravityDecelerationMax();
float GameHelper_GetGravityDeceleration();
ComponentType GameHelper_BuildControllerComponent(int number, Entity entity);
IStringArray* GameHelper_GetControllerComponentStringArray();
IntIntPair* GameHelper_GetControllerComponentTypeMap();
void GameHelper_SetupPlatformTypes();
bool GameHelper_IsCollisionSolidForLineOfSight(int collision);
bool GameHelper_IsCollisionSolidForPathFinding(int collision, int32_t currentX, int32_t currentY, int32_t newX, int32_t newY);
void GameHelper_DefaultBindings(IStringArray* strings, InputAction* input);
void GameHelper_SetupMusicAndSfxList(StringPair* music, StringPair* sfx);
const char* GameHelper_ReturnInputDisplayMask(const char* displayName);
void GameHelper_AddStrings();
void GameHelper_AddDefaultThingSettings(StringPair* pairs);
IStringArray* GameHelper_GetAllTheRecordings();
void GameHelper_BakedCollisionCheck(float x, float y, int32_t collisionToCheck, Body* bodyRef, bool vertical, CollisionCheckData* data);
void GameHelper_WriteGameSaveData(void* gsd, DynamicByteBuffer* writer);
void GameHelper_ReadGameSaveData(void* gsd, BufferReader* reader);