#include "GameStateManager.h"

#include "../utils/Cvars.h"
#include "../systems/System.h"
#include "../../third_party/stb_ds.h"
#include "../core/GameHelper.h"
#include "../audio/Music.h"
#include "../audio/SoundEffect.h"
#include "../globals/Globals.h"
#include "../core/GameUpdater.h"
#include "../utils/Logger.h"
#include "../input/RecordingTool.h"
#include "../utils/Utils.h"

static int32_t _mUniqueMapSeed;
static int32_t _mCurrentGameState;
static int32_t _mCurrentGameStateForRenderCamera;
static int32_t _mNextGameState;
static uint64_t _mTicksSinceMapLoad;
static MString* _mMapToLoad;
static bool _mJustChangedGameStateThisFrame;
static System** arr_global_systems;
static System** arr_state_systems;
static GameState _mGameState;
static bool _mHasRunCtor;

void GameStateManager_Ctor()
{
	if (_mHasRunCtor)
	{
		return;
	}

	MString_Assign(&_mMapToLoad, EE_STR_EMPTY);
	GameState_Ctor(&_mGameState, "WHATEVER", false);

	_mHasRunCtor = true;
}

int32_t GameStateManager_GetGlobalSystemsLen()
{
	return arrlen(arr_global_systems);
}
System** GameStateManager_GetGlobalSystems()
{
	return arr_global_systems;
}
void GameStateManager_AddGlobalSystem(System* sys)
{
	arrput(arr_global_systems, sys);
}
int32_t GameStateManager_GetStateSystemsLen()
{
	return arrlen(arr_state_systems);
}
System** GameStateManager_GetStateSystems()
{
	return arr_state_systems;
}
void GameStateManager_AddStateSystem(System* sys)
{
	int len = arrlen(arr_state_systems);
	if (len == 81 || len == 82 || len == 83)
	{
		int hello = 0;
	}
	arrput(arr_state_systems, sys);
}
GameState* GameStateManager_GetGameState()
{
	return &_mGameState;
}
/*GameState* GameStateManager_ActiveGameStateForRenderCamera()
{
	return &_mGameState;
}*/
void GameStateManager_UpdateLastRenderPosition()
{
	GameHelper_UpdateLastRenderPosition();
}
void GameStateManager_Tick()
{
	GameHelper_UpdateGlobalSystems();
}
void GameStateManager_Draw(SpriteBatch* spriteBatch)
{
	GameHelper_DrawGlobalSystems(spriteBatch);
}
void GameStateManager_DrawHud(SpriteBatch* spriteBatch)
{
	GameHelper_DrawHudGlobalSystems(spriteBatch);
}
void GameStateManager_DrawDebugHud(SpriteBatch* spriteBatch)
{
	GameHelper_DrawDebugHudGlobalSystems(spriteBatch);
}
void GameStateManager_InitDefaultNormalState()
{
	GameStateManager_LoadMap(Cvars_Get(CVARS_ENGINE_DEFAULT_MAP));
}
void GameStateManager_InitDefaultPauseState()
{
	return;
	//WILLNOTDO 05152023
	/*
	if (OeResourceManagers.LevelDataManager.HasResource(OeCvars::Get(OeCvars::ENGINE_PAUSE_MENU_MAP)))
	{
		ActiveGameState.Load(OeCvars::Get(OeCvars::ENGINE_PAUSE_MENU_MAP));
		OeEntity entity = ActiveGameState.BuildNewEntity();
		OeFunc.Do_SetBoolTag<OeTagIsPauseScene>(entity, true);
		Logger.LogInformation("Loaded pause menu map");
	}
	else
	{
		Logger.LogInformation("No pause menu map present");
	}
	*/
}
void GameStateManager_SetGameState(int value)
{
	GameStateManager_SetGameState2(value, false);
}
void GameStateManager_SetGameState2(int value, bool forceNow)
{
	_mNextGameState = value;
	if (forceNow)
	{
		GameStateManager_HandleGameStateChange();
	}
}
void GameStateManager_DebugDrawInfoHelper(int* counter, SpriteBatch* spriteBatch, const char* text)
{
	//TODO C99
	/*
	int dist = 24;
	std::string font = "editor";
	spriteBatch->DrawString(font, text, OeColors::YELLOW, 100, Vector2(0, *counter * dist));
	*counter += 1;
	* */
}
InputPlayer* GameStateManager_GetPlayerInput(Entity thing)
{
	return NULL;
	//WILLOTDO 05152023
	//int playerNumber = OeFunc.Get_PlayerNumber(thing);
	//return OeInput.GetPlayer(playerNumber);
}
Camera* GameStateManager_GetCurrentRenderCamera()
{
#if EDITOR
	//WILLOTDO 05152023
	/*
	if (OeGlobals.DEBUG_IS_EDITOR_MODE)
	{
		return ref OeEditor.Camera;
	}
	*/
#endif
	return GameHelper_GetCameraForRender();
}
void GameStateManager_DebugForceLoadMapNow(const char* map)
{
	GameStateManager_SetupLoadMap(map);
	GameStateManager_HandleLoadNextMap();
}
void GameStateManager_SetupLoadMap(const char* s)
{
	GameStateManager_SetGameState(GAMESTATEMANAGER_GAME_STATE_NORMAL);
	MString_Assign(&_mMapToLoad, s);
}
void GameStateManager_SetupReloadMap()
{
	GameStateManager_SetGameState(GAMESTATEMANAGER_GAME_STATE_NORMAL);
	MString_Assign(&_mMapToLoad, GameStateManager_GetCurrentFileName());
}
const char* GameStateManager_GetCurrentFileName()
{
	//TODO C99
	return NULL;
	//return Func::Get_LevelDataResource()->GetName();
}
void GameStateManager_DebugForceReloadMapNow()
{
	GameStateManager_SetupLoadMap(GameStateManager_GetCurrentFileName());
	GameStateManager_HandleLoadNextMap();
}
void GameStateManager_SetupLoadMapWithRecording(const char* recordingName)
{
	//WILLOTDO 05152023
/*
string filename = OeStringTools.JavaSubString(recordingName, recordingName.IndexOf('{') + 1, recordingName.IndexOf('}'));
_mMapToLoad = filename;
*/
}
void GameStateManager_LoadMap(const char* mapToLoad)
{
	if(mapToLoad == NULL)
	{
		Logger_LogWarning("Attempted to load NULL map!");
		return;
	}
	else if (Utils_StringEqualTo(mapToLoad, EE_STR_NOT_SET))
	{
		Logger_LogWarning("Attempted to load EMPTY STRING map!");
		return;
	}

	Logger_printf("Attempting to load map: %s\n", mapToLoad);

	Music_SetDoNotAllowUpdatesWhilePaused(false);

	//TODO 2024, DISABLING THIS COMPLETELY FOR C++? 
	/*
	if (!OeCvars::GetAsBool(OeCvars::ENGINE_LOAD_ALL_MOVIES))
	{
		OeResourceManagers::MovieTextureManager.Dispose();
	}
	*/

	//WILLNOTDO 05152023
	/*if (!OeResourceManagers::LevelDataManager.HasResource(mapToLoad))
	{
		std::string path = OeFile::Combine(OeLevelData::LEVEL_DATA_DIRECTORY[0], mapToLoad + ".bin");
		OeResourceManagers.LevelDataManager.CreateResource(path, new OeLevelData());
		Logger.LogError("Unable to load map " + mapToLoad + ", created new level resource in memory for " + path);
	}*/

#if EDITOR
	GLOBALS_DEBUG_IS_META_MAP_EDIT_TILE_MODE_AT_MAP_LOAD = Cvars_GetAsBool(CVARS_EDITOR_META_MAP_EDIT_TILE_MODE);
	//WILLNOTDO 05152023 OeConsole.CloseConsole();
#endif

	_mTicksSinceMapLoad = 0;
	/*
	if (!OeRecordingTool::IsReading())
	{
		_mUniqueMapSeed = SDL_GetTicks64() % INT_MAX;
		if (!OeCvars::GetAsBool(OeCvars::ENGINE_DISABLE_NORMAL_RECORDINGS))
		{
			OeRecordingTool::SetupWriteSession(0, mapToLoad);
		}
	}
	*/

	GameState_Load(&_mGameState, mapToLoad);

	SoundEffect_StopAllPausedSounds();

#ifdef DEBUG_DEF_USE_TIME_RANDOM_FOR_SHARED_RANDOM
	Random32_SetSeed(Globals_GetSharedRandom(), (uint32_t)(OeGlobals::GetTimeForRandomSeed()));
#else
	Random32_SetSeed(Globals_GetSharedRandom(), (uint32_t)(GameUpdater_GetGlobalTicks()));
#endif

	Logger_printf("Map loaded: %s\n", mapToLoad);
	GLOBALS_DEBUG_JUST_LOADED_MAP_NOTIFY_EDITOR = true;
}
bool GameStateManager_IsNormalState()
{
	return _mCurrentGameState == GAMESTATEMANAGER_GAME_STATE_NORMAL;
}
bool GameStateManager_IsPausedState()
{
	return _mCurrentGameState == GAMESTATEMANAGER_GAME_STATE_PAUSED;
}
void GameStateManager_HandleGameStateChange()
{
	if (_mNextGameState == -1)
	{
		return;
	}

	_mCurrentGameState = _mNextGameState;
	_mCurrentGameStateForRenderCamera = _mNextGameState;

	_mNextGameState = -1;
	_mJustChangedGameStateThisFrame = true;

	GameHelper_OnNormalGameStateChange();
}
void GameStateManager_HandleLoadNextMap()
{
	bool isMapLoad = false;
	if (!MString_EqualToString(_mMapToLoad, EE_STR_EMPTY))
	{
		isMapLoad = true;
	}

	if (RecordingTool_LoadNextRecordingIfAtEndOfRecording(isMapLoad))
	{
		MString_Assign(&_mMapToLoad, EE_STR_EMPTY);
		return;
	}

	if (!isMapLoad)
	{
		return;
	}

	GameStateManager_LoadMap(MString_GetText(_mMapToLoad));
	MString_Assign(&_mMapToLoad, EE_STR_EMPTY);
}
bool GameStateManager_JustChangedGameStateThisFrame()
{
	return _mJustChangedGameStateThisFrame;
}
void GameStateManager_HandleJustChangedGameStateThisFrame()
{
	_mJustChangedGameStateThisFrame = false;
}
void GameStateManager_SetCurrentGameStateForRenderCamera(int value)
{
	_mCurrentGameStateForRenderCamera = value;
}
int GameStateManager_GetCurrentGameState()
{
	return _mCurrentGameState;
}
void GameStateManager_SetCurrentGameState(int value)
{
	_mCurrentGameState = value;
}
void GameStateManager_IncrementTicksSinceMapLoad()
{
	_mTicksSinceMapLoad += 1;
}
uint64_t GameStateManager_GetTicksSinceMapLoad()
{
	return _mTicksSinceMapLoad;
}
int GameStateManager_GetUniqueMapSeed()
{
	return _mUniqueMapSeed;
}
void GameStateManager_SetUniqueMapSeed(int value)
{
	_mUniqueMapSeed = value;
}
#if EDITOR
void GameStateManager_SaveComponentSizes()
{

}
#endif

ComponentPack* GameStateManager_GetComponentPack(ComponentType ctype)
{
	return GameState_GetComponentPack(&_mGameState, ctype);
}
bool GameStateManager_HasComponent(ComponentType ctype, Entity entity)
{
	return GameState_HasComponent(&_mGameState, ctype, entity);
}
void* GameStateManager_GetComponent(ComponentType ctype, Entity entity) //Just another name for Set
{
	return GameState_Set(&_mGameState, ctype, entity);
}
void* GameStateManager_Set(ComponentType ctype, Entity entity)
{
	return GameState_Set(&_mGameState, ctype, entity);
}
void* GameStateManager_SetAndInit(ComponentType ctype, Entity entity)
{
	return GameState_SetAndInit(&_mGameState, ctype, entity);
}
void GameStateManager_Init(ComponentType ctype, Entity entity)
{
	GameState_Init(&_mGameState, ctype, entity);
}
void GameStateManager_Unset(ComponentType ctype, Entity entity)
{
	GameState_Unset(&_mGameState, ctype, entity);
}
void GameStateManager_UnsetAll(ComponentType ctype)
{
	GameState_UnsetAll(&_mGameState, ctype);
}
bool GameStateManager_IsAnyEntityInPack(ComponentType ctype)
{
	return GameState_IsAnyEntityInPack(&_mGameState, ctype);
}
void* GameStateManager_GetFirstSetComponent(ComponentType ctype)
{
	return GameState_GetFirstSetComponent(&_mGameState, ctype);
}
Entity GameStateManager_GetFirstSetEntity(ComponentType ctype)
{
	return GameState_GetFirstSetEntity(&_mGameState, ctype);
}
void* GameStateManager_TryGetComponent(ComponentType ctype, Entity entity, bool* wasSuccessful)
{
	return GameState_TryGetComponent(&_mGameState, ctype, entity, wasSuccessful);
}
void* GameStateManager_TryGetFirstSetComponent(ComponentType ctype, bool* wasSuccessful)
{
	return GameState_TryGetFirstSetComponent(&_mGameState, ctype, wasSuccessful);
}