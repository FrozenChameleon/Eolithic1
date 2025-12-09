/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

 /* Derived from code by Ethan Lee (Copyright 2009-2024).
  * Released under the Microsoft Public License.
  * See fna.LICENSE for details.

  * Derived from code by the Mono.Xna Team (Copyright 2006).
  * Released under the MIT License.
  * See monoxna.LICENSE for details.
  */

#include "ControllerState.h"

#include "../../third_party/stb_ds.h"
#include "SDL3/SDL.h"
#include "Buttons.h"
#include "PlayerIndex.h"
#include "Axes.h"
#include "ButtonList.h"
#include "../math/Math.h"
#include "../math/MathHelper.h"
#include "../utils/Logger.h"
#include "../utils/Utils.h"
#include "../utils/Macros.h"

#define DEVICES_ARRAY_LENGTH 4

//static std::vector<OeInputAction> _mDummyAction;
static const char* _mGlyphDummy = EE_STR_EMPTY;
static SDL_Gamepad* INTERNAL_devices[DEVICES_ARRAY_LENGTH];
static struct { int32_t key; int32_t value; } *hm_INTERNAL_instanceList = NULL; //Map of SDL device # to internal devices array index ^

static SDL_Gamepad* GetDevice(PlayerIndex index)
{
	int indexToUse = index;
	return INTERNAL_devices[indexToUse];
}
static SDL_GamepadButton ButtonToSDL(int button)
{
	switch (button)
	{
	case BUTTONS_DPadUp:
		return SDL_GAMEPAD_BUTTON_DPAD_UP;
	case BUTTONS_DPadDown:
		return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
	case BUTTONS_DPadLeft:
		return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
	case BUTTONS_DPadRight:
		return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
	case BUTTONS_Start:
		return SDL_GAMEPAD_BUTTON_START;
	case BUTTONS_Back:
		return SDL_GAMEPAD_BUTTON_BACK;
	case BUTTONS_LeftStick:
		return SDL_GAMEPAD_BUTTON_LEFT_STICK;
	case BUTTONS_RightStick:
		return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
	case BUTTONS_LeftShoulder:
		return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
	case BUTTONS_RightShoulder:
		return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
	case BUTTONS_A:
		return SDL_GAMEPAD_BUTTON_SOUTH;
	case BUTTONS_B:
		return SDL_GAMEPAD_BUTTON_EAST;
	case BUTTONS_X:
		return SDL_GAMEPAD_BUTTON_WEST;
	case BUTTONS_Y:
		return SDL_GAMEPAD_BUTTON_NORTH;
	}
	return SDL_GAMEPAD_BUTTON_INVALID;
}

void ControllerData_PollControllerStatus(ControllerData* cd, PlayerIndex index)
{
	cd->_mIndex = index;

	SDL_Gamepad* device = GetDevice(index);
	if (device == NULL)
	{
		cd->_mIsConnected = false;
	}
	else
	{
		cd->_mIsConnected = true;
	}
}
void ControllerData_PollInput(ControllerData* cd, bool* isButtonMutedArray, bool* isAnalogMutedArray)
{
	if (!cd->_mIsConnected)
	{
		return;
	}

	SDL_Gamepad* device = GetDevice(cd->_mIndex);

	for (int i = 0; i < BUTTONS_AMOUNT_OF_BUTTONS; i++)
	{
		cd->_mIsButtonPressed[i] = SDL_GetGamepadButton(device, ButtonToSDL(ButtonList_GetButton(i)));

		if (isButtonMutedArray[i])
		{
			if (cd->_mIsButtonPressed[i])
			{
				cd->_mIsButtonPressed[i] = false;
			}
			else
			{
				isButtonMutedArray[i] = false;
			}
		}
	}

	cd->_mAnalogData[AXES_ANALOG_LEFT_STICK_X] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_LEFTX)) / 32767.0f;
	cd->_mAnalogData[AXES_ANALOG_LEFT_STICK_Y] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_LEFTY)) / -32767.0f;
	cd->_mAnalogData[AXES_ANALOG_RIGHT_STICK_X] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_RIGHTX)) / 32767.0f;
	cd->_mAnalogData[AXES_ANALOG_RIGHT_STICK_Y] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_RIGHTY)) / -32767.0f;
	cd->_mAnalogData[AXES_ANALOG_LEFT_TRIGGER] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_LEFT_TRIGGER)) / 32767.0f;
	cd->_mAnalogData[AXES_ANALOG_RIGHT_TRIGGER] = (float)(SDL_GetGamepadAxis(device, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER)) / 32767.0f;

	for (int i = 0; i < AXES_AMOUNT_OF_AXIS; i += 1)
	{
		if (isAnalogMutedArray[i])
		{
			float val = Math_fabsf(cd->_mAnalogData[i]);
			if (val > AXES_ANALOG_MUTE_DEADZONE)
			{
				cd->_mAnalogData[i] = 0;
			}
			else
			{
				isAnalogMutedArray[i] = false;
			}
		}
	}
}

void ControllerState_SetVibration(ControllerState* cs, float leftMotor, float rightMotor)
{
	if (!ControllerData_IsConnected(&cs->_mThisFrame))
	{
		return;
	}

	Uint16 left = (Uint16)(MathHelper_Clamp(leftMotor, 0.0f, 1.0f) * 0xFFFF);
	Uint16 right = (Uint16)(MathHelper_Clamp(rightMotor, 0.0f, 1.0f) * 0xFFFF);

#ifdef GLOBAL_DEF_RUMBLE_MUL
	left = (Uint16)(left * GLOBAL_DEF_RUMBLE_MUL);
	right = (Uint16)(right * GLOBAL_DEF_RUMBLE_MUL);
#endif

	SDL_RumbleGamepad(GetDevice(cs->_mIndex), left, right, 0);
}

int32_t ControllerState_AddControllerInstance(ControllerState* cs, int32_t dev)
{
	//Adapted from FNA/src/FNAPlatform/SDL2_FNAPlatform.cs

	int which = -1;
	for (int i = 0; i < DEVICES_ARRAY_LENGTH; i++)
	{
		if (INTERNAL_devices[i] == NULL)
		{
			which = i;
			break;
		}
	}

	if (which == -1)
	{
		Logger_LogInformation("Unable to find index to add controller instance!");
		return -1; // Ignoring more than 4 controllers.
	}

	// Clear the error buffer. We're about to do a LOT of dangerous stuff.
	SDL_ClearError();

	// Open the device!
	INTERNAL_devices[which] = SDL_OpenGamepad(dev);

	// We use this when dealing with GUID initialization.
	SDL_Joystick* thisJoystick = SDL_GetGamepadJoystick(INTERNAL_devices[which]);

	// Pair up the instance ID to the player index.
	// FIXME: Remove check after 2.0.4? -flibit
	SDL_JoystickID thisInstance = SDL_GetJoystickID(thisJoystick);
	int64_t thisInstanceIndex = hmgeti(hm_INTERNAL_instanceList, thisInstance);
	if (thisInstanceIndex != -1)
	{
		// Duplicate? Usually this is OSX being dumb, but...?
		Logger_LogInformation("Duplicate controller instance!");
		INTERNAL_devices[which] = NULL;
		return -1;
	}

	hmput(hm_INTERNAL_instanceList, thisInstance, which);

	Logger_printf("Added device #%d, %s", which, SDL_GetGamepadName(INTERNAL_devices[which]));

	return which;
}
int32_t ControllerState_RemoveControllerInstance(ControllerState* cs, int32_t dev)
{
	//Adapted from FNA/src/FNAPlatform/SDL2_FNAPlatform.cs

	int output = -1;

	int64_t instanceListLen = hmlen(hm_INTERNAL_instanceList);
	for (int i = 0; i < instanceListLen; i += 1)
	{
		if (hm_INTERNAL_instanceList->key == dev)
		{
			output = hm_INTERNAL_instanceList->value;
			break;
		}
	}

	if (output == -1)
	{
		Logger_LogInformation("Unable to remove controller instance!");
		// Odds are, this is controller 5+ getting removed.
		return -1;
	}

	Logger_printf("Removed Device #%d, %s", output, SDL_GetGamepadName(INTERNAL_devices[output]));

	hmdel(hm_INTERNAL_instanceList, dev);
	SDL_CloseGamepad(INTERNAL_devices[output]);
	INTERNAL_devices[output] = NULL;

	// A lot of errors can happen here, but honestly, they can be ignored...
	SDL_ClearError();

	return output;
}
void ControllerState_BeforePollingUpdate()
{

}
bool ControllerState_PlatformUsesControllerPrompt()
{
	return false;
}
bool ControllerState_GetControllerPrompt(int32_t minPlayer, int32_t maxPlayer, bool retainConnection, bool singlePlayer, bool spinlockUntilSuccess)
{
	return false;
}
bool ControllerState_PlatformIsForcingCustomInputActions(int32_t player)
{
	return false;
}
//std::vector<OeInputAction>& OeControllerState_GetForcedCustomInputActions(int player)
//{
//	return _mDummyAction;
//}
bool ControllerState_IsUsingControllerForbiddenToFullRebinding()
{
	return false;
}
bool ControllerState_IsUsingControllerPrompt()
{
	return false;
}
const char* ControllerState_PlatformGetForcedSpecificGlyphAsString()
{
	return _mGlyphDummy;
}