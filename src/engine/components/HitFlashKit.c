#include "HitFlashKit.h"

#include "../core/Func.h"

void HitFlashKit_Setup(HitFlashKit* hfk, int time)
{
	hfk->mHitFlashTimer.mLimit = time;
}
void OeComHitFlashKit_ResetFlash(HitFlashKit* hfk)
{
	hfk->mShowHitFlash = false;
	Do_ResetFrameTimer2(&hfk->mHitFlashTimer);
}
