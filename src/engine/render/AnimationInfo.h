#pragma once

#include "stdbool.h"
#include "../utils/Macros.h"

typedef struct AnimationInfo
{
	bool mHasStart;
	char mSheetName[EE_FILENAME_MAX];
	char mBaseName[EE_FILENAME_MAX];
	int mFrames;
	int mNumberOfDigits;
} AnimationInfo;