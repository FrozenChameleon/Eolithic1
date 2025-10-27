/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "InputCheck.h"

#include "MouseState.h"
#include "ControllerStates.h"
#include "KeyboardState.h"
#include "InputPlayer.h"
#include "../math/Math.h"
#include "Input.h"
#include "Axes.h"
#include "../utils/Logger.h"

float InputCheck_CorrectAnalogForDirection(int direction, float value)
{
	int32_t sig = Math_SignumSingle(value);
	if (((direction == -1) && (sig == 1)) || ((direction == 1) && (sig == -1)))
	{
		return 0;
	}
	else
	{
		return value;
	}
}
bool InputCheck_CheckTypeAxis(InputCheck* data)
{
	bool isTriggers = InputCheck_IsAxisTriggers(data);

	float threshold;
	if (isTriggers)
	{
		threshold = Input_GetAnalogToPressThresholdForTriggers();
	}
	else
	{
		threshold = Input_GetAnalogToPressThresholdForSticks();
	}

	if (threshold == 0)
	{
		Logger_LogWarning("No threshold set for stick/trigger");
		threshold = 50;
	}

	if (data->mAnalogValue >= threshold)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool InputCheck_IsAxisTriggers(InputCheck* data)
{
	return (data->mAxis == INPUTCHECK_AXIS_LEFT_TRIGGER) || (data->mAxis == INPUTCHECK_AXIS_RIGHT_TRIGGER);
}
bool InputCheck_CheckTypeButton(InputPlayer* playerInput, InputCheck* data)
{
	if (Input_IsSimultaneousInputForController())
	{
		return ControllerStates_IsButtonPressedOnAnyController(data->mButton);
	}

	if (!InputPlayer_IsUsingController(&playerInput))
	{
		return false;
	}
	if (ControllerState_IsButtonPressed(InputPlayer_GetController(&playerInput), data->mButton))
	{
		return true;
	}

	return false;
}
bool InputCheck_CheckTypeMouseButton(InputPlayer* playerInput, InputCheck* data)
{
	if (Input_IsRecordingOrPlayingMasterRecording())
	{
		return false;
	}

	if (Input_IsSimultaneousInputForKeyboard())
	{
		return MouseState_IsButtonPressed(data->mMouseButton);
	}

	if (playerInput != NULL)
	{
		if (!InputPlayer_IsUsingKeyboard(&playerInput))
		{
			return false;
		}
	}

	bool valid = false;
	if (MouseState_IsButtonPressed(data->mMouseButton))
	{
		valid = true;
	}

	if (valid)
	{
		return true;
	}

	return false;
}
bool InputCheck_CheckTypeKey(InputPlayer* playerInput, InputCheck* data)
{
	if (Input_IsRecordingOrPlayingMasterRecording())
	{
		return false;
	}

	if (Input_IsSimultaneousInputForKeyboard())
	{
		return KeyboardState_IsKeyPressed(data->mKey);
	}

	if (playerInput != NULL)
	{
		if (!InputPlayer_IsUsingKeyboard(&playerInput))
		{
			return false;
		}
	}

	if (KeyboardState_IsKeyPressed(data->mKey))
	{
		return true;
	}

	return false;
}
const char* InputCheck_GetNameTypeAxis(InputCheck* data)
{
	switch (data->mAxis)
	{
	case INPUTCHECK_AXIS_LEFT_STICK_X:
		if (data->mAxisDirection >= 0)
		{
			return "LS_RIGHT";
		}
		else
		{
			return "LS_LEFT";
		}
	case INPUTCHECK_AXIS_LEFT_STICK_Y:
		if (data->mAxisDirection >= 0)
		{
			return "LS_UP";
		}
		else
		{
			return "LS_DOWN";
		}
	case INPUTCHECK_AXIS_RIGHT_STICK_X:
		if (data->mAxisDirection >= 0)
		{
			return "RS_RIGHT";
		}
		else
		{
			return "RS_LEFT";
		}
	case INPUTCHECK_AXIS_RIGHT_STICK_Y:
		if (data->mAxisDirection >= 0)
		{
			return "RS_UP";
		}
		else
		{
			return "RS_DOWN";
		}
	case INPUTCHECK_AXIS_LEFT_TRIGGER:
		return "LT";
	case INPUTCHECK_AXIS_RIGHT_TRIGGER:
		return "RT";
	}
	return "";
}
const char* InputCheck_GetNameTypeButton(InputCheck* data)
{
	switch (data->mButton)
	{
	case BUTTONS_A:
		return "A";
	case BUTTONS_B:
		return "B";
	case BUTTONS_X:
		return "X";
	case BUTTONS_Y:
		return "Y";
	case BUTTONS_LeftStick:
		return "LS";
	case BUTTONS_LeftShoulder:
		return "LB";
		/*case BUTTONS_LeftTrigger:
			return "LT";*/
	case BUTTONS_RightStick:
		return "RS";
	case BUTTONS_RightShoulder:
		return "RB";
		/*case BUTTONS_RightTrigger:
			return "RT";*/
	case BUTTONS_Start:
		return "START";
	case BUTTONS_Back:
		return "BACK";
	case BUTTONS_DPadUp:
		return "DPAD_UP";
	case BUTTONS_DPadRight:
		return "DPAD_RIGHT";
	case BUTTONS_DPadDown:
		return "DPAD_DOWN";
	case BUTTONS_DPadLeft:
		return "DPAD_LEFT";
		/*case BUTTONS_LeftThumbstickUp:
			return "LS_UP";
		case BUTTONS_LeftThumbstickRight:
			return "LS_RIGHT";
		case BUTTONS_LeftThumbstickDown:
			return "LS_DOWN";
		case BUTTONS_LeftThumbstickLeft:
			return "LS_LEFT";
		case BUTTONS_RightThumbstickUp:
			return "RS_UP";
		case BUTTONS_RightThumbstickRight:
			return "RS_RIGHT";
		case BUTTONS_RightThumbstickDown:
			return "RS_DOWN";
		case BUTTONS_RightThumbstickLeft:
			return "RS_LEFT";*/
	}
	return "?";
}
const char* InputCheck_GetNameTypeMouseButton(InputCheck* data)
{
	switch (data->mMouseButton)
	{
	case MOUSEBUTTONS_MOUSE_LEFTBUTTON:
		return "LMB";
	case MOUSEBUTTONS_MOUSE_RIGHTBUTTON:
		return "RMB";
	case MOUSEBUTTONS_MOUSE_MIDDLEBUTTON:
		return "MMB";
	case MOUSEBUTTONS_MOUSE_XBUTTON1:
		return "MXB1";
	case MOUSEBUTTONS_MOUSE_XBUTTON2:
		return "MXB2";
	}
	return "";
}
const char* InputCheck_GetGlyphStringTypeKey(InputCheck* data)
{
	if (data->mKey == KEYS_OemSemicolon)
	{
		return "Semicolon";
	}
	if (data->mKey == KEYS_OemPlus)
	{
		return "Plus";
	}
	if (data->mKey == KEYS_OemComma)
	{
		return "Comma";
	}
	if (data->mKey == KEYS_OemMinus)
	{
		return "Minus";
	}
	if (data->mKey == KEYS_OemPeriod)
	{
		return "Period";
	}
	if (data->mKey == KEYS_OemQuestion)
	{
		return "/";
	}
	if (data->mKey == KEYS_OemBackslash)
	{
		return "\\";
	}
	if (data->mKey == KEYS_OemTilde)
	{
		return "`";
	}
	if (data->mKey == KEYS_OemOpenBrackets)
	{
		return "[";
	}
	if (data->mKey == KEYS_OemCloseBrackets)
	{
		return "]";
	}
	return Keys_GetKeyName(data->mKey);
}
//const char* ToString();
bool InputCheck_IsDummy(InputCheck* data)
{
	return data->mType == INPUTCHECK_TYPE_DUMMY;
}
bool InputCheck_Check(InputPlayer* playerInput, InputCheck* data)
{
	switch (data->mType)
	{
	case INPUTCHECK_TYPE_KEY:
		return InputCheck_CheckTypeKey(playerInput, data);
	case INPUTCHECK_TYPE_MOUSEBUTTON:
		return InputCheck_CheckTypeMouseButton(playerInput, data);
	case INPUTCHECK_TYPE_BUTTON:
		return InputCheck_CheckTypeButton(playerInput, data);
	case INPUTCHECK_TYPE_AXIS:
		return InputCheck_CheckTypeAxis(data);
	}
	return false;
}
void InputCheck_UpdateAnalogValue(InputPlayer* playerInput, InputCheck* data)
{
	data->mAnalogValue = 0;

	if (data->mType != INPUTCHECK_TYPE_AXIS)
	{
		return;
	}

	float currentVal = 0;
	if (Input_IsSimultaneousInputForController())
	{
		currentVal = ControllerStates_GetHighestAnalogDataValue(data->mAxis);
		data->mAnalogValue = Math_fabsf(InputCheck_CorrectAnalogForDirection(data->mAxisDirection, currentVal));
		return;
	}

	if (!InputPlayer_IsUsingController(&playerInput))
	{
		return;
	}

	currentVal = ControllerState_GetAnalogData(InputPlayer_GetController(&playerInput), data->mAxis);
	data->mAnalogValue = Math_fabsf(InputCheck_CorrectAnalogForDirection(data->mAxisDirection, currentVal));
}
bool InputCheck_IsAnalog(InputCheck* data)
{
	if (data->mType == INPUTCHECK_TYPE_AXIS)
	{
		return true;
	}
	return false;
}
const char* InputCheck_GetName(InputCheck* data)
{
	return "TODO C99";
	//switch (data->mType)
	//{
	//case TYPE_KEY:
	//	return OeStrings::Get("GEN_BIND_KEY") + ": " + Keys::GetKeyName(static_cast<Keys::Key>(data->mKey));
	//case TYPE_MOUSEBUTTON:
	//	return OeStrings::Get("GEN_BIND_MOUSE") + ": " + GetNameTypeMouseButton(data);
	//case TYPE_BUTTON:
	//	return "Button: " + GetNameTypeButton(data);
	//case TYPE_AXIS:
	//	return GetNameTypeAxis(data);
	//}
	//return OeStrings::Get("GEN_BIND_NOT_SET");
}
//void Write(InputCheck* data, const char* begin, std::shared_ptr<OeIniWriter> writer);
//void Read(InputCheck* data, const char* begin, std::shared_ptr<OeIniReader> reader);
bool InputCheck_IsGlyphImage(InputCheck* data)
{
	if ((data->mType == INPUTCHECK_TYPE_AXIS) || (data->mType == INPUTCHECK_TYPE_BUTTON))
	{
		return true;
	}
	return false;
}
bool InputCheck_IsController(InputCheck* data)
{
	if ((data->mType == INPUTCHECK_TYPE_AXIS) || (data->mType == INPUTCHECK_TYPE_BUTTON))
	{
		return true;
	}
	return false;
}
const char* InputCheck_GetGlyphString(InputCheck* data)
{
	switch (data->mType)
	{
	case INPUTCHECK_TYPE_KEY:
		return InputCheck_GetGlyphStringTypeKey(data);
	case INPUTCHECK_TYPE_MOUSEBUTTON:
		return InputCheck_GetNameTypeMouseButton(data);
	case INPUTCHECK_TYPE_BUTTON:
		return InputCheck_GetGlyphStringForController(InputCheck_GetNameTypeButton(data));
	case INPUTCHECK_TYPE_AXIS:
		return InputCheck_GetGlyphStringForController(InputCheck_GetNameTypeAxis(data));
	}
	return "";
}
const char* InputCheck_GetGlyphStringForController(const char* value)
{
	return "TODOC99";
	//return "GLYPH_" + OeUtils::GetGlyphType() + "_" + value;
}
InputCheck InputCheck_CreateCheckKey(int key)
{
	InputCheck tempCheck = { 0 };
	tempCheck.mType = INPUTCHECK_TYPE_KEY;
	tempCheck.mKey = key;
	return tempCheck;
}
InputCheck InputCheck_CreateCheckMouseButton(int mouseButton)
{
	InputCheck tempCheck = { 0 };
	tempCheck.mType = INPUTCHECK_TYPE_MOUSEBUTTON;
	tempCheck.mMouseButton = mouseButton;
	return tempCheck;
}
InputCheck InputCheck_CreateCheckButton(int button)
{
	InputCheck tempCheck = { 0 };
	tempCheck.mType = INPUTCHECK_TYPE_BUTTON;
	tempCheck.mButton = button;
	return tempCheck;
}
InputCheck InputCheck_CreateCheckAxis(int axis, int direction)
{
	InputCheck tempCheck = { 0 };
	tempCheck.mType = INPUTCHECK_TYPE_AXIS;
	tempCheck.mAxis = axis;
	tempCheck.mAxisDirection = direction;
	return tempCheck;
}