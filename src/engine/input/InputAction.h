/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../utils/Timer.h"
#include "InputChecks.h"
#include "../utils/MString.h"

typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;
typedef struct MString MString;

typedef struct InputAction
{
	int32_t mTimeHeld;
	float mAnalogValue;
	bool mWasAnalog;
	bool mIsPressed;
	bool mIsPressedLastFrame;
	bool mIsPressedOrReleased;
	bool mIsTapped;
	bool mIsDoubleTapped;
	bool mIsReleased;
	bool mIsCheckDoubleTap;
	MString* mName;
	Timer mTimerDoubleTap;
	InputChecks mChecks;
} InputAction;

extern InputAction INPUTACTION_DUMMY_ACTION;

enum
{
	INPUT_ACTION_DOUBLE_TAP_LENGTH = 12
};

void InputAction_ClearPolledInput(InputAction* action);
void InputAction_Init(const char* name, InputAction* action);
void InputAction_Write(InputAction* action, const char* begin, BufferWriter* writer);
void InputAction_Read(InputAction* action, const char* begin, BufferReader* reader);
void InputAction_Update(InputAction* action, InputPlayer* input);
//static void DrawCurrentGlyph(InputAction* action, OeSpriteBatch* spriteBatch, int32_t depth, const std::string& font,
//	Color color, bool centerX, bool centerY, int32_t alignmentX, int32_t alignmentY, float x, float y, Vector2 scale, bool forceControllerGlyph);
//static void DrawCurrentGlyph(InputAction* action, OeSpriteBatch* spriteBatch, int32_t depth, const std::string& font,
//	Color colorForText, Color colorForSheet, bool centerX, bool centerY, int32_t alignmentX, int32_t alignmentY, float x, float y,
//	Vector2 scale, bool forceControllerGlyph);
//static Rectangle GetCurrentGlyphRectangle(InputAction* action, std::string font, bool forceControllerGlyph);
//static Rectangle GetGlyphRectangle(InputAction* action, int32_t index, std::string font);
//static void DrawGlyph(InputAction* action, int32_t index, OeSpriteBatch* spriteBatch, int32_t depth, std::string font,
//	Color color, bool centerX, bool centerY, int32_t alignmentX, int32_t alignmentY, float x, float y, Vector2 scale);
//std::string ToString();