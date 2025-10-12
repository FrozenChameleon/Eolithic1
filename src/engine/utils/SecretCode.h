#pragma once

#include "Utils.h"
#include "../input/ActionList.h"
#include "../input/Input.h"

typedef struct SecretCode
{
	int32_t mDepth;
} SecretCode;

const extern SecretCode SecretCode_Nothing;

enum SecretCodeButtons
{
	SECRETCODES_BUTTON_UP = 0,
	SECRETCODES_BUTTON_RIGHT = 1,
	SECRETCODES_BUTTON_DOWN = 2,
	SECRETCODES_BUTTON_LEFT = 3,
	SECRETCODES_BUTTON_BACK = 4,
	SECRETCODES_BUTTON_START = 5,
	SECRETCODES_AMOUNT_OF_SECRET_BUTTONS = 6
};

bool SecretCodes_UpdateSecretCode(SecretCode* data, bool (*code)(int));
bool SecretCodes_Check(int buttonToCheck, int currentDepth);