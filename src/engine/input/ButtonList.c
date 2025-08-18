/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ButtonList.h"

#include "Buttons.h"

int32_t ButtonList_GetButton(int index)
{
	switch (index)
	{
	case 0:
		return BUTTONS_DPadUp;
	case 1:
		return BUTTONS_DPadDown;
	case 2:
		return BUTTONS_DPadLeft;
	case 3:
		return BUTTONS_DPadRight;
	case 4:
		return BUTTONS_Start;
	case 5:
		return BUTTONS_Back;
	case 6:
		return BUTTONS_LeftStick;
	case 7:
		return BUTTONS_RightStick;
	case 8:
		return BUTTONS_LeftShoulder;
	case 9:
		return BUTTONS_RightShoulder;
	case 10:
		return BUTTONS_A;
	case 11:
		return BUTTONS_B;
	case 12:
		return BUTTONS_X;
	case 13:
		return BUTTONS_Y;
	}

	return -1;
}
