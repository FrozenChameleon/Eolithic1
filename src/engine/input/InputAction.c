/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "InputAction.h"

#include "InputCheck.h"
#include "InputChecks.h"
#include "../utils/Utils.h"
#include "Input.h"

InputAction INPUTACTION_DUMMY_ACTION = { 0 };

void InputAction_ClearPolledInput(InputAction* action)
{
	action->mTimeHeld = 0;
	action->mAnalogValue = 0;
	action->mWasAnalog = false;
	action->mIsPressed = false;
	action->mIsPressedLastFrame = false;
	action->mIsPressedOrReleased = false;
	action->mIsTapped = false;
	action->mIsDoubleTapped = false;
	action->mIsReleased = false;
	action->mIsCheckDoubleTap = false;
	Timer_Reset(&action->mTimerDoubleTap);
}
void InputAction_Init(const char* name, InputAction* action)
{
	Utils_memset(action, 0, sizeof(InputAction));
	MString_Assign(&action->mName, name);
	Timer_Init(&action->mTimerDoubleTap, INPUT_ACTION_DOUBLE_TAP_LENGTH);
}
void InputAction_Write(InputAction* action, const char* begin, BufferWriter* writer)
{

}
void InputAction_Read(InputAction* action, const char* begin, BufferReader* reader)
{

}
void InputAction_Update(InputAction* action, InputPlayer* input)
{
	action->mIsPressedLastFrame = action->mIsPressed;
	action->mIsPressed = false;
	action->mIsTapped = false;
	action->mIsReleased = false;
	action->mAnalogValue = 0;
	action->mWasAnalog = false;

	for (int i = 0; i < INPUTCHECKS_LENGTH; i += 1)
	{
		InputCheck* check = InputChecks_Get(&action->mChecks, i);

		InputCheck_UpdateAnalogValue(input, check);

		if (INPUT_FLAG_IS_ON_MENU)
		{
			if (check->mType == INPUTCHECK_TYPE_MOUSEBUTTON)
			{
				continue;
			}
		}

		if (InputCheck_Check(input, check))
		{
			action->mIsPressed = true;
			if (InputCheck_IsAnalog(check))
			{
				action->mWasAnalog = true;
			}
			else
			{
				action->mWasAnalog = false;
				action->mAnalogValue = 1;
				break;
			}
		}
	}

	for (int i = 0; i < INPUTCHECKS_LENGTH; i += 1)
	{
		InputCheck* check = InputChecks_Get(&action->mChecks, i);
		if (InputCheck_IsAnalog(check))
		{
			if (check->mAnalogValue > action->mAnalogValue) //Save highest analog value
			{
				action->mAnalogValue = check->mAnalogValue;
			}
		}
	}

	if (action->mIsPressed && !action->mIsPressedLastFrame)
	{
		action->mIsTapped = true;
	}

	if (!action->mIsPressed && action->mIsPressedLastFrame)
	{
		action->mIsReleased = true;
	}

	if (action->mIsPressed) // Get amount held in press.
	{
		action->mTimeHeld += 1;
	}
	else
	{
		action->mTimeHeld = 0;
	}

	if (action->mIsDoubleTapped)
	{
		action->mIsDoubleTapped = false;
		action->mIsCheckDoubleTap = false;
		Timer_Reset(&action->mTimerDoubleTap);
	}
	else if (action->mIsCheckDoubleTap) // Check for double tap.
	{
		if (action->mIsTapped)
		{
			action->mIsDoubleTapped = true;
		}
		else if (Timer_Update(&action->mTimerDoubleTap))
		{
			action->mIsDoubleTapped = false;
			action->mIsCheckDoubleTap = false;
		}
	}

	if (action->mIsTapped)
	{
		action->mIsCheckDoubleTap = true;
	}

	action->mIsPressedOrReleased = (action->mIsPressed || action->mIsReleased);
}