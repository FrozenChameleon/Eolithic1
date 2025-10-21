/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../render/Sheet.h"
#include "../utils/Macros.h"
#include "../utils/MString.h"

typedef bool(*Achievement_ConditionFunc);

typedef struct Achievement
{
	bool mIsCertified;
	bool mIsHidden;
	bool mIsUnlocked;
	MString* mName;
	MString* mDescription;
	MString* mLockedDescription;
	bool (*mCondition)();
	Sheet* mSheet;
} Achievement;

void Achievement_Init(Achievement* achievement, bool (*condition)(), const char* name, const char* description, const char* lockedDescription, const char* image, bool isHidden);
void Achievement_Update(bool doNotCertify, Achievement* achievement, int index);
void Achievement_UnlockAchievement(bool doNotCertify, Achievement* achievement, int index);
void Achievement_CertifyAchievement(Achievement* achievement, int index);