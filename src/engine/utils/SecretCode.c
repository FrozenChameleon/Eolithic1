#include "SecretCode.h"

#include "../../GlobalDefs.h"

//definition private
static int _mTempCodeDepth;
static bool _mTempResetDepth;
static bool _mTempWentForward;
static bool _mTempButtons[SECRETCODES_AMOUNT_OF_SECRET_BUTTONS];

const SecretCode SecretCode_Nothing = { 0 };

bool SecretCodes_UpdateSecretCode(SecretCode* data, bool(*code)(int))
{
#ifdef GLOBAL_DEF_DISABLE_CHEAT_CODES
	return false;
#else
	_mTempCodeDepth = 0;
	_mTempResetDepth = false;
	_mTempWentForward = false;
	Utils_ResetArrayAsBool(_mTempButtons, SECRETCODES_AMOUNT_OF_SECRET_BUTTONS, false);
	bool isUnlocked = (*code)(data->mDepth);
	if (_mTempWentForward)
	{
		data->mDepth += 1;
	}
	if (_mTempResetDepth || isUnlocked)
	{
		data->mDepth = 0;
	}
	return isUnlocked;
#endif
}
bool SecretCodes_Check(int buttonToCheck, int currentDepth)
{
#ifdef GLOBAL_DEF_DISABLE_CHEAT_CODES
	return false;
#else
	int tempDepth = _mTempCodeDepth;
	_mTempCodeDepth += 1;
	if (currentDepth != tempDepth)
	{
		return false;
	}

	_mTempButtons[0] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_MENU_UP);
	_mTempButtons[1] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_MENU_RIGHT);
	_mTempButtons[2] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_MENU_DOWN);
	_mTempButtons[3] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_MENU_LEFT);
	_mTempButtons[4] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_MENU_BACK);
	_mTempButtons[5] = Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_START);

	bool isTargetTapped = false;
	bool isNotTargetTapped = false;
	for (int i = 0; i < SECRETCODES_AMOUNT_OF_SECRET_BUTTONS; i += 1)
	{
		bool isTapped = _mTempButtons[i];
		if (i == buttonToCheck)
		{
			isTargetTapped = isTapped;
		}
		else
		{
			if (isTapped)
			{
				isNotTargetTapped = true;
			}
		}
	}

	if (isNotTargetTapped)
	{
		_mTempResetDepth = true;
	}
	else
	{
		if (isTargetTapped)
		{
			_mTempWentForward = true;
			return true;
		}
	}
	return false;
#endif
}
