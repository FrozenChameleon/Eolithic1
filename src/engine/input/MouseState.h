/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Point.h"
#include "../math/Vector2.h"
#include "MouseButtons.h"

typedef struct MouseData
{
	Vector2 _mMousePosition;
	int32_t _mScrollWheelValue;
	bool _mIsButtonDown[MOUSEBUTTONS_AMOUNT_OF_MOUSE_BUTTONS];
} MouseData;


void MouseData_CopyFrom(MouseData* md, const MouseData* otherData);
void MouseData_Clear(MouseData* md);
void MouseData_ClearOnlyButtonData(MouseData* md);
void MouseData_Poll(MouseData* md);
int32_t MouseData_GetScrollWheelValue(const MouseData* md);
float MouseData_GetMouseX(const MouseData* md);
float MouseData_GetMouseY(const MouseData* md);
bool MouseData_IsButtonPressed(const MouseData* md, int32_t button);

void MouseState_Init();
void MouseState_MuteInput();
bool MouseState_IsButtonPressed(int32_t button);
bool MouseState_IsButtonTapped(int32_t button);
bool MouseState_IsButtonReleased(int32_t button);
bool MouseState_IsAnyButtonReleased();
bool MouseState_IsAnyButtonTapped();
void MouseState_ClearEverything();
void MouseState_ClearOnlyButtonData();
void MouseState_Poll();
int32_t MouseState_GetScrollWheelValue();
float MouseState_GetMouseX();
float MouseState_GetMouseY();
float MouseState_GetDifferenceMouseX();
float MouseState_GetDifferenceMouseY();
bool MouseState_JustScrolledUp();
bool MouseState_JustScrolledDown();
void MouseState_INTERNAL_SetScrollWheelValue(int32_t value);