#pragma once

#include "stdbool.h"
#include "ActionList.h"
#include "InputAction.h"

typedef struct FixedByteBuffer FixedByteBuffer;
typedef struct BufferReader BufferReader;
typedef struct IStringArray IStringArray;

#define PLAYERBINDINGDATA_BINDINGS_LEN ACTIONLIST_LENGTH

typedef struct PlayerBindingData
{
	int _mPlayerNumber;
	bool _mHasLoaded;
	InputAction _mBindings[PLAYERBINDINGDATA_BINDINGS_LEN];
} PlayerBindingData;

void PlayerBindingData_Init(PlayerBindingData* pbd, IStringArray* actionList, int playerNumber);

const char* PlayerBindingData_GetFilePlayerPath(PlayerBindingData* pbd);
void PlayerBindingData_LogLoadSuccess(PlayerBindingData* pbd);
void PlayerBindingData_LogLoadFailure(PlayerBindingData* pbd);
void PlayerBindingData_LoadFromStream(PlayerBindingData* pbd, BufferReader* reader);
FixedByteBuffer* PlayerBindingData_CreateBufferFromBindings();
void PlayerBindingData_ResetCertainBindingsToDefault(PlayerBindingData* pbd, IStringArray* actions, int indexStart, int length);
bool PlayerBindingData_DoBindingsExistFor(PlayerBindingData* pbd, const char* action, int indexStart, int length);
void PlayerBindingData_SetAsLoaded(PlayerBindingData* pbd);
InputAction* PlayerBindingData_GetBindings(PlayerBindingData* pbd);
void PlayerBindingData_ResetToDefault(PlayerBindingData* pbd);
bool PlayerBindingData_HasLoaded(PlayerBindingData* pbd);
void PlayerBindingData_Load(PlayerBindingData* pbd);
void PlayerBindingData_Save(PlayerBindingData* pbd);

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
void InputBindings_ResetAllPlayerCertainBindingsToDefaultAndSave(IStringArray* actions, int indexStart, int length);
bool InputBindings_DoBindingsExistFor(int player, const char* action, int indexStart, int length);
void InputBindings_SyncAllBindingsToAllPlayers();
InputAction* InputBindings_GetBindings(int player);
InputAction* InputBindings_GetActionFromBindings(int player, const char* name);
InputAction* InputBindings_GetActionFromArray(InputAction* actions, const char* name);