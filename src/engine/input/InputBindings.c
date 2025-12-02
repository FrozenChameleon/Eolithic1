/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "InputBindings.h"

#include "ActionList.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"

void InputBindings_Init()
{

}
InputAction* InputBindings_GetDefaultActions()
{
	return NULL;
}
void InputBindings_ResetAllPlayerBindingsToDefaultAndSave()
{

}
void InputBindings_SetupKey(InputAction* data, int32_t place, const char* s, const char* check, int32_t key)
{

}
void InputBindings_SetupMouseButton(InputAction* data, int32_t place, const char* s, const char* check, int32_t mouseButton)
{

}
void InputBindings_SetupButton(InputAction* data, int32_t place, const char* s, const char* check, int32_t button)
{

}
void InputBindings_SetupAxis(InputAction* data, int32_t place, const char* s, const char* check, int32_t axis, int32_t direction)
{

}
bool InputBindings_HaveAllPlayersLoadedBindings()
{
	return false;
}
void InputBindings_LoadAllPlayerBindings()
{

}
void InputBindings_SaveAllBindings()
{

}
//void InputBindings_ResetAllPlayerCertainBindingsToDefaultAndSave(std::vector<std::string>& actions, int32_t indexStart, int32_t length);
bool InputBindings_DoBindingsExistFor(int player, const char* action, int32_t indexStart, int32_t length)
{
	return false;
}
void InputBindings_SyncAllBindingsToAllPlayers()
{

}
InputAction* InputBindings_GetBindings(int player)
{
	return NULL;
}
InputAction* InputBindings_GetActionFromBindings(int player, const char* name)
{
	return NULL;
}
InputAction* InputBindings_GetActionFromArray(InputAction* actions, const char* name)
{
	for (int i = 0; i < ACTIONLIST_LENGTH; i += 1)
	{
		InputAction* currentAction = &actions[i];
		if (Utils_StringEqualTo(currentAction->mName, name))
		{
			return currentAction;
		}
	}

	Logger_LogWarning("UNABLE TO GET INPUT ACTION:");
	Logger_LogWarning(name);

	return &actions[0];
}
