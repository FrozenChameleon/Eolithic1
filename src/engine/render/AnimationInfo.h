#pragma once

#include "stdbool.h"
#include "../utils/Macros.h"

typedef struct AnimationInfo
{
	bool mHasStart;
	IString mSheetName;
	IString mBaseName;
	int mFrames;
	int mNumberOfDigits;
} AnimationInfo;