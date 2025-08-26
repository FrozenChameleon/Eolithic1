/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Globals.h"

#include "../utils/Logger.h"
#include "../service/Service.h"
#include "../utils/Utils.h"
#include "../input/Input.h"
#include "../input/ControllerStates.h"
#include "time.h"

static bool _mIsAutoMode;
static bool _mIsAutoModeFixed;
static Random32 _mSharedRandom;
static bool _mIsAudioDisabled;
static bool _mIsLoadingUserDataDisabled;
static bool _mAreAchievementsDisabled;
static bool _mIsSavingUserDataDisabled;
static bool _mIsGameLoaded;
static bool _mNeedToTestFrameRate;
static bool _mIsExceptionUnsafe;
static bool _mDebugFileModeWasSet;
static bool _mIsDebugFileMode;
static bool _mIsRenderDisabled;

Vector2 GLOBALS_DEBUG_QUICK_PLAYER_POSITION;
int32_t GLOBALS_DEBUG_SHOW_INFO;
int32_t GLOBALS_DEBUG_GAME_LOGIC_SPEED = GLOBALS_DEFAULT_DEBUG_GAME_LOGIC_SPEED;
bool GLOBALS_DEBUG_SHOW_INGAME_COLLISION;
bool GLOBALS_DEBUG_DISABLE_HUD;
bool GLOBALS_DEBUG_IS_GOD_MODE;
bool GLOBALS_DEBUG_IS_PAUSED;
bool GLOBALS_DEBUG_EDITOR_JUST_RELOADED_GRAPHICS;
bool GLOBALS_DEBUG_JUST_LOADED_MAP_NOTIFY_EDITOR;
bool GLOBALS_DEBUG_IS_EDITOR_MODE;
bool GLOBALS_DEBUG_IS_META_MAP_EDIT_TILE_MODE_AT_MAP_LOAD;
bool GLOBALS_DEBUG_ENGINE_FORCE_LOAD_DATS;

bool Globals_DebugIsRenderDisabled()
{
	return _mIsRenderDisabled;
}
void Globals_DebugSetRenderDisabled(bool value)
{
	_mIsRenderDisabled = value;
}
bool Globals_IsAutoMode()
{
	return _mIsAutoMode;
}
bool Globals_IsAutoModeFixed()
{
	return _mIsAutoModeFixed;
}
void Globals_TurnOnAutoMode(bool isFixed)
{
	Globals_DisableSavingAndLoadingAndAchievementsAndLeaderboards();
	_mIsAutoMode = true;
	_mIsAutoModeFixed = isFixed;
}
Random32* Globals_GetSharedRandom()
{
	return &_mSharedRandom;
}
bool Globals_IsAudioDisabledPermanently()
{
	return _mIsAudioDisabled;
}
void Globals_DisableAudioPermanently()
{
	if (_mIsAudioDisabled)
	{
		return;
	}

	Logger_LogError("Disabling all audio");
	_mIsAudioDisabled = true;
}
void Globals_DisableAudioPermanentlyBecauseOfNoAudioHardware()
{
	if (_mIsAudioDisabled)
	{
		return;
	}

	Logger_LogError("No audio hardware, disabling all audio");
	_mIsAudioDisabled = true;
}
void Globals_SetDebugFileMode(bool value)
{
	if (_mDebugFileModeWasSet)
	{
		return;
	}

	_mDebugFileModeWasSet = true;
	_mIsDebugFileMode = value;
}
bool Globals_IsDebugFileMode()
{
	return _mIsDebugFileMode;
}
void Globals_SetAsExceptionUnsafe()
{
	_mIsExceptionUnsafe = true;
}
bool Globals_IsExceptionUnsafe()
{
	return _mIsExceptionUnsafe;
}
void Globals_SetAsNeedToTestFrameRate()
{
	_mNeedToTestFrameRate = true;
}
bool Globals_NeedToTestFrameRate()
{
	return _mNeedToTestFrameRate;
}
void Globals_SetAsGameLoaded()
{
	_mIsGameLoaded = true;
}
bool Globals_IsGameLoaded()
{
	return _mIsGameLoaded;
}
void Globals_DisableSavingUserData()
{
#ifdef DEBUG_DEF_DISABLE_RECORDING_SAFETY_SAVING
	return;
#endif

	_mIsSavingUserDataDisabled = true;
}
bool Globals_IsSavingUserDataDisabled()
{
	return _mIsSavingUserDataDisabled;
}
void Globals_DisableAchievements()
{
#ifdef DEBUG_DEF_DISABLE_RECORDING_SAFETY_ACHIEVEMENTS
	return;
#endif

	_mAreAchievementsDisabled = true;
}
bool Globals_AreAchievementsDisabled()
{
	return _mAreAchievementsDisabled;
}
void Globals_DisableLoadingUserData()
{
#ifdef DEBUG_DEF_DISABLE_RECORDING_SAFETY_LOADING
	return;
#endif

	_mIsLoadingUserDataDisabled = true;
}
bool Globals_IsLoadingUserDataDisabled()
{
	return _mIsLoadingUserDataDisabled;
}
void Globals_DisableLeaderboards()
{
#ifdef DEBUG_DEF_DISABLE_RECORDING_SAFETY_LEADERBOARDS
	return;
#endif

	Service_DisableLeaderboards();
}
bool Globals_AreLeaderboardDisabled()
{
	return Service_AreLeaderboardDisabled();
}
double Globals_GetDebugGameSpeedAsMul()
{
	return (double)GLOBALS_DEBUG_GAME_LOGIC_SPEED / GLOBALS_DEFAULT_DEBUG_GAME_LOGIC_SPEED;
}
bool Globals_IsDebugGameSpeedSet()
{
	if (GLOBALS_DEBUG_GAME_LOGIC_SPEED == GLOBALS_DEFAULT_DEBUG_GAME_LOGIC_SPEED)
	{
		return false;
	}
	if (GLOBALS_DEBUG_GAME_LOGIC_SPEED <= 0)
	{
		return false;
	}
	return true;
}
void Globals_DisableSavingAndLoadingAndAchievementsAndLeaderboards()
{
	Globals_DisableSavingUserData();
	Globals_DisableLoadingUserData();
	Globals_DisableAchievements();
	Globals_DisableLeaderboards();
}
int32_t Globals_GetNewestRecordingVersion()
{
	return GLOBALS_RECORDING_VERSION_2_CS_THING_ID_FIX;
}
int32_t Globals_GetCurrentRecordingVersion()
{
	return Globals_GetNewestRecordingVersion();

	//TODO C99
	//if (Input_IsPlayingMasterRecording())
	//{
	//	return ControllerStates_GetCurrentMasterRecordingVersion();
	//}
	//else if (OeRecordingTool::IsReading())
	//{
	//	return OeRecordingTool::GetCurrentRecordingVersion();
	//}
	//else
	//{
	//	return GetNewestRecordingVersion();
	//}
}
int64_t Globals_GetTime()
{
	time_t currentTime;
	currentTime = time(NULL);
	return (int64_t)currentTime;
}
uint32_t Globals_GetTimeForRandomSeed()
{
	int64_t source = Globals_GetTime();
	uint64_t dest;
	Utils_memcpy(&dest, &source, sizeof(uint64_t));
	uint32_t returnValue = (uint32_t)dest;
	return returnValue;
}
void Globals_ToggleGodMode()
{
	GLOBALS_DEBUG_IS_GOD_MODE = !GLOBALS_DEBUG_IS_GOD_MODE;
	if (GLOBALS_DEBUG_IS_GOD_MODE)
	{
		Logger_LogInformation("God Mode: ON");
	}
	else
	{
		Logger_LogInformation("God Mode: OFF");
	}
}