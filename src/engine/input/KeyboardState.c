/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "KeyboardState.h"

#include "KeyList.h"
#include "SDL3/SDL.h"
#include "../utils/Utils.h"
#include "../utils/Cvars.h"
#include "../service/Service.h"
#include "../core/Game.h"

static bool _mIsKeyMuted[KEYS_AMOUNT_OF_KEYS];
static int _mKeyTimeHeld[KEYS_AMOUNT_OF_KEYS];
static KeyboardData _mThisFrame;
static KeyboardData _mLastFrame;
static bool _mHasInit;

static SDL_Scancode GetScanCode(int key)
{
	//Mapped from FNA
	switch (key)
	{
	case KEYS_A:
		return SDL_SCANCODE_A;
	case KEYS_B:
		return SDL_SCANCODE_B;
	case KEYS_C:
		return SDL_SCANCODE_C;
	case KEYS_D:
		return SDL_SCANCODE_D;
	case KEYS_E:
		return SDL_SCANCODE_E;
	case KEYS_F:
		return SDL_SCANCODE_F;
	case KEYS_G:
		return SDL_SCANCODE_G;
	case KEYS_H:
		return SDL_SCANCODE_H;
	case KEYS_I:
		return SDL_SCANCODE_I;
	case KEYS_J:
		return SDL_SCANCODE_J;
	case KEYS_K:
		return SDL_SCANCODE_K;
	case KEYS_L:
		return SDL_SCANCODE_L;
	case KEYS_M:
		return SDL_SCANCODE_M;
	case KEYS_N:
		return SDL_SCANCODE_N;
	case KEYS_O:
		return SDL_SCANCODE_O;
	case KEYS_P:
		return SDL_SCANCODE_P;
	case KEYS_Q:
		return SDL_SCANCODE_Q;
	case KEYS_R:
		return SDL_SCANCODE_R;
	case KEYS_S:
		return SDL_SCANCODE_S;
	case KEYS_T:
		return SDL_SCANCODE_T;
	case KEYS_U:
		return SDL_SCANCODE_U;
	case KEYS_V:
		return SDL_SCANCODE_V;
	case KEYS_W:
		return SDL_SCANCODE_W;
	case KEYS_X:
		return SDL_SCANCODE_X;
	case KEYS_Y:
		return SDL_SCANCODE_Y;
	case KEYS_Z:
		return SDL_SCANCODE_Z;
	case KEYS_D0:
		return SDL_SCANCODE_0;
	case KEYS_D1:
		return SDL_SCANCODE_1;
	case KEYS_D2:
		return SDL_SCANCODE_2;
	case KEYS_D3:
		return SDL_SCANCODE_3;
	case KEYS_D4:
		return SDL_SCANCODE_4;
	case KEYS_D5:
		return SDL_SCANCODE_5;
	case KEYS_D6:
		return SDL_SCANCODE_6;
	case KEYS_D7:
		return SDL_SCANCODE_7;
	case KEYS_D8:
		return SDL_SCANCODE_8;
	case KEYS_D9:
		return SDL_SCANCODE_9;
	case KEYS_NumPad0:
		return SDL_SCANCODE_KP_0;
	case KEYS_NumPad1:
		return SDL_SCANCODE_KP_1;
	case KEYS_NumPad2:
		return SDL_SCANCODE_KP_2;
	case KEYS_NumPad3:
		return SDL_SCANCODE_KP_3;
	case KEYS_NumPad4:
		return SDL_SCANCODE_KP_4;
	case KEYS_NumPad5:
		return SDL_SCANCODE_KP_5;
	case KEYS_NumPad6:
		return SDL_SCANCODE_KP_6;
	case KEYS_NumPad7:
		return SDL_SCANCODE_KP_7;
	case KEYS_NumPad8:
		return SDL_SCANCODE_KP_8;
	case KEYS_NumPad9:
		return SDL_SCANCODE_KP_9;
	case KEYS_OemClear:
		return SDL_SCANCODE_KP_CLEAR;
	case KEYS_Decimal:
		return SDL_SCANCODE_KP_DECIMAL;
	case KEYS_Divide:
		return SDL_SCANCODE_KP_DIVIDE;
	case KEYS_Multiply:
		return SDL_SCANCODE_KP_MULTIPLY;
	case KEYS_Subtract:
		return SDL_SCANCODE_KP_MINUS;
	case KEYS_Add:
		return SDL_SCANCODE_KP_PLUS;
	case KEYS_F1:
		return SDL_SCANCODE_F1;
	case KEYS_F2:
		return SDL_SCANCODE_F2;
	case KEYS_F3:
		return SDL_SCANCODE_F3;
	case KEYS_F4:
		return SDL_SCANCODE_F4;
	case KEYS_F5:
		return SDL_SCANCODE_F5;
	case KEYS_F6:
		return SDL_SCANCODE_F6;
	case KEYS_F7:
		return SDL_SCANCODE_F7;
	case KEYS_F8:
		return SDL_SCANCODE_F8;
	case KEYS_F9:
		return SDL_SCANCODE_F9;
	case KEYS_F10:
		return SDL_SCANCODE_F10;
	case KEYS_F11:
		return SDL_SCANCODE_F11;
	case KEYS_F12:
		return SDL_SCANCODE_F12;
	case KEYS_F13:
		return SDL_SCANCODE_F13;
	case KEYS_F14:
		return SDL_SCANCODE_F14;
	case KEYS_F15:
		return SDL_SCANCODE_F15;
	case KEYS_F16:
		return SDL_SCANCODE_F16;
	case KEYS_F17:
		return SDL_SCANCODE_F17;
	case KEYS_F18:
		return SDL_SCANCODE_F18;
	case KEYS_F19:
		return SDL_SCANCODE_F19;
	case KEYS_F20:
		return SDL_SCANCODE_F20;
	case KEYS_F21:
		return SDL_SCANCODE_F21;
	case KEYS_F22:
		return SDL_SCANCODE_F22;
	case KEYS_F23:
		return SDL_SCANCODE_F23;
	case KEYS_F24:
		return SDL_SCANCODE_F24;
	case KEYS_Space:
		return SDL_SCANCODE_SPACE;
	case KEYS_Up:
		return SDL_SCANCODE_UP;
	case KEYS_Down:
		return SDL_SCANCODE_DOWN;
	case KEYS_Left:
		return SDL_SCANCODE_LEFT;
	case KEYS_Right:
		return SDL_SCANCODE_RIGHT;
	case KEYS_LeftAlt:
		return SDL_SCANCODE_LALT;
	case KEYS_RightAlt:
		return SDL_SCANCODE_RALT;
	case KEYS_LeftControl:
		return SDL_SCANCODE_LCTRL;
	case KEYS_RightControl:
		return SDL_SCANCODE_RCTRL;
	case KEYS_LeftWindows:
		return SDL_SCANCODE_LGUI;
	case KEYS_RightWindows:
		return SDL_SCANCODE_RGUI;
	case KEYS_LeftShift:
		return SDL_SCANCODE_LSHIFT;
	case KEYS_RightShift:
		return SDL_SCANCODE_RSHIFT;
	case KEYS_Apps:
		return SDL_SCANCODE_APPLICATION;
	case KEYS_OemQuestion:
		return SDL_SCANCODE_SLASH;
	case KEYS_OemPipe:
		return SDL_SCANCODE_BACKSLASH;
	case KEYS_OemOpenBrackets:
		return SDL_SCANCODE_LEFTBRACKET;
	case KEYS_OemCloseBrackets:
		return SDL_SCANCODE_RIGHTBRACKET;
	case KEYS_CapsLock:
		return SDL_SCANCODE_CAPSLOCK;
	case KEYS_OemComma:
		return SDL_SCANCODE_COMMA;
	case KEYS_Delete:
		return SDL_SCANCODE_DELETE;
	case KEYS_End:
		return SDL_SCANCODE_END;
	case KEYS_Back:
		return SDL_SCANCODE_BACKSPACE;
	case KEYS_Enter:
		return SDL_SCANCODE_RETURN;
	case KEYS_Escape:
		return SDL_SCANCODE_ESCAPE;
	case KEYS_Home:
		return SDL_SCANCODE_HOME;
	case KEYS_Insert:
		return SDL_SCANCODE_INSERT;
	case KEYS_OemMinus:
		return SDL_SCANCODE_MINUS;
	case KEYS_NumLock:
		return SDL_SCANCODE_NUMLOCKCLEAR;
	case KEYS_PageUp:
		return SDL_SCANCODE_PAGEUP;
	case KEYS_PageDown:
		return SDL_SCANCODE_PAGEDOWN;
	case KEYS_Pause:
		return SDL_SCANCODE_PAUSE;
	case KEYS_OemPeriod:
		return SDL_SCANCODE_PERIOD;
	case KEYS_OemPlus:
		return SDL_SCANCODE_EQUALS;
	case KEYS_PrintScreen:
		return SDL_SCANCODE_PRINTSCREEN;
	case KEYS_OemQuotes:
		return SDL_SCANCODE_APOSTROPHE;
	case KEYS_Scroll:
		return SDL_SCANCODE_SCROLLLOCK;
	case KEYS_OemSemicolon:
		return SDL_SCANCODE_SEMICOLON;
	case KEYS_Sleep:
		return SDL_SCANCODE_SLEEP;
	case KEYS_Tab:
		return SDL_SCANCODE_TAB;
	case KEYS_OemTilde:
		return SDL_SCANCODE_GRAVE;
	case KEYS_VolumeUp:
		return SDL_SCANCODE_VOLUMEUP;
	case KEYS_VolumeDown:
		return SDL_SCANCODE_VOLUMEDOWN;
	case KEYS_None:
		return SDL_SCANCODE_UNKNOWN;
	}

	return SDL_SCANCODE_UNKNOWN;
}

int32_t KeyboardData_GetLoc(int32_t key)
{
	const int* keyArray = KeyList_GetArray();
	int32_t keyArrayLength = KeyList_GetArrayLength();
	for (int i = 0; i < keyArrayLength; i += 1)
	{
		if (key == keyArray[i])
		{
			return i;
		}
	}
	return -1;
}
bool KeyboardData_IsKeyPressedAtLoc(const KeyboardData* kd, int32_t loc)
{
	return kd->_mIsKeyDown[loc];
}
bool KeyboardData_IsKeyPressed(const KeyboardData* kd, int32_t key)
{
	int32_t loc = KeyboardData_GetLoc(key);
	if (loc != -1)
	{
		return KeyboardData_IsKeyPressedAtLoc(kd, loc);
	}
	else
	{
		return false;
	}
}
int32_t KeyboardData_GetTimeHeld(int32_t key)
{
	int32_t loc = KeyboardData_GetLoc(key);
	if (loc != -1)
	{
		return _mKeyTimeHeld[loc];
	}
	else
	{
		return 0;
	}
}
void KeyboardData_Clear(KeyboardData* kd)
{
	Utils_ResetArrayAsBool(kd->_mIsKeyDown, KEYS_AMOUNT_OF_KEYS, false);
}
void KeyboardData_Poll(KeyboardData* kd)
{
	const int* keyArray = KeyList_GetArray();
	int32_t keyArrayLength = KeyList_GetArrayLength();

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < keyArrayLength; i += 1)
	{
		SDL_Scancode scanCode = GetScanCode(keyArray[i]);

		kd->_mIsKeyDown[i] = currentKeyStates[scanCode];

		if (_mIsKeyMuted[i])
		{
			if (kd->_mIsKeyDown[i])
			{
				kd->_mIsKeyDown[i] = false;
			}
			else
			{
				_mIsKeyMuted[i] = false;
			}
		}

		if (kd->_mIsKeyDown[i])
		{
			_mKeyTimeHeld[i] += 1;
		}
		else
		{
			_mKeyTimeHeld[i] = 0;
		}
	}
}
void KeyboardData_CopyFrom(KeyboardData* kd, const KeyboardData* otherData)
{
	for (int i = 0; i < KEYS_AMOUNT_OF_KEYS; i += 1)
	{
		kd->_mIsKeyDown[i] = otherData->_mIsKeyDown[i];
	}
}

void KeyboardState_Init()
{
	if (_mHasInit)
	{
		return;
	}

	KeyboardState_MuteInput();

	_mHasInit = true;
}
void KeyboardState_MuteInput()
{
	Utils_ResetArrayAsBool(_mIsKeyMuted, KEYS_AMOUNT_OF_KEYS, true);
}
void KeyboardState_ClearEverything()
{
	KeyboardData_Clear(&_mLastFrame);
	KeyboardData_Clear(&_mThisFrame);
}
void KeyboardState_Poll()
{
	KeyboardData_CopyFrom(&_mLastFrame, &_mThisFrame);

	KeyboardData_Clear(&_mThisFrame);

	if (Cvars_GetAsBool(CVARS_ENGINE_DISABLE_KEYBOARD) || Service_PlatformDisablesKeyboardUse() ||
		(!Game_IsActive() && Service_PlatformStopsPollingInputWhenGameIsNotActive()))
	{
		return;
	}

	KeyboardData_Poll(&_mThisFrame);
}
int32_t KeyboardState_GetTimeHeld(int32_t key)
{
	return KeyboardData_GetTimeHeld(key);
}
bool KeyboardState_IsKeyPressed(int32_t key)
{
	return KeyboardData_IsKeyPressed(&_mThisFrame, key);
}
bool KeyboardState_IsKeyTapped(int32_t key)
{
	return !KeyboardData_IsKeyPressed(&_mLastFrame, key) && KeyboardData_IsKeyPressed(&_mThisFrame, key);
}
bool KeyboardState_IsKeyReleased(int32_t key)
{
	return KeyboardData_IsKeyPressed(&_mLastFrame, key) && !KeyboardData_IsKeyPressed(&_mThisFrame, key);
}
bool KeyboardState_IsAnyKeyReleased()
{
	int len = KEYS_AMOUNT_OF_KEYS;
	for (int i = 0; i < len; i += 1)
	{
		if (KeyboardData_IsKeyPressedAtLoc(&_mLastFrame, i) && !KeyboardData_IsKeyPressedAtLoc(&_mThisFrame, i))
		{
			return true;
		}
	}
	return false;
}
bool KeyboardState_IsAnyKeyTapped()
{
	int len = KEYS_AMOUNT_OF_KEYS;
	for (int i = 0; i < len; i += 1)
	{
		if (!KeyboardData_IsKeyPressedAtLoc(&_mLastFrame, i) && KeyboardData_IsKeyPressedAtLoc(&_mThisFrame, i))
		{
			return true;
		}
	}
	return false;
}
bool KeyboardState_IsAnyKeyPressed()
{
	int len = KEYS_AMOUNT_OF_KEYS;
	for (int i = 0; i < len; i += 1)
	{
		if (KeyboardData_IsKeyPressedAtLoc(&_mThisFrame, i))
		{
			return true;
		}
	}
	return false;
}