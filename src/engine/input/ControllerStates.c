/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ControllerStates.h"

#include "Input.h"
#include "../math/Math.h"
#include "../globals/Globals.h"

static bool _mHasInit;

//TODO C99 static int _mMasterRecordingCurrentVersion = OeGlobals::GetNewestRecordingVersion();
static int _mMasterRecordingCurrentVersion;
static int _mMasterRecordingReadFrame;

//static BinaryWriter _mWriter;
static bool _mIsReading;
//static std::shared_ptr<BinaryReader> _mReader;
static ControllerState _mControllerStates[INPUT_MAXIMUM_PLAYER_COUNT];

static void init() //DONT FORGET THIS TODO C99
{
	/*
	static OeInputPlayer _mPlayers[OeInput::MAXIMUM_PLAYER_COUNT] =
	{
		OeInputPlayer(0),
		OeInputPlayer(1),
		OeInputPlayer(2),
		OeInputPlayer(3)
	};
	*/
}

void ControllerStates_Init()
{
	//TODO C99
}
void ControllerStates_Dispose()
{
	//TODO C99
}
void ControllerStates_Read()
{
	//TODO C99
}
void ControllerStates_Write()
{
	//TODO C99
}
void ControllerStates_Poll()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		ControllerState_Poll(&_mControllerStates[i]);
	}
}
ControllerState* ControllerStates_GetController(int number)
{
	return &_mControllerStates[number];
}
bool ControllerStates_IsAnyButtonPressedOnAnyController()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (ControllerState_IsAnyButtonPressed(&_mControllerStates[i]))
		{
			return true;
		}
	}
	return false;
}
bool ControllerStates_IsAnyButtonTappedOnAnyController()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (ControllerState_IsAnyButtonTapped(&_mControllerStates[i]))
		{
			return true;
		}
	}
	return false;
}
bool ControllerStates_IsButtonPressedOnAnyController(int button)
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (ControllerState_IsButtonPressed(&_mControllerStates[i], button))
		{
			return true;
		}
	}
	return false;
}
int ControllerStates_GetControllerNumberIfAnyButtonReleased()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (ControllerState_IsAnyButtonReleased(&_mControllerStates[i]))
		{
			return i;
		}
	}
	return -1;
}
int ControllerStates_GetControllerNumberIfAnyButtonTapped()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (ControllerState_IsAnyButtonTapped(&_mControllerStates[i]))
		{
			return i;
		}
	}
	return -1;
}
void ControllerStates_MuteInput()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		ControllerState_MuteInput(&_mControllerStates[i]);
	}
}
float ControllerStates_GetHighestAnalogDataValue(int loc)
{
	int index = -1;
	float highest = -999;
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		float value = Math_fabsf(ControllerState_GetAnalogData(&_mControllerStates[i], loc));
		if (value > highest)
		{
			highest = value;
			index = i;
		}
	}
	return ControllerState_GetAnalogData(&_mControllerStates[index], loc);
}
int ControllerStates_GetMasterRecordingReadFrame()
{
	return _mMasterRecordingReadFrame;
}
int ControllerStates_GetCurrentMasterRecordingVersion()
{
	if (!Input_IsPlayingMasterRecording())
	{
		return Globals_GetNewestRecordingVersion();
	}
	else
	{
		return _mMasterRecordingCurrentVersion;
	}
}