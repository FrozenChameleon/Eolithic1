/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "ActionList.h"
#include "InputAction.h"

typedef struct ControllerState ControllerState;

typedef struct InputPlayer
{
	int _mPlayerNumber;
	int _mIsBlockedForPlayerSelect;
	int _mInputDeviceNumber;
	int _mCounterRumble;
	int _mRumblePriority;
	float _mRumbleLeftMotor;
	float _mRumbleRightMotor;
	InputAction _mActions[ACTION_LIST_LENGTH];
} InputPlayer;

typedef enum InputPlayerDevice
{
	INPUT_PLAYER_CONTROLLER_ONE_DEVICE_NUMBER = 0,
	INPUT_PLAYER_CONTROLLER_TWO_DEVICE_NUMBER = 1,
	INPUT_PLAYER_CONTROLLER_THREE_DEVICE_NUMBER = 2,
	INPUT_PLAYER_CONTROLLER_FOUR_DEVICE_NUMBER = 3,
	INPUT_PLAYER_KEYBOARD_DEVICE_NUMBER = 9
} InputPlayerDevice;

typedef enum InputPlayerBlockMenu
{
	INPUT_PLAYER_BLOCK_MENU_INPUT_OFF = 0,
	INPUT_PLAYER_BLOCK_MENU_INPUT_ALLOW_BACK = 1,
	INPUT_PLAYER_BLOCK_MENU_INPUT_ALL = 2
} InputPlayerBlockMenu;

void InputPlayer_SetVibration(float leftMotor, float rightMotor);
void InputPlayer_StopVibrating();
InputAction* InputPlayer_GetCurrentActions();
void InputPlayer_Init(InputPlayer* ip, int number);
void InputPlayer_SetInputDevice(InputPlayer* ip, int newDeviceNumber);
InputAction* InputPlayer_GetActionsForBindingsSync(InputPlayer* ip);
int32_t InputPlayer_GetActionsLength(InputPlayer* ip);
void InputPlayer_DetectInputDevice(InputPlayer* ip, bool isOnRelease);
int InputPlayer_GetDeviceNumber(InputPlayer* ip);
bool InputPlayer_IsInputDeviceSet(InputPlayer* ip);
void InputPlayer_RemoveInputDevice(InputPlayer* ip);
bool InputPlayer_IsUsingController(InputPlayer* ip);
bool InputPlayer_IsUsingKeyboard(InputPlayer* ip);
void InputPlayer_ClearInput(InputPlayer* ip);
bool InputPlayer_IsPlayerPressingAnything(InputPlayer* ip);
void InputPlayer_SetBlockMenuInput(InputPlayer* ip, int value);
void InputPlayer_Update(InputPlayer* ip);
InputAction* InputPlayer_GetAction(InputPlayer* ip, const char* name);
ControllerState* InputPlayer_GetController(InputPlayer* ip);
void InputPlayer_Vibrate(InputPlayer* ip, int priority, int frames, float leftMotor, float rightMotor);
bool InputPlayer_MyControllerLostConnection(InputPlayer* ip);
#if EDITOR
//void DebugSetDevice(int deviceNumber);
#endif