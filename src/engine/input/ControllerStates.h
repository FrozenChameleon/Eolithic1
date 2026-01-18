/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "ControllerState.h"

void ControllerStates_Init();
void ControllerStates_Dispose();
void ControllerStates_Read();
void ControllerStates_Write();
void ControllerStates_Poll();
ControllerState* ControllerStates_GetController(int32_t number);
bool ControllerStates_IsAnyButtonPressedOnAnyController();
bool ControllerStates_IsAnyButtonTappedOnAnyController();
bool ControllerStates_IsButtonPressedOnAnyController(int32_t button);
int32_t ControllerStates_GetControllerNumberIfAnyButtonReleased();
int32_t ControllerStates_GetControllerNumberIfAnyButtonTapped();
void ControllerStates_MuteInput();
float ControllerStates_GetHighestAnalogDataValue(int32_t loc);
int32_t ControllerStates_GetMasterRecordingReadFrame();
int32_t ControllerStates_GetCurrentMasterRecordingVersion();