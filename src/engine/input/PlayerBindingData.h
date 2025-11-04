/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "ActionList.h"
#include "InputAction.h"

#include "../io/FixedByteBuffer.h"

typedef struct PlayerBindingData
{
	int32_t _mPlayerNumber;
	bool _mHasLoaded;
	InputAction _mBindings[ACTIONLIST_LENGTH];
} PlayerBindingData;

void PlayerBindingData_Init(int playerNumber);
const char* PlayerBindingData_GetFilePlayerPath();
void PlayerBindingData_LogLoadSuccess();
void PlayerBindingData_LogLoadFailure();
//void PlayerBindingData_LoadFromStream(std::shared_ptr<OeIniReader> reader);
FixedByteBuffer* PlayerBindingData_CreateBufferFromBindings();
//void PlayerBindingData_ResetCertainBindingsToDefault(std::vector<std::string>& actions, int indexStart, int length);
bool PlayerBindingData_DoBindingsExistFor(const char* action, int indexStart, int length);
void PlayerBindingData_SetAsLoaded();
InputAction* PlayerBindingData_GetBindings();
void PlayerBindingData_ResetToDefault();
bool PlayerBindingData_HasLoaded();
//void PlayerBindingData_Load();
//void PlayerBindingData_Save();