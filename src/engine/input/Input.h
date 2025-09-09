/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdbool.h"
#include "stdint.h"
#include "../math/Vector2.h"
#include "../math/Rectangle.h"
#include "../math/Point.h"

typedef struct InputPlayer InputPlayer;
typedef struct ControllerState ControllerState;
typedef struct InputAction InputAction;

enum MasterRecordingState
{
	INPUT_MASTER_RECORDING_STATE_OFF = 0,
	INPUT_MASTER_RECORDING_STATE_RECORDING = 1,
	INPUT_MASTER_RECORDING_STATE_PLAYBACK = 2
};

enum ControllerGlyph
{
	INPUT_CONTROLLER_GLYPH_X = 0,
	INPUT_CONTROLLER_GLYPH_P4 = 1,
	INPUT_CONTROLLER_GLYPH_P5 = 2,
	INPUT_CONTROLLER_GLYPH_N = 3
};

enum PlayerNumbers
{
	INPUT_PLAYER_1 = 0,
	INPUT_PLAYER_2 = 1,
	INPUT_PLAYER_3 = 2,
	INPUT_PLAYER_4 = 3
};

enum
{
	INPUT_MAXIMUM_PLAYER_COUNT = 4
};

extern bool INPUT_FLAG_IS_ON_MENU;
extern bool INPUT_FLAG_IS_ON_MULTIPLAYER_SETUP_MENU;
extern bool INPUT_FLAG_IS_PLAYING_MASTER_RECORDING_FAST;

void Input_Init();
bool Input_HasInit();

void Input_MuteAllInput();
bool Input_IsAnythingPressedByAnyPlayer();
bool Input_IsPressedByAnyPlayer(const char* action);
bool Input_IsReleasedByAnyPlayer(const char* action);
bool Input_IsTappedByAnyPlayer(const char* action);
int32_t Input_GetLongestTimeHeldByAnyPlayer(const char* action);
int32_t Input_GetAmountOfActivePlayers();
void Input_Update(bool doNotUpdateMasterRecording);
bool Input_IsAnyPlayerUsingThisDeviceNumber(int32_t deviceNumber);
bool Input_IsSimultaneousInputForKeyboard();
bool Input_IsSimultaneousInputForController();
bool Input_IsSinglePlayerInputMode();
bool Input_IsMultiplayerInputMode();
void Input_BlockMKBInputForFrames(int32_t frames);
InputPlayer* Input_GetPlayerOne();
InputPlayer* Input_GetPlayer(int32_t i);
ControllerState* Input_GetController(int32_t number);
InputAction* Input_GetPlayerOneAction(const char* name);
InputAction* Input_GetPlayerAction(int32_t playerNumber, const char* name);
//Vector2 GetCameraAdjustedMouse(const Camera* camera);
bool Input_JustScrolledUp();
bool Input_JustScrolledDown();
int32_t Input_GetDifferenceMouseX();
int32_t Input_GetDifferenceMouseY();
int32_t Input_GetMouseX();
int32_t Input_GetMouseY();
Point Input_GetMouse();
Vector2 Input_GetScaledMouseForRetroScreen();
float Input_GetScaledMouseForRetroScreenX();
float Input_GetScaledMouseForRetroScreenY();
//Vector2 GetCameraAdjustedMouseForRetroScreen(const Camera* camera);
//float GetCameraAdjustedMouseForRetroScreenX(const Camera* camera);
//float GetCameraAdjustedMouseForRetroScreenY(const Camera* camera);
bool Input_MouseHasChangedPosition();
bool Input_IsLeftMousePressed();
bool Input_IsLeftMouseTapped();
bool Input_IsLeftMouseReleased();
bool Input_IsLeftMouseDoubleClicked();
bool Input_IsRightMousePressed();
bool Input_IsRightMouseTapped();
bool Input_IsRightMouseReleased();
bool Input_IsMiddleMousePressed();
bool Input_IsMiddleMouseTapped();
bool Input_IsMiddleMouseReleased();
bool Input_IsCtrlPressed();
bool Input_IsTabPressed();
bool Input_IsShiftPressed();
bool Input_IsShiftTapped();
bool Input_IsAltPressed();
bool Input_IsDeletePressed();
bool Input_IsDeleteTapped();
bool Input_IsDeleteReleased();
bool Input_IsTildePressed();
bool Input_IsTildeReleased();
bool Input_IsEscapePressed();
bool Input_IsEscapeTapped();
bool Input_IsEnterTapped();
bool Input_IsModifierPressed();
void Input_StopAllRumble();
Vector2 Input_ProcessStickDeadzones(Vector2 stick, float radialDeadzone, float axialDeadzone, float outerDeadzone);
void Input_OverrideDeadzones(int32_t radial, int32_t outer, int32_t axial);
int32_t Input_GetRadialDeadzone();
int32_t Input_GetOuterDeadzone();
int32_t Input_GetAxialDeadzone();
float Input_GetRadialDeadzoneAsFloat();
float Input_GetOuterDeadzoneAsFloat();
float Input_GetAxialDeadzoneAsFloat();
float Input_GetAnalogToPressThresholdForSticks();
float Input_GetAnalogToPressThresholdForTriggers();
bool Input_IsRecordingMasterRecording();
bool Input_IsPlayingMasterRecording();
bool Input_IsRecordingOrPlayingMasterRecording();
void Input_SetMasterRecordingState(int32_t state);
#if EDITOR || CHEATS
bool Input_IsKeyTapped(int32_t key);
bool Input_IsKeyReleased(int32_t key);
bool Input_IsKeyPressed(int32_t key);
int32_t Input_GetKeyTimeHeld(int32_t key);
#endif