/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "PlayerBindingData.h"

void PlayerBindingData_Init(int playerNumber)
{

}
const char* PlayerBindingData_GetFilePlayerPath()
{
	return NULL;
}
void PlayerBindingData_LogLoadSuccess()
{

}
void PlayerBindingData_LogLoadFailure()
{

}
//void PlayerBindingData_LoadFromStream(std::shared_ptr<OeIniReader> reader)
FixedByteBuffer* PlayerBindingData_CreateBufferFromBindings()
{
	return NULL;
}
//void PlayerBindingData_ResetCertainBindingsToDefault(std::vector<std::string>& actions, int32_t indexStart, int32_t length);
bool PlayerBindingData_DoBindingsExistFor(const char* action, int32_t indexStart, int32_t length)
{
	return false;
}
void PlayerBindingData_SetAsLoaded()
{

}
InputAction* PlayerBindingData_GetBindings()
{
	return NULL;
}
void PlayerBindingData_ResetToDefault()
{

}
bool PlayerBindingData_HasLoaded()
{
	return false;
}
//void PlayerBindingData_Load();
//void PlayerBindingData_Save();