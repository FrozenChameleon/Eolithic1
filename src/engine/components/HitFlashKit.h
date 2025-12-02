#pragma once

#include "../utils/Timer.h"

typedef struct HitFlashKit
{
	int mState;
	bool mIsDisabled;
	bool mShowHitFlash;
	Timer mHitFlashTimer;
} HitFlashKit;

void HitFlashKit_Setup(HitFlashKit* hfk, int32_t time);
void HitFlashKit_ResetFlash(HitFlashKit* hfk);