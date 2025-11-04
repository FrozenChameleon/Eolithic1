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
	const char* mName;
	Timer mTimerDoubleTap;
	InputChecks mChecks;
} InputAction;

enum
{
	INPUT_ACTION_DOUBLE_TAP_LENGTH = 12
};

void InputAction_ClearPolledInput(InputAction* action);
void InputAction_Init(const char* name, InputAction* action);
//static void Write(InputAction* action, const std::string& begin, std::shared_ptr<OeIniWriter> writer);
//static void Read(InputAction* action, const std::string& begin, std::shared_ptr<OeIniReader> reader);
void InputAction_Update(InputAction* action, InputPlayer* input);
//static void DrawCurrentGlyph(InputAction* action, OeSpriteBatch* spriteBatch, int depth, const std::string& font,
//	Color color, bool centerX, bool centerY, int alignmentX, int alignmentY, float x, float y, Vector2 scale, bool forceControllerGlyph);
//static void DrawCurrentGlyph(InputAction* action, OeSpriteBatch* spriteBatch, int depth, const std::string& font,
//	Color colorForText, Color colorForSheet, bool centerX, bool centerY, int alignmentX, int alignmentY, float x, float y,
//	Vector2 scale, bool forceControllerGlyph);
//static Rectangle GetCurrentGlyphRectangle(InputAction* action, std::string font, bool forceControllerGlyph);
//static Rectangle GetGlyphRectangle(InputAction* action, int index, std::string font);
//static void DrawGlyph(InputAction* action, int index, OeSpriteBatch* spriteBatch, int depth, std::string font,
//	Color color, bool centerX, bool centerY, int alignmentX, int alignmentY, float x, float y, Vector2 scale);
//std::string ToString();