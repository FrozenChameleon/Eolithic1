/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "InputPlayer.h"

#include "../utils/Logger.h"

void InputPlayer_SetVibration(float leftMotor, float rightMotor)
{

}
void InputPlayer_StopVibrating()
{

}
InputAction* InputPlayer_GetCurrentActions()
{

}
void InputPlayer_Init(InputPlayer* ip, int number)
{

}
void InputPlayer_SetInputDevice(InputPlayer* ip, int newDeviceNumber)
{
	if (newDeviceNumber == ip->_mInputDeviceNumber)
	{
		return;
	}

	if ((ip->_mInputDeviceNumber == INPUT_PLAYER_CONTROLLER_ONE_DEVICE_NUMBER) || (ip->_mInputDeviceNumber == INPUT_PLAYER_CONTROLLER_TWO_DEVICE_NUMBER)
		|| (ip->_mInputDeviceNumber == INPUT_PLAYER_CONTROLLER_THREE_DEVICE_NUMBER) || (ip->_mInputDeviceNumber == INPUT_PLAYER_CONTROLLER_FOUR_DEVICE_NUMBER))
	{
		InputPlayer_StopVibrating();
	}

	if (ip->_mInputDeviceNumber == -1)
	{
		Logger_printf("Input device set for Player #%d, Device #%d", (ip->_mPlayerNumber + 1), newDeviceNumber);
	}

	ip->_mInputDeviceNumber = newDeviceNumber;
}
InputAction* InputPlayer_GetActionsForBindingsSync(InputPlayer* ip)
{

}
int32_t InputPlayer_GetActionsLength(InputPlayer* ip)
{
	return ACTION_LIST_LENGTH;
}
void InputPlayer_DetectInputDevice(InputPlayer* ip, bool isOnRelease)
{

}
int InputPlayer_GetDeviceNumber(InputPlayer* ip)
{

}
bool InputPlayer_IsInputDeviceSet(InputPlayer* ip)
{

}
void InputPlayer_RemoveInputDevice(InputPlayer* ip)
{

}
bool InputPlayer_IsUsingController(InputPlayer* ip)
{

}
bool InputPlayer_IsUsingKeyboard(InputPlayer* ip)
{

}
void InputPlayer_ClearInput(InputPlayer* ip)
{

}
bool InputPlayer_IsPlayerPressingAnything(InputPlayer* ip)
{

}
void InputPlayer_SetBlockMenuInput(InputPlayer* ip, int value)
{

}
void InputPlayer_Update(InputPlayer* ip)
{

}
InputAction* InputPlayer_GetAction(InputPlayer* ip, const char* name)
{

}
ControllerState* InputPlayer_GetController(InputPlayer* ip)
{

}
void InputPlayer_Vibrate(InputPlayer* ip, int priority, int frames, float leftMotor, float rightMotor)
{

}
bool InputPlayer_MyControllerLostConnection(InputPlayer* ip)
{

}
#if EDITOR
//void DebugSetDevice(int deviceNumber);
#endif