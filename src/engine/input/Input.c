/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Input.h"

#include "InputPlayer.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include "InputAction.h"
#include "ControllerState.h"
#include "ControllerStates.h"
#include "../math/Math.h"
//#include "OeInputBindings.h"
#include "../core/Game.h"
#include "../service/Service.h"
//#include "../components/Camera.h"
#include "../utils/Cvars.h"
//#include "../globals/OeGlobals.h"
//#include "../render/OeRenderer.h"
#include "../utils/Logger.h"

typedef struct DoubleClickData
{
	int mTimeSinceLastTap;
	bool mIsTapped;
	bool mIsDoubleClicked;
} DoubleClickData;

typedef struct OverrideDeadzoneData
{
	bool mIsOverriding;
	int mRadialDeadzone;
	int mOuterDeadzone;
	int mAxialDeadzone;
} OverrideDeadzoneData;

bool INPUT_FLAG_IS_ON_MENU = false;
bool INPUT_FLAG_IS_ON_MULTIPLAYER_SETUP_MENU = false;
bool INPUT_FLAG_IS_PLAYING_MASTER_RECORDING_FAST = false;

static bool _mHasInit;
static InputPlayer _mPlayers[INPUT_MAXIMUM_PLAYER_COUNT];
static DoubleClickData _mLeftDoubleClick;
static OverrideDeadzoneData _mOverrideDeadzoneData;
static int _mBlockMKBInputForFrames = 0;
static int _mMasterRecordingState = 0;

static void HandleDoubleClickData(DoubleClickData* data, bool tapValue)
{
	data->mIsDoubleClicked = false;
	data->mIsTapped = tapValue;
	if (data->mIsTapped)
	{
		if (data->mTimeSinceLastTap < INPUT_ACTION_DOUBLE_TAP_LENGTH)
		{
			data->mIsDoubleClicked = true;
		}
		data->mTimeSinceLastTap = 0;
	}
	else
	{
		data->mTimeSinceLastTap++;
	}
}
static bool IsStickBeyondOuterDeadzone(Vector2 stick, float outerDeadzone)
{
	return (Vector2_Length(stick) > (1 - outerDeadzone));
}
static Vector2 ProcessStickRadialDeadzone(Vector2 stick, float radialDeadzone)
{
	if (Vector2_Length(stick) < radialDeadzone)
	{
		return Vector2_Zero;
	}
	else
	{
		return stick;
	}
}
static Vector2 ProcessStickAxialDeadzone(Vector2 stick, float axialDeadzone)
{
	if (Math_fabsf(stick.X) < axialDeadzone)
	{
		stick.X = 0;
	}
	if (Math_fabsf(stick.Y) < axialDeadzone)
	{
		stick.Y = 0;
	}
	return stick;
}

void Input_Init()
{
	if (_mHasInit)
	{
		return;
	}

	InputPlayer_Init(&_mPlayers[0], 0);
	InputPlayer_Init(&_mPlayers[1], 1);
	InputPlayer_Init(&_mPlayers[2], 2);
	InputPlayer_Init(&_mPlayers[3], 3);

	MouseState_Init();
	KeyboardState_Init();
	ControllerStates_Init();

	//TODO C99 InputBindings::Init();

	//TODO C99 InputBindings::SyncAllBindingsToAllPlayers();

	_mHasInit = true;
}
bool Input_HasInit()
{
	return _mHasInit;
}

void Input_MuteAllInput()
{
	ControllerStates_MuteInput();
	KeyboardState_MuteInput();
	MouseState_MuteInput();
}
bool Input_IsAnythingPressedByAnyPlayer()
{
	int amountOfActiveInput = Input_GetAmountOfActivePlayers();
	for (int i = 0; i < amountOfActiveInput; i++)
	{
		if (InputPlayer_IsPlayerPressingAnything(&_mPlayers[i]))
		{
			return true;
		}
	}
	if (Input_IsLeftMousePressed())
	{
		return true;
	}
	if (Input_IsMiddleMousePressed())
	{
		return true;
	}
	if (Input_IsRightMousePressed())
	{
		return true;
	}
	return false;
}
bool Input_IsPressedByAnyPlayer(const char* action)
{
	int amountOfActiveInput = Input_GetAmountOfActivePlayers();
	for (int i = 0; i < amountOfActiveInput; i += 1)
	{
		if (Input_GetPlayerAction(i, action)->mIsPressed)
		{
			return true;
		}
	}
	return false;
}
bool Input_IsReleasedByAnyPlayer(const char* action)
{
	int amountOfActiveInput = Input_GetAmountOfActivePlayers();
	for (int i = 0; i < amountOfActiveInput; i += 1)
	{
		if (Input_GetPlayerAction(i, action)->mIsReleased)
		{
			return true;
		}
	}
	return false;
}
bool Input_IsTappedByAnyPlayer(const char* action)
{
	int amountOfActiveInput = Input_GetAmountOfActivePlayers();
	for (int i = 0; i < amountOfActiveInput; i += 1)
	{
		if (Input_GetPlayerAction(i, action)->mIsTapped)
		{
			return true;
		}
	}
	return false;
}
int32_t Input_GetLongestTimeHeldByAnyPlayer(const char* action)
{
	int amountOfActiveInput = Input_GetAmountOfActivePlayers();
	int longestTimeHeld = 0;
	for (int i = 0; i < amountOfActiveInput; i += 1)
	{
		int timeHeld = Input_GetPlayerAction(i, action)->mTimeHeld;
		if (Input_GetPlayerAction(i, action)->mTimeHeld > longestTimeHeld)
		{
			longestTimeHeld = timeHeld;
		}
	}
	return longestTimeHeld;
}
int32_t Input_GetAmountOfActivePlayers()
{
	int amount = 1;
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		if (i != 0)
		{
			if (InputPlayer_IsInputDeviceSet(&_mPlayers[i]))
			{
				amount += 1;
			}
		}
	}
	return amount;
}
void Input_Update(bool doNotUpdateMasterRecording)
{
	if (!_mHasInit)
	{
		Logger_LogError("Need to init input before update!");
		return;
	}

	ControllerState_BeforePollingUpdate();

	MouseState_Poll();
	KeyboardState_Poll();
	ControllerStates_Poll();

	if (!doNotUpdateMasterRecording)
	{
		if (Input_IsPlayingMasterRecording())
		{
			//TODO C99?OeControllerStates_Read(); //Overwrite polled controller input with master recording if reading it
		}

		if (Input_IsRecordingMasterRecording())
		{
			//TODO C99?OeControllerStates_Write();
		}
	}

	if (_mBlockMKBInputForFrames > 0)
	{
		MouseState_ClearOnlyButtonData();
		KeyboardState_ClearEverything();
		_mBlockMKBInputForFrames -= 1;
	}

	if (Input_IsSinglePlayerInputMode())
	{
		InputPlayer_DetectInputDevice(&_mPlayers[INPUT_PLAYER_1], false);
	}

	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		InputPlayer_Update(&_mPlayers[i]);
	}

	HandleDoubleClickData(&_mLeftDoubleClick, Input_IsLeftMouseTapped());
}
bool Input_IsAnyPlayerUsingThisDeviceNumber(int32_t deviceNumber)
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i++)
	{
		if (InputPlayer_GetDeviceNumber(&_mPlayers[i]) == deviceNumber)
		{
			return true;
		}
	}
	return false;
}
bool Input_IsSimultaneousInputForKeyboard()
{
	if (!Input_IsSinglePlayerInputMode())
	{
		return false;
	}

	return true;
}
bool Input_IsSimultaneousInputForController()
{
	if (!Input_IsSinglePlayerInputMode())
	{
		return false;
	}

	if (Service_PlatformDisablesSimultaneousInputForController() && !Input_IsRecordingOrPlayingMasterRecording())
	{
		return false;
	}

	return true;
}
bool Input_IsSinglePlayerInputMode()
{
	if (INPUT_FLAG_IS_ON_MULTIPLAYER_SETUP_MENU)
	{
		return false;
	}

	if (Input_GetAmountOfActivePlayers() > 1)
	{
		return false;
	}

	return true;
}
bool Input_IsMultiplayerInputMode()
{
	return !Input_IsSinglePlayerInputMode();
}
void Input_BlockMKBInputForFrames(int32_t frames)
{
	_mBlockMKBInputForFrames = frames;
}
InputPlayer* Input_GetPlayerOne()
{
	return &_mPlayers[0];
}
InputPlayer* Input_GetPlayer(int32_t i)
{
	return &_mPlayers[i];
}
ControllerState* Input_GetController(int32_t number)
{
	return ControllerStates_GetController(number);
}
InputAction* Input_GetPlayerOneAction(const char* name)
{
	return Input_GetPlayerAction(0, name);
}
InputAction* Input_GetPlayerAction(int32_t playerNumber, const char* name)
{
	return InputPlayer_GetAction(&_mPlayers[playerNumber], name);
}
//Vector2 GetCameraAdjustedMouse(const Camera* camera);
bool Input_JustScrolledUp()
{
	return MouseState_JustScrolledUp();
}
bool Input_JustScrolledDown()
{
	return MouseState_JustScrolledDown();
}
int32_t Input_GetDifferenceMouseX()
{
	return MouseState_GetDifferenceMouseX();
}
int32_t Input_GetDifferenceMouseY()
{
	return MouseState_GetDifferenceMouseY();
}
int32_t Input_GetMouseX()
{
	return MouseState_GetMouseX();
}
int32_t Input_GetMouseY()
{
	return MouseState_GetMouseY();
}
Point Input_GetMouse()
{
	Point temp;
	temp.X = Input_GetMouseX();
	temp.Y = Input_GetMouseY();
	return temp;
}
Vector2 Input_GetScaledMouseForRetroScreen()
{
	//TODOC99
	return Vector2_Zero;
}
float Input_GetScaledMouseForRetroScreenX()
{
	return Input_GetScaledMouseForRetroScreen().X;
}
float Input_GetScaledMouseForRetroScreenY()
{
	return Input_GetScaledMouseForRetroScreen().X;
}
//Vector2 GetCameraAdjustedMouseForRetroScreen(const Camera* camera);
//float GetCameraAdjustedMouseForRetroScreenX(const Camera* camera);
//float GetCameraAdjustedMouseForRetroScreenY(const Camera* camera);
bool Input_MouseHasChangedPosition()
{
	if ((Input_GetDifferenceMouseX() == 0) && (Input_GetDifferenceMouseY() == 0))
	{
		return false;
	}
	return true;
}
bool Input_IsLeftMousePressed()
{
	return MouseState_IsButtonPressed(MOUSEBUTTONS_MOUSE_LEFTBUTTON);
}
bool Input_IsLeftMouseTapped()
{
	return MouseState_IsButtonTapped(MOUSEBUTTONS_MOUSE_LEFTBUTTON);
}
bool Input_IsLeftMouseReleased()
{
	return MouseState_IsButtonReleased(MOUSEBUTTONS_MOUSE_LEFTBUTTON);
}
bool Input_IsLeftMouseDoubleClicked()
{
	return _mLeftDoubleClick.mIsDoubleClicked;
}
bool Input_IsRightMousePressed()
{
	return MouseState_IsButtonPressed(MOUSEBUTTONS_MOUSE_RIGHTBUTTON);
}
bool Input_IsRightMouseTapped()
{
	return MouseState_IsButtonTapped(MOUSEBUTTONS_MOUSE_RIGHTBUTTON);
}
bool Input_IsRightMouseReleased()
{
	return MouseState_IsButtonReleased(MOUSEBUTTONS_MOUSE_RIGHTBUTTON);
}
bool Input_IsMiddleMousePressed()
{
	return MouseState_IsButtonPressed(MOUSEBUTTONS_MOUSE_MIDDLEBUTTON);
}
bool Input_IsMiddleMouseTapped()
{
	return MouseState_IsButtonTapped(MOUSEBUTTONS_MOUSE_MIDDLEBUTTON);
}
bool Input_IsMiddleMouseReleased()
{
	return MouseState_IsButtonReleased(MOUSEBUTTONS_MOUSE_MIDDLEBUTTON);
}
bool Input_IsCtrlPressed()
{
	return KeyboardState_IsKeyPressed(KEYS_LeftControl) || KeyboardState_IsKeyPressed(KEYS_RightControl);
}
bool Input_IsTabPressed()
{
	return KeyboardState_IsKeyPressed(KEYS_Tab);
}
bool Input_IsShiftPressed()
{
	return KeyboardState_IsKeyPressed(KEYS_LeftShift) || KeyboardState_IsKeyPressed(KEYS_RightShift);
}
bool Input_IsShiftTapped()
{
	return KeyboardState_IsKeyTapped(KEYS_LeftShift) || KeyboardState_IsKeyTapped(KEYS_RightShift);
}
bool Input_IsAltPressed()
{
	return KeyboardState_IsKeyPressed(KEYS_LeftAlt) || KeyboardState_IsKeyPressed(KEYS_RightAlt);
}
bool Input_IsDeletePressed()
{
	return KeyboardState_IsKeyPressed(KEYS_Delete);
}
bool Input_IsDeleteTapped()
{
	return KeyboardState_IsKeyTapped(KEYS_Delete);
}
bool Input_IsDeleteReleased()
{
	return KeyboardState_IsKeyReleased(KEYS_Delete);
}
bool Input_IsTildePressed()
{
	return KeyboardState_IsKeyPressed(KEYS_OemTilde);
}
bool Input_IsTildeReleased()
{
	return KeyboardState_IsKeyReleased(KEYS_OemTilde);
}
bool Input_IsEscapePressed()
{
	return KeyboardState_IsKeyPressed(KEYS_Escape);
}
bool Input_IsEscapeTapped()
{
	return KeyboardState_IsKeyTapped(KEYS_Escape);
}
bool Input_IsEnterTapped()
{
	return KeyboardState_IsKeyTapped(KEYS_Enter);
}
bool Input_IsModifierPressed()
{
	return Input_IsCtrlPressed() || Input_IsShiftPressed() || Input_IsAltPressed();
}
void Input_StopAllRumble()
{
	for (int i = 0; i < INPUT_MAXIMUM_PLAYER_COUNT; i += 1)
	{
		InputPlayer_Vibrate(&_mPlayers[i], 999999, 2, 0, 0);
	}
}
Vector2 Input_ProcessStickDeadzones(Vector2 stick, float radialDeadzone, float axialDeadzone, float outerDeadzone)
{
	stick = ProcessStickRadialDeadzone(stick, radialDeadzone);
	stick = ProcessStickAxialDeadzone(stick, axialDeadzone);
	if (Vector2_EqualTo(stick, Vector2_Zero))
	{
		return Vector2_Zero;
	}

	if (IsStickBeyondOuterDeadzone(stick, outerDeadzone))
	{
		Vector2_Normalize(&stick);
		return stick;
	}

	Vector2 direction = stick;
	Vector2_Normalize(&direction);
	float stickLength = Vector2_Length(stick);
	float range = 1 - radialDeadzone - outerDeadzone;
	stick = Vector2_MulSingle(direction, ((stickLength - radialDeadzone) / range));

	if (IsStickBeyondOuterDeadzone(stick, 0))
	{
		Vector2_Normalize(&stick);
	}

	return stick;
}
void Input_OverrideDeadzones(int32_t radial, int32_t outer, int32_t axial)
{
	_mOverrideDeadzoneData.mIsOverriding = true;
	_mOverrideDeadzoneData.mRadialDeadzone = radial;
	_mOverrideDeadzoneData.mOuterDeadzone = outer;
	_mOverrideDeadzoneData.mAxialDeadzone = axial;
}
int32_t Input_GetRadialDeadzone()
{
	if (_mOverrideDeadzoneData.mIsOverriding)
	{
		return _mOverrideDeadzoneData.mRadialDeadzone;
	}
	return Cvars_GetAsInt(CVARS_ENGINE_CONTROLLER_RADIAL_DEADZONE);
}
int32_t Input_GetOuterDeadzone()
{
	if (_mOverrideDeadzoneData.mIsOverriding)
	{
		return _mOverrideDeadzoneData.mOuterDeadzone;
	}
	return Cvars_GetAsInt(CVARS_ENGINE_CONTROLLER_OUTER_DEADZONE);
}
int32_t Input_GetAxialDeadzone()
{
	if (_mOverrideDeadzoneData.mIsOverriding)
	{
		return _mOverrideDeadzoneData.mAxialDeadzone;
	}
	return Cvars_GetAsInt(CVARS_ENGINE_CONTROLLER_AXIAL_DEADZONE);
}
float Input_GetRadialDeadzoneAsFloat()
{
	return (Input_GetRadialDeadzone() / 100.0f);
}
float Input_GetOuterDeadzoneAsFloat()
{
	return (Input_GetOuterDeadzone() / 100.0f);
}
float Input_GetAxialDeadzoneAsFloat()
{
	return (Input_GetAxialDeadzone() / 100.0f);
}
float Input_GetAnalogToPressThresholdForSticks()
{
	return Cvars_GetAsInt(CVARS_ENGINE_CONTROLLER_ANALOG_TO_PRESS_THRESHOLD_FOR_STICKS) / 100.0f;
}
float Input_GetAnalogToPressThresholdForTriggers()
{
	return Cvars_GetAsInt(CVARS_ENGINE_CONTROLLER_ANALOG_TO_PRESS_THRESHOLD_FOR_TRIGGERS) / 100.0f;
}
bool Input_IsRecordingMasterRecording()
{
	return _mMasterRecordingState == INPUT_MASTER_RECORDING_STATE_RECORDING;
}
bool Input_IsPlayingMasterRecording()
{
	return _mMasterRecordingState == INPUT_MASTER_RECORDING_STATE_PLAYBACK;
}
bool Input_IsRecordingOrPlayingMasterRecording()
{
	return Input_IsRecordingMasterRecording() || Input_IsPlayingMasterRecording();
}
void Input_SetMasterRecordingState(int32_t state)
{
	if (state != INPUT_MASTER_RECORDING_STATE_OFF)
	{
		//TODO C99 OeGlobals::DisableSavingAndLoadingAndAchievementsAndLeaderboards();
	}

	_mMasterRecordingState = state;
}
#if EDITOR || CHEATS
bool Input_IsKeyTapped(int32_t key)
{

}
bool Input_IsKeyReleased(int32_t key)
{

}
bool Input_IsKeyPressed(int32_t key)
{

}
int32_t Input_GetKeyTimeHeld(int32_t key)
{

}
#endif