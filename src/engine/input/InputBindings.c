#include "InputBindings.h"

#include "InputPlayer.h"
#include "../globals/Globals.h"
#include "Input.h"
#include "ActionList.h"
#include "../utils/Cvars.h"
#include "../utils/Logger.h"
#include "../core/Game.h"
#include "../core/GameHelper.h"
#include "../service/Service.h"
#include "../io/BufferReader.h"
#include "../io/BufferWriter.h"
#include "../utils/Utils.h"
#include "../utils/IStringArray.h"

static const char* CONTAINER_DISPLAY_NAME = "GameBindings";
static const char* CONTAINER_NAME = "GameBindingsContainer";

static const int CURRENT_DATA_VERSION = 0;
static const char* data_version = "data_version";
static const char* data_count = "data_count";

#define PLAYERBINDINGS_LEN INPUT_MAXIMUM_PLAYER_COUNT

static InputAction _mDefaultBindings[PLAYERBINDINGDATA_BINDINGS_LEN];
static PlayerBindingData _mPlayerBindings[PLAYERBINDINGS_LEN];

static bool _mHasInit;
static MString* _mTempString;

const char* PlayerBindingData_GetFilePlayerPath(PlayerBindingData* pbd)
{
	MString_Assign(&_mTempString, "player");
	MString_AddAssignString(&_mTempString, Utils_IntToStringStaticBuffer(pbd->_mPlayerNumber));
	MString_AddAssignString(&_mTempString, ".bin");
	return MString_GetText(_mTempString);
}
void PlayerBindingData_LogLoadSuccess(PlayerBindingData* pbd)
{
	MString_Assign(&_mTempString, "Bindings have been loaded for player #");
	MString_AddAssignString(&_mTempString, Utils_IntToStringStaticBuffer(pbd->_mPlayerNumber));
	Logger_LogInformation(MString_GetText(_mTempString));
}
void PlayerBindingData_LogLoadFailure(PlayerBindingData* pbd)
{
	MString_Assign(&_mTempString, "Unable to load bindings for player #");
	MString_AddAssignString(&_mTempString, Utils_IntToStringStaticBuffer(pbd->_mPlayerNumber));
	Logger_LogInformation(MString_GetText(_mTempString));
}
void PlayerBindingData_LoadFromStream(PlayerBindingData* pbd, BufferReader* reader)
{
	int version = BufferReader_ReadI32(reader);
	int count = BufferReader_ReadI32(reader);
	for (int i = 0; i < count; i += 1)
	{
		MString* begin = NULL;
		MString_Assign(&begin, Utils_IntToStringStaticBuffer(i));
		MString_AddAssignString(&begin, "_");
		InputAction data;
		InputAction_Init(EE_STR_NOT_SET, &data);
		InputAction_Read(&data, MString_GetText(begin), reader);
		pbd->_mBindings[i] = data;
	}
}
FixedByteBuffer* PlayerBindingData_CreateBufferFromBindings(PlayerBindingData* pbd)
{
	return NULL;
	//TODO C99
	/*
	BufferWriter* writer = BufferWriter_Create();
	BufferWriter_WriteInt32(writer, data_version, CURRENT_DATA_VERSION);
	BufferWriter_WriteInt32(writer, data_count, PLAYERBINDINGDATA_BINDINGS_LEN);
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		MString* begin = NULL;
		MString_Assign(&begin, Utils_IntToStringStaticBuffer(i));
		MString_AddAssignString(&begin, "_");
		InputAction_Write(&pbd->_mBindings[i], begin, writer);
		MString_Dispose(&begin);
	}

	BufferWriter_WriteEOF(writer);
	return BufferWriter_ToFixedByteBuffer(writer);*/
}

void PlayerBindingData_Init(PlayerBindingData* pbd, IStringArray* actionList, int playerNumber)
{
	Utils_memset(pbd, 0, sizeof(PlayerBindingData));
	pbd->_mPlayerNumber = playerNumber;
}

void PlayerBindingData_ResetCertainBindingsToDefault(PlayerBindingData* pbd, IStringArray* actions, int indexStart, int length)
{
	InputAction* defaultActions = InputBindings_GetDefaultActions();
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		for (int j = 0; j < IStringArray_Length(actions); j += 1)
		{
			if (MString_EqualToString(pbd->_mBindings[i].mName, IStringArray_Get(actions, j)))
			{
				InputAction* currentAction = &pbd->_mBindings[i];
				InputAction* defaultAction = &defaultActions[i];
				for (int k = indexStart; k < indexStart + length; k++)
				{
					InputCheck* defaultCheck = InputChecks_Get(&defaultAction->mChecks, k);
					InputChecks_Set(&currentAction->mChecks, k, *defaultCheck);
				}
			}
		}
	}

	//TODO C99 OeLogger_LogInformation("Player #" + std_to_string(_mPlayerNumber) + " certain bindings (" + std_to_string(indexStart) + "-" + std_to_string((indexStart + (length - 1))) + ") have been reset to default");
}
bool PlayerBindingData_DoBindingsExistFor(PlayerBindingData* pbd, const char* action, int indexStart, int length)
{
	int dummyCounter = 0;
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		if (MString_EqualToString(pbd->_mBindings[i].mName, action))
		{
			InputAction* currentAction = &pbd->_mBindings[i];
			for (int j = indexStart; j < indexStart + length; j++)
			{
				InputCheck* check = InputChecks_Get(&currentAction->mChecks, j);
				if (check->mType == INPUTCHECK_TYPE_DUMMY)
				{
					dummyCounter += 1;
				}
			}
		}
	}

	if (dummyCounter >= length)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void PlayerBindingData_SetAsLoaded(PlayerBindingData* pbd)
{
	pbd->_mHasLoaded = true;
}
InputAction* PlayerBindingData_GetBindings(PlayerBindingData* pbd)
{
	return 	pbd->_mBindings;
}
void PlayerBindingData_ResetToDefault(PlayerBindingData* pbd)
{
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		pbd->_mBindings[i] = _mDefaultBindings[i];
	}
}
bool PlayerBindingData_HasLoaded(PlayerBindingData* pbd)
{
	return pbd->_mHasLoaded;
}
void PlayerBindingData_Load(PlayerBindingData* pbd)
{
	if (pbd->_mHasLoaded)
	{
		return;
	}

	//TODO C99
	/*
	const char* filename = PlayerBindingData_GetFilePlayerPath();
	BufferRequest request = OeService_AskToRetrieveBuffer(false, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, filename);
	if (request.mIsBufferReady)
	{
		_mHasLoaded = true;
		if (request.mBuffer == nullptr)
		{
			LogLoadFailure();
			return;
		}
		else
		{
			//try
			//{
			std_shared_ptr<OeIniReader> reader = OeIniReader_CreateNewOeIniReader(true, OeStream_CreateNewStream(request.mBuffer));
			LoadFromStream(reader);
			LogLoadSuccess();
			return;
			// }
			//catch (...)
			//{
			//	OeLogger_LogError("Unable to read binding data!");
			//	LogLoadFailure();
			//	return;
			//}
		}
	}*/
}
void PlayerBindingData_Save(PlayerBindingData* pbd)
{
	//TODO C99
	/*
	const char* filename = PlayerBindingData_GetFilePlayerPath();
	OeService_SaveBuffer(false, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, filename, CreateBufferFromBindings());
	OeLogger_LogInformation("Bindings have been saved for player #" + std_to_string(_mPlayerNumber) + ", " + filename);
	OeUtils_JustSaved();*/
}

static bool IsMirroringBindingsDisabled()
{
	return Cvars_GetAsBool(CVARS_ENGINE_DISABLE_PLAYER_BINDING_MIRRORING);
}
static void ResetAllPlayerBindingsToDefault()
{
	for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
	{
		PlayerBindingData_ResetToDefault(&_mPlayerBindings[i]);
	}
}
static void CreateDefaultBindings(InputAction* inputData, IStringArray* strings)
{
	Utils_memset(inputData, 0, sizeof(InputAction) * PLAYERBINDINGDATA_BINDINGS_LEN);
	for (int i = 0; i < IStringArray_Length(strings); i += 1)
	{
		InputAction_Init(IStringArray_Get(strings, i), &inputData[i]);
	}
	GameHelper_DefaultBindings(strings, inputData);
}
static void CopyActions(const InputAction* copyFrom, InputAction* copyTo)
{
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		copyTo[i] = copyFrom[i];
	}
}
static void UpdateAllBindingsToMatchPlayerOne()
{
	/*
	std_vector<InputAction>& playerOneBindings = _mPlayerBindings[0].GetBindings();
	for (int i = 0; i < _mPlayerBindings.size(); i += 1)
	{
		if (i != 0)
		{
			CopyActions(playerOneBindings, _mPlayerBindings[i].GetBindings());
		}
	}
	*/
}

void InputBindings_Init()
{
	if (_mHasInit)
	{
		return;
	}

	IStringArray* actionList = ActionList_GetArray();
	CreateDefaultBindings(_mDefaultBindings, actionList);
	for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
	{
		PlayerBindingData_Init(&_mPlayerBindings[i], actionList, i);
	}

	ResetAllPlayerBindingsToDefault();

	_mHasInit = true;
}
InputAction* InputBindings_GetDefaultActions()
{
	return _mDefaultBindings;
}
void InputBindings_ResetAllPlayerBindingsToDefaultAndSave()
{
	ResetAllPlayerBindingsToDefault();
	InputBindings_SaveAllBindings();
}
void InputBindings_SetupKey(InputAction* data, int place, const char* s, const char* check, int key)
{
	if (Utils_StringEqualTo(s, check))
	{
		InputChecks_Set(&data->mChecks, place, InputCheck_CreateCheckKey(key));
	}
}
void InputBindings_SetupMouseButton(InputAction* data, int place, const char* s, const char* check, int mouseButton)
{
	if (Utils_StringEqualTo(s, check))
	{
		InputChecks_Set(&data->mChecks, place, InputCheck_CreateCheckMouseButton(mouseButton));
	}
}
void InputBindings_SetupButton(InputAction* data, int place, const char* s, const char* check, int button)
{
	if (Utils_StringEqualTo(s, check))
	{
		InputChecks_Set(&data->mChecks, place, InputCheck_CreateCheckButton(button));
	}
}
void InputBindings_SetupAxis(InputAction* data, int place, const char* s, const char* check, int axis, int direction)
{
	if (Utils_StringEqualTo(s, check))
	{
		InputChecks_Set(&data->mChecks, place, InputCheck_CreateCheckAxis(axis, direction));
	}
}
bool InputBindings_HaveAllPlayersLoadedBindings()
{
	for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
	{
		if (!PlayerBindingData_HasLoaded(&_mPlayerBindings[i]))
		{
			return false;
		}
	}
	return true;
}
void InputBindings_LoadAllPlayerBindings()
{
	bool bindingsAreMirrored = !IsMirroringBindingsDisabled();

	if (Cvars_GetAsBool(CVARS_ENGINE_LOADING_SAVE_DATA_DISABLED) || Globals_IsLoadingUserDataDisabled())
	{
		for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
		{
			PlayerBindingData_SetAsLoaded(&_mPlayerBindings[i]);
		}
		InputBindings_SyncAllBindingsToAllPlayers();
		if (bindingsAreMirrored)
		{
			UpdateAllBindingsToMatchPlayerOne();
		}
		return;
	}

	int len = PLAYERBINDINGS_LEN;
	if (bindingsAreMirrored)
	{
		len = 1;
	}
	bool isDone = true;
	for (int i = 0; i < len; i += 1)
	{
		PlayerBindingData* player = &_mPlayerBindings[i];
		if (!PlayerBindingData_HasLoaded(player))
		{
			PlayerBindingData_Load(player);
			if (!PlayerBindingData_HasLoaded(player))
			{
				isDone = false;
			}
		}
	}

	if (isDone)
	{
		for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
		{
			PlayerBindingData_SetAsLoaded(&_mPlayerBindings[i]);
		}
		if (bindingsAreMirrored)
		{
			UpdateAllBindingsToMatchPlayerOne();
		}
		InputBindings_SyncAllBindingsToAllPlayers();
	}
}
void InputBindings_SaveAllBindings()
{
	if (Cvars_GetAsBool(CVARS_ENGINE_SAVING_SAVES_DISABLED) || Globals_IsSavingUserDataDisabled())
	{
		InputBindings_SyncAllBindingsToAllPlayers();
		return;
	}

	bool bindingsAreMirrored = !IsMirroringBindingsDisabled();
	int len = PLAYERBINDINGS_LEN;
	if (bindingsAreMirrored)
	{
		len = 1;
	}
	for (int i = 0; i < len; i += 1)
	{
		PlayerBindingData_Save(&_mPlayerBindings[i]);
	}

	if (bindingsAreMirrored)
	{
		UpdateAllBindingsToMatchPlayerOne();
	}
	InputBindings_SyncAllBindingsToAllPlayers();
}
void InputBindings_ResetAllPlayerCertainBindingsToDefaultAndSave(IStringArray* actions, int indexStart, int length)
{
	for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
	{
		PlayerBindingData_ResetCertainBindingsToDefault(&_mPlayerBindings[i], actions, indexStart, length);
	}

	InputBindings_SaveAllBindings();
}
bool InputBindings_DoBindingsExistFor(int player, const char* action, int indexStart, int length)
{
	return PlayerBindingData_DoBindingsExistFor(&_mPlayerBindings[player], action, indexStart, length);
}
void InputBindings_SyncAllBindingsToAllPlayers()
{
	for (int i = 0; i < PLAYERBINDINGS_LEN; i += 1)
	{
		CopyActions(PlayerBindingData_GetBindings(&_mPlayerBindings[i]), 
			InputPlayer_GetActionsForBindingsSync(Input_GetPlayer(i)));
	}
}
InputAction* InputBindings_GetBindings(int player)
{
	return PlayerBindingData_GetBindings(&_mPlayerBindings[player]);
}
InputAction* InputBindings_GetActionFromBindings(int player, const char* name)
{
	return  InputBindings_GetActionFromArray(PlayerBindingData_GetBindings(&_mPlayerBindings[player]), name);
}
InputAction* InputBindings_GetActionFromArray(InputAction* actions, const char* name)
{
	for (int i = 0; i < PLAYERBINDINGDATA_BINDINGS_LEN; i += 1)
	{
		InputAction* action = &actions[i];
		if (MString_EqualToString(action->mName, name))
		{
			return action;
		}
	}

	MString* tempStr = NULL;
	MString_Assign(&tempStr, "Unable to find action: ");
	MString_AddAssignString(&tempStr, name);
	Logger_LogError(MString_GetText(tempStr));
	MString_Dispose(&tempStr);
	return &INPUTACTION_DUMMY_ACTION;
}
