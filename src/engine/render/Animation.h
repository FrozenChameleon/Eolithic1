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
	bool mIsSuppressed;
	bool mIsAnimationComplete;
	bool mIsLoopingDisabled;
	bool mIsReverse;
	bool mIsGoingInReverse;
	bool mIsUpdateDisabled;
	Timer mFrameTimer;
	Timer mFlipTimer;
	//std::vector<OeSheet*>* mSheets;
} Animation;

void Animation_Init(Animation* anim, const char* whatever, int whatever2);
void Animation_Update(Animation* anim);
Sheet* Animation_GetCurrentSheet(Animation* anim);