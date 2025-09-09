#pragma once

#include "../utils/Timer.h"

struct HitFlashKit final
{
	int mState;
	bool mIsDisabled;
	bool mShowHitFlash;
	Timer mHitFlashTimer;
};

void HitFlashKit_Setup(HitFlashKit* hfk, int time);
void HitFlashKit_ResetFlash(HitFlashKit* hfk);