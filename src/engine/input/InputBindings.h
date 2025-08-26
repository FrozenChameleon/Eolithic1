/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "InputAction.h"

void InputBindings_Init();
InputAction* InputBindings_GetDefaultActions();
void InputBindings_ResetAllPlayerBindingsToDefaultAndSave();
void InputBindings_SetupKey(InputAction* data, int place, const char* s, const char* check, int key);
void InputBindings_SetupMouseButton(InputAction* data, int place, const char* s, const char* check, int mouseButton);
void InputBindings_SetupButton(InputAction* data, int place, const char* s, const char* check, int button);
void InputBindings_SetupAxis(InputAction* data, int place, const char* s, const char* check, int axis, int direction);
bool InputBindings_HaveAllPlayersLoadedBindings();
void InputBindings_LoadAllPlayerBindings();
void InputBindings_SaveAllBindings();
//void InputBindings_ResetAllPlayerCertainBindingsToDefaultAndSave(std::vector<std::string>& actions, int indexStart, int length);
bool InputBindings_DoBindingsExistFor(int player, const char* action, int indexStart, int length);
void InputBindings_SyncAllBindingsToAllPlayers();
InputAction* InputBindings_GetBindings(int player);
InputAction* InputBindings_GetActionFromBindings(int player, const char* name);
InputAction* InputBindings_GetActionFromArray(InputAction* actions, const char* name);
