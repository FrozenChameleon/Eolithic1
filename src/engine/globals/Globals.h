/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Vector2.h"
#include "../math/Random32.h"

enum RecordingVersion
{
	GLOBALS_RECORDING_VERSION_0_ORIGINAL = 0,
	GLOBALS_RECORDING_VERSION_1_SUCCESS_NUMBER_FIX = 1,
	GLOBALS_RECORDING_VERSION_2_CS_THING_ID_FIX = 2
};

enum { GLOBALS_DEFAULT_DEBUG_GAME_LOGIC_SPEED = 100 };

extern Vector2 GLOBALS_DEBUG_QUICK_PLAYER_POSITION;
extern int32_t GLOBALS_DEBUG_SHOW_INFO;
extern int32_t GLOBALS_DEBUG_GAME_LOGIC_SPEED;
extern bool GLOBALS_DEBUG_SHOW_INGAME_COLLISION;
extern bool GLOBALS_DEBUG_DISABLE_HUD;
extern bool GLOBALS_DEBUG_IS_GOD_MODE;
extern bool GLOBALS_DEBUG_IS_PAUSED;
extern bool GLOBALS_DEBUG_EDITOR_JUST_RELOADED_GRAPHICS;
extern bool GLOBALS_DEBUG_JUST_LOADED_MAP_NOTIFY_EDITOR;
extern bool GLOBALS_DEBUG_IS_EDITOR_MODE;
extern bool GLOBALS_DEBUG_IS_META_MAP_EDIT_TILE_MODE_AT_MAP_LOAD;
extern bool GLOBALS_DEBUG_ENGINE_FORCE_LOAD_DATS;

bool Globals_DebugIsRenderDisabled();
void Globals_DebugSetRenderDisabled(bool value);
bool Globals_IsAutoMode();
bool Globals_IsAutoModeFixed();
void Globals_TurnOnAutoMode(bool isFixed);
Random32* Globals_GetSharedRandom();
bool Globals_IsAudioDisabledPermanently();
void Globals_DisableAudioPermanently();
void Globals_DisableAudioPermanentlyBecauseOfNoAudioHardware();
void Globals_SetDebugFileMode(bool value);
bool Globals_IsDebugFileMode();
void Globals_SetAsExceptionUnsafe();
bool Globals_IsExceptionUnsafe();
void Globals_SetAsNeedToTestFrameRate();
bool Globals_NeedToTestFrameRate();
void Globals_SetAsGameLoaded();
bool Globals_IsGameLoaded();
void Globals_DisableSavingUserData();
bool Globals_IsSavingUserDataDisabled();
void Globals_DisableAchievements();
bool Globals_AreAchievementsDisabled();
void Globals_DisableLoadingUserData();
bool Globals_IsLoadingUserDataDisabled();
void Globals_DisableLeaderboards();
bool Globals_AreLeaderboardDisabled();
double Globals_GetDebugGameSpeedAsMul();
bool Globals_IsDebugGameSpeedSet();
void Globals_DisableSavingAndLoadingAndAchievementsAndLeaderboards();
int32_t Globals_GetNewestRecordingVersion();
int32_t Globals_GetCurrentRecordingVersion();
int64_t Globals_GetTime();
uint32_t Globals_GetTimeForRandomSeed();
void Globals_ToggleGodMode();