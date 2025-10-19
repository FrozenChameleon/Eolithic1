/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Timer.h"
#include "../render/Sheet.h"

typedef struct Animation
{
	int mAnimationLoopPoint;
	int mInitialFlipTimerLimit;
	int mSheetsLen;
	bool mIsSuppressed;
	bool mIsAnimationComplete;
	bool mIsLoopingDisabled;
	bool mIsReverse;
	bool mIsGoingInReverse;
	bool mIsUpdateDisabled;
	Timer mFrameTimer;
	Timer mFlipTimer;
	Sheet* mSheets;
} Animation;

void Animation_DebugTest();

void Animation_Init(Animation* data, const char* spriteSheet, int flipTimer);
void Animation_Init2(Animation* data, Sheet* sheets, int sheetsLen, int flipTimer);

const char* Animation_GetCurrentSheetName(Animation* data);
bool Animation_Update(Animation* data);
void Animation_ResetAnimation(Animation* data);
Sheet* Animation_GetCurrentSheet(Animation* data);
int Animation_DigitsAtEnd(const char* sheetName, int sheetNameLength);
void Animation_CheckForAnimation(const char* textureName);
void Animation_BuildAnimations();
void Animation_AddToAnimationMap(const char* baseName, const char* sheetName, int frames, int digits);
void Animation_CreateAnimationStringArray(IStringArray* listToAddTo, const char* baseName, int frames, int digits);
const char* Animation_GetConvertedName(const char* baseName);
const char** Animation_GetAnimationSheets(const char* animation);