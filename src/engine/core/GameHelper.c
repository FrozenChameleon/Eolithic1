#include "GameHelper.h"

#include "../gamestate/GameStateManager.h"
#include "../systems/System.h"
#include "../input/InputBindings.h"
#include "../input/ActionList.h"
#include "../input/Keys.h"
#include "../input/Buttons.h"
#include "../leveldata/ThingInstance.h"
#include "../systems/GlobalSysDrawFPS.h"
#include "../systems/GlobalSysHideMouse.h"
#include "../systems/GlobalSysHandleGameStateChange.h"
#include "../systems/GlobalSysHandleLoadNextMap.h"
#include "../systems/GlobalSysUpdateManagers.h"
#include "../systems/GlobalSysTickSoundEffect.h"
#include "../systems/GlobalSysTickMusic.h"
#include "../systems/GlobalSysUpdateInput.h"
//#include "../systems/OeGlobalSysConsole.h"
#include "../systems/GlobalSysDefaultState.h"
#include "../systems/GlobalSysUpdateMapLoadTicker.h"
#include "../systems/GlobalSysSetJustChangedGameStateToFalse.h"
#include "../systems/GlobalSysSaveIcon.h"
#include "../systems/GlobalSysUpdateAchievementHandler.h"
#include "../gamestate/GameState.h"
#include "../core/Func.h"
#include "../components/LevelDataStubFunc.h"
#include "../components/Camera.h"
#include "../../engine/io/File.h"
#include "../../engine/utils/Utils.h"
#include "../leveldata/ThingInstance.h"

static struct { int key; int value; } _mControllerComponentTypeMap;
static IStringArray* _mControllerComponentStrArray;
//static std_unordered_map<std_string, std_unordered_map<std_string, int>> _mComponentSizes;

const float GAMEHELPER_DEFAULT_GRAVITY_DECELERATION = 0.233f;
const float GAMEHELPER_DEFAULT_GRAVITY_DECELERATION_MAX = 5.25f;
const int GAMEHELPER_DEFAULT_MOVING_PLATFORM_LEEWAY = 1;

int GAMEHELPER_PLATFORM_UP = -1;
int GAMEHELPER_PLATFORM_DOWN = -1;
int GAMEHELPER_PLATFORM_RIGHT = -1;
int GAMEHELPER_PLATFORM_LEFT = -1;

void GameHelper_DoDefaultSetupThingInstanceSettings(ThingInstance* instance, bool ignoreWarnings)
{
	//TODO C99 ThingInstance_SetupSettings(instance, ignoreWarnings);
}

Resource* GameHelper_GetDefaultLevelDataResource()
{
	LevelDataStub* stub = GameState_GetFirstSetComponent(Get_ActiveGameState(), C_LevelDataStub);
	return LevelDataStubFunc_GetLevelDataResource(stub);
}
LevelData* GameHelper_GetDefaultLevelData()
{
	LevelDataStub* stub = GameState_GetFirstSetComponent(Get_ActiveGameState(), C_LevelDataStub);
	return LevelDataStubFunc_GetLevelData(stub);
}
void GameHelper_UpdateLastRenderPositionNormally()
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System** stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = stateSystems[i];
		currentSystem->_mUpdateLastRenderPosition(currentSystem, GameStateManager_GetGameState());
	}
}
Camera* GameHelper_GetDefaultCameraForRender()
{
	return GameStateManager_GetFirstSetComponent(C_Camera);
}
StringPair* GameHelper_AddSound(StringPair* arr_list, const char* key, const char* value)
{
	return NULL;
	//TODO C99 list.push_back(OeStringPair(key, value));
}
float GameHelper_GetDefaultPostGameBrightness()
{
	return 1;
}
void GameHelper_UpdateGlobalSystemsNormally()
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System** globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = globalSystems[i];
		currentSystem->_mUpdate(currentSystem);
	}
}
void GameHelper_DrawGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System** globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = globalSystems[i];
		currentSystem->_mDraw(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawHudGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System** globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = globalSystems[i];
		currentSystem->_mDrawHud(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawDebugHudGlobalSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t globalSystemsLen = GameStateManager_GetGlobalSystemsLen();
	System** globalSystems = GameStateManager_GetGlobalSystems();
	for (int i = 0; i < globalSystemsLen; i += 1)
	{
		System* currentSystem = globalSystems[i];
		currentSystem->_mDrawDebugHud(currentSystem, spriteBatch);
	}
}
void GameHelper_UpdateStateSystemsNormally()
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System** stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = stateSystems[i];
		currentSystem->_mUpdate(currentSystem);
	}
}
void GameHelper_DrawStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System** stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = stateSystems[i];
		currentSystem->_mDraw(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawHudStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System** stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = stateSystems[i];
		currentSystem->_mDrawHud(currentSystem, spriteBatch);
	}
}
void GameHelper_DrawDebugHudStateSystemsNormally(SpriteBatch* spriteBatch)
{
	int32_t stateSystemsLen = GameStateManager_GetStateSystemsLen();
	System** stateSystems = GameStateManager_GetStateSystems();
	for (int i = 0; i < stateSystemsLen; i += 1)
	{
		System* currentSystem = stateSystems[i];
		currentSystem->_mDrawDebugHud(currentSystem, spriteBatch);
	}
}
void GameHelper_CreateDefaultGameStates()
{
	/* //TODO C99?
	OeGameStateManager_GameStates = std_vector<OeGameState*>(2);
	OeGameStateManager_GameStates[OeGameStateManager_GAME_STATE_NORMAL] = new OeGameState("normal", false);
	OeGameStateManager_GameStates[OeGameStateManager_GAME_STATE_PAUSED] = new OeGameState("paused", true);

	GameStateManager_SetCurrentGameState(0);
	GameStateManager_InitDefaultNormalState();

	GameStateManager_SetCurrentGameState(1);
	GameStateManager_InitDefaultPauseState();*/
}
void GameHelper_CreateDefaultGlobalSystems()
{
#if EDITOR
	/* //WILLNOTDO 06242023 DEBUG STUFF
	GameStateManager_AddGlobalSystem(GlobalSysMetaMapHack_CreateSystem()));
	GameStateManager_AddGlobalSystem(GlobalSysUpdateFontMap_CreateSystem()));
	GameStateManager_AddGlobalSystem(GlobalSysDebugMenu_CreateSystem()));
	GameStateManager_AddGlobalSystem(GlobalSysDrawQuickStats_CreateSystem()));
	*/
#endif

	GameStateManager_AddGlobalSystem(GlobalSysHideMouse_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysHandleGameStateChange_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysHandleLoadNextMap_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysUpdateManagers_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysTickSoundEffect_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysTickMusic_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysUpdateInput_CreateSystem());
	//GameStateManager_AddGlobalSystem(GlobalSysConsole_CreateSystem()); //WILLNOTDO 06242023 DEBUG CONSOLE STUFF
	GameStateManager_AddGlobalSystem(GlobalSysDefaultState_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysUpdateMapLoadTicker_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysSetJustChangedGameStateToFalse_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysSaveIcon_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysUpdateAchievementHandler_CreateSystem());
	GameStateManager_AddGlobalSystem(GlobalSysDrawFPS_CreateSystem());
}
void GameHelper_CreateDefaultBindings(IStringArray* strings, InputAction* input)
{
	int64_t len = IStringArray_Length(strings);

	for (int i = 0; i < len; i += 1)
	{
		const char* s = IStringArray_Get(strings, i);

		InputAction* data = &input[i];

		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_A, KEYS_Z);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_X, KEYS_X);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_B, KEYS_C);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_Y, KEYS_V);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LB, KEYS_A);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LT, KEYS_S);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LS, KEYS_D);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RB, KEYS_Q);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RT, KEYS_W);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RS, KEYS_E);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_START, KEYS_Enter);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_SELECT, KEYS_Back);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LS_UP, KEYS_Up);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LS_RIGHT, KEYS_Right);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LS_DOWN, KEYS_Down);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_LS_LEFT, KEYS_Left);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_DIGITAL_UP, KEYS_T);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_DIGITAL_RIGHT, KEYS_H);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_DIGITAL_DOWN, KEYS_G);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_DIGITAL_LEFT, KEYS_F);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RS_UP, KEYS_I);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RS_RIGHT, KEYS_L);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RS_DOWN, KEYS_K);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_RS_LEFT, KEYS_J);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_MENU_SELECT, KEYS_Z);
		InputBindings_SetupKey(data, 0, s, ACTIONLIST_GAME_MENU_BACK, KEYS_X);

		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_A, BUTTONS_A);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_X, BUTTONS_X);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_B, BUTTONS_B);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_Y, BUTTONS_Y);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_LB, BUTTONS_LeftShoulder);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_RB, BUTTONS_RightShoulder);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_LT, INPUT_CHECK_AXIS_LEFT_TRIGGER, 1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_RT, INPUT_CHECK_AXIS_RIGHT_TRIGGER, -1);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_LS, BUTTONS_LeftStick);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_RS, BUTTONS_RightStick);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_START, BUTTONS_Start);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_SELECT, BUTTONS_Back);

		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_LS_LEFT, INPUT_CHECK_AXIS_LEFT_STICK_X, -1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_LS_RIGHT, INPUT_CHECK_AXIS_LEFT_STICK_X, 1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_LS_UP, INPUT_CHECK_AXIS_LEFT_STICK_Y, 1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_LS_DOWN, INPUT_CHECK_AXIS_LEFT_STICK_Y, -1);

		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_RS_LEFT, INPUT_CHECK_AXIS_RIGHT_STICK_X, -1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_RS_RIGHT, INPUT_CHECK_AXIS_RIGHT_STICK_X, 1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_RS_UP, INPUT_CHECK_AXIS_RIGHT_STICK_Y, -1);
		InputBindings_SetupAxis(data, 1, s, ACTIONLIST_GAME_RS_DOWN, INPUT_CHECK_AXIS_RIGHT_STICK_Y, 1);

		InputBindings_SetupButton(data, 2, s, ACTIONLIST_GAME_DIGITAL_LEFT, BUTTONS_DPadLeft);
		InputBindings_SetupButton(data, 2, s, ACTIONLIST_GAME_DIGITAL_RIGHT, BUTTONS_DPadRight);
		InputBindings_SetupButton(data, 2, s, ACTIONLIST_GAME_DIGITAL_UP, BUTTONS_DPadUp);
		InputBindings_SetupButton(data, 2, s, ACTIONLIST_GAME_DIGITAL_DOWN, BUTTONS_DPadDown);

		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_MENU_SELECT, BUTTONS_A);
		InputBindings_SetupButton(data, 1, s, ACTIONLIST_GAME_MENU_BACK, BUTTONS_B);
	}
}
GameStateData* GameHelper_CreateGameStateData(const char* name)
{
	GameStateData* temp = Utils_calloc(1, sizeof(GameStateData));

	/*
	if (!_mComponentSizes.count(name))
	{
		bool isBinary = true;
		std_string extension = OeUtils_GetExtension(isBinary);
		std_string filePath = OeFile_Combine("data", "componentsizes_" + name + extension);
		if (!OeFile_FileExists(filePath))
		{
			return temp;
		}
		std_shared_ptr<OeIniReader> reader = OeIniReader_CreateNewOeIniReader(filePath);
		_mComponentSizes[name] = reader->ReadAsStringIntDictionary();
	}
	*/

	//CreateGameStateDataHelper(temp, _mComponentSizes[name]);

	return temp;
}
void GameHelper_InitPoolsForEngine()
{
	//NOTE 2024 - THIS IS REALLY NOT EVER NECESSARY IN C += 1
	//WILLNOTDO 06242023 FOR MUTE CRIMSON DX?
	/*
	OePool.InitPool<OeLevelCameraDataInstance>(new OeLevelCameraDataInstance());

	OeAutoPool.InitPool<OeEntitySearch>(new OeEntitySearch());
	OeAutoPool.InitPool<OePathNode>(new OePathNode());
	*/
}
IStringArray* GameHelper_GetControllerComponentStringArray()
{
	//WILLNOTDO 06242023 FOR MUTE CRIMSON DX?
	/*
	if (_mControllerComponentStrArray == null)
	{
		_mControllerComponentStrArray = new List<string>();

		OeDictionary<int, Type> map = GetControllerComponentTypeMap();
		for (int i = 0; i < map.Values.Count; i += 1)
		{
			Type o = map.Values[i];
			_mControllerComponentStrArray.Add(o.Name);
		}
	}
		*/
	return _mControllerComponentStrArray;
}
IntIntPair* GameHelper_GetControllerComponentTypeMap()
{
	return NULL;
	//WILLNOTDO 06242023 FOR MUTE CRIMSON DX?
	/*
	if (_mControllerComponentTypeMap == null)
	{
		_mControllerComponentTypeMap = new OeDictionary<int, Type>();
		for (int i = 0; i < COMPONENT_SCAN_RANGE; i += 1)
		{
			Type type = BuildControllerComponent(i, OeEntity.Nothing);
			if (type != null)
			{
				_mControllerComponentTypeMap.Add(i, type);
			}
		}
	}
	*/
	//TODO C99 return _mControllerComponentTypeMap;
}
void GameHelper_AddStrings()
{
	GameHelper_AddStringsHelper();
}
