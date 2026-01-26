/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

#include "HitFlashKit.h"

#include "../core/Func.h"

void HitFlashKit_Setup(HitFlashKit* hfk, int32_t time)
{
	hfk->mHitFlashTimer.mLimit = time;
}
void HitFlashKit_ResetFlash(HitFlashKit* hfk)
{
	hfk->mShowHitFlash = false;
	Do_ResetFrameTimer2(&hfk->mHitFlashTimer);
}
