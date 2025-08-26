/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct InputPlayer InputPlayer;

typedef struct InputCheck
{
	int32_t mType;
	int32_t mMouseButton;
	int32_t mAxis;
	int32_t mAxisDirection;
	float mAnalogValue;
	int32_t mKey;
	int32_t mButton;
} InputCheck;

enum InputCheckType
{
	INPUT_CHECK_TYPE_DUMMY = 0,
	INPUT_CHECK_TYPE_AXIS = 1,
	INPUT_CHECK_TYPE_BUTTON = 2,
	INPUT_CHECK_TYPE_KEY = 3,
	INPUT_CHECK_TYPE_MOUSEBUTTON = 4
};

enum
{
	INPUT_CHECK_AXIS_AMOUNT = 6
};

enum InputCheckAxisInfo
{
	INPUT_CHECK_AXIS_LEFT_STICK_X = 0,
	INPUT_CHECK_AXIS_LEFT_STICK_Y = 1,
	INPUT_CHECK_AXIS_RIGHT_STICK_X = 2,
	INPUT_CHECK_AXIS_RIGHT_STICK_Y = 3,
	INPUT_CHECK_AXIS_LEFT_TRIGGER = 4,
	INPUT_CHECK_AXIS_RIGHT_TRIGGER = 5
};

float InputCheck_CorrectAnalogForDirection(int direction, float value);
bool InputCheck_CheckTypeAxis(InputCheck* data);
bool InputCheck_IsAxisTriggers(InputCheck* data);
bool InputCheck_CheckTypeButton(InputPlayer* playerInput, InputCheck* data);
bool InputCheck_CheckTypeMouseButton(InputPlayer* playerInput, InputCheck* data);
bool InputCheck_CheckTypeKey(InputPlayer* playerInput, InputCheck* data);
const char* InputCheck_GetNameTypeAxis(InputCheck* data);
const char* InputCheck_GetNameTypeButton(InputCheck* data);
const char* InputCheck_GetNameTypeMouseButton(InputCheck* data);
const char* InputCheck_GetGlyphStringTypeKey(InputCheck* data);
//const char* ToString();
bool InputCheck_IsDummy(InputCheck* data);
bool InputCheck_Check(InputPlayer* playerInput, InputCheck* data);
void InputCheck_UpdateAnalogValue(InputPlayer* playerInput, InputCheck* data);
bool InputCheck_IsAnalog(InputCheck* data);
const char* InputCheck_GetName(InputCheck* data);
//void Write(InputCheck* data, const char* begin, std::shared_ptr<OeIniWriter> writer);
//void Read(InputCheck* data, const char* begin, std::shared_ptr<OeIniReader> reader);
bool InputCheck_IsGlyphImage(InputCheck* data);
bool InputCheck_IsController(InputCheck* data);
const char* InputCheck_GetGlyphString(InputCheck* data);
const char* InputCheck_GetGlyphStringForController(const char* value);
InputCheck InputCheck_CreateCheckKey(int key);
InputCheck InputCheck_CreateCheckMouseButton(int mouseButton);
InputCheck InputCheck_CreateCheckButton(int button);
InputCheck InputCheck_CreateCheckAxis(int axis, int direction);