/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdbool.h"
#include "stdint.h"
#include "Keys.h"

typedef struct KeyboardData
{
	bool _mIsKeyDown[KEYS_AMOUNT_OF_KEYS];
} KeyboardData;

int32_t KeyboardData_GetLoc(int32_t key);
bool KeyboardData_IsKeyPressedAtLoc(const KeyboardData* kd, int32_t loc);
bool KeyboardData_IsKeyPressed(const KeyboardData* kd, int32_t key);
int32_t KeyboardData_GetTimeHeld(int32_t key);
void KeyboardData_Clear(KeyboardData* kd);
void KeyboardData_Poll(KeyboardData* kd);
void KeyboardData_CopyFrom(KeyboardData* kd, const KeyboardData* otherData);

void KeyboardState_Init();
void KeyboardState_MuteInput();
void KeyboardState_ClearEverything();
void KeyboardState_Poll();
int32_t KeyboardState_GetTimeHeld(int32_t key);
bool KeyboardState_IsKeyPressed(int32_t key);
bool KeyboardState_IsKeyTapped(int32_t key);
bool KeyboardState_IsKeyReleased(int32_t key);
bool KeyboardState_IsAnyKeyReleased();
bool KeyboardState_IsAnyKeyTapped();
bool KeyboardState_IsAnyKeyPressed();