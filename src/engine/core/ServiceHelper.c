#include "ServiceHelper.h"

#include "../core/Game.h"
#include "../service/Service.h"
#include "../input/Input.h"
#include "../input/InputPlayer.h"
#include "../utils/Cvars.h"
#include "../input/ControllerStates.h"
#include "../input/KeyboardState.h"
#include "../input/MouseState.h"
//TODO C99 #include "../input/RecordingTool.h"
#include "../gamesave/GameSaveManager.h"
#include "../input/InputBindings.h"
#include "../../DebugDefs.h"

enum { PLAYER_LOST_CONTROLLER_CONNECTION_LENGTH = 4 };

static bool _mPlayerHasLostControllerConnection[PLAYER_LOST_CONTROLLER_CONNECTION_LENGTH];
static bool _mHasSignedInAtSomePoint;
static bool _mHasLoadedEverything;

static void UpdateLostControllerConnectionStatus()
{
	/*
	if (OeRecordingTool_IsDisplayingSessionReadout() || Input_IsRecordingOrPlayingMasterRecording())
	{
		return;
	}

	if (!Service_PlatformShowsControllerDisconnectScreen())
	{
		return;
	}

#ifdef DEBUG_DEF_DISABLE_CONTROLLER_SAFETY_CHECKS
	return;
#endif

	int len = INPUT_MAXIMUM_PLAYER_COUNT;
	for (int i = 0; i < len; i++)
	{
		if (Input_GetPlayer(i)->MyControllerLostConnection())
		{
			_mPlayerHasLostControllerConnection[i] = true;
		}
	}
}
static void TrySignIn()
{
	if (Service_HasSignedIn())
	{
		return;
	}

	Service_SignIn(true, false);
	*/
}
static bool LoadEverythingHelper()
{
	return true;
	/*
	bool loadedSaves = false;
	bool loadedConfig = false;
	bool loadedBindings = false;

	if (GameSaveManager_HasInit())
	{
		if (!GameSaveManager_HasLoaded())
		{
			GameSaveManager_Load();
		}
		else
		{
			loadedSaves = true;
		}
	}

	if (!Service_PlatformUsesLocalStorageForSaveData()) //Cvars are loaded immediately if local storage
	{
		if (!OeCvars_HasLoadedSaveDataCvars())
		{
			Cvars_LoadSaveCvarsFromBlob();
		}
		else
		{
			loadedConfig = true;
		}
	}
	else
	{
		loadedConfig = true;
	}

	if (Input_HasInit())
	{
		if (!InputBindings_HaveAllPlayersLoadedBindings())
		{
			InputBindings_LoadAllPlayerBindings();
		}
		else
		{
			loadedBindings = true;
		}
	}

	if (loadedSaves && loadedConfig && loadedBindings)
	{
		return true;
	}
	else
	{
		return false;
	}
	*/
}
static void LoadEverything()
{
	/*
	if (!Service_HasSignedIn())
	{
		return;
	}

	_mHasSignedInAtSomePoint = true;
	if (!_mHasLoadedEverything)
	{
		_mHasLoadedEverything = LoadEverythingHelper();
	}
	*/
}

void ServiceHelper_Update(double delta)
{
	/*
	TrySignIn();

	LoadEverything();

	UpdateLostControllerConnectionStatus();

	Service_Update(delta);
	*/
}
bool ServiceHelper_HasPlayerHasLostControllerConnection()
{
	return false;
	/*
	int playerThatLostConnection = GetPlayerThatLostControllerConnection();
	if (playerThatLostConnection != -1)
	{
		return true;
	}
	else
	{
		return false;
	}
	*/
}
int ServiceHelper_GetPlayerThatLostControllerConnection()
{
	return -1;
	/*
	for (int i = 0; i < PLAYER_LOST_CONTROLLER_CONNECTION_LENGTH; i++)
	{
		if (_mPlayerHasLostControllerConnection[i])
		{
			return i;
		}
	}
	return -1;
	*/
}
void ServiceHelper_HandlePlayerLostControllerConnection()
{
	/*
	int playerThatLostConnection = GetPlayerThatLostControllerConnection();
	if (playerThatLostConnection == -1)
	{
		return;
	}

	int controllerTapped = OeControllerStates_GetControllerNumberIfAnyButtonTapped();
	if (controllerTapped != -1 || OeKeyboardState_IsAnyKeyTapped() || OeMouseState_IsAnyButtonTapped())
	{
		_mPlayerHasLostControllerConnection[playerThatLostConnection] = false;
	}
	*/
}
bool ServiceHelper_HasLoadedEverything()
{
	return true;
	//return _mHasLoadedEverything;
}
