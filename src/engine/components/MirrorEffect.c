#include "MirrorEffect.h"

#include "../core/Func.h"

void MirrorEffect_SetOn(MirrorEffect* me)
{
	if (!me->mIsOn)
	{
		Do_ResetFrameTimer2(&me->mTimer);
		me->mIsOn = true;
	}
}
void MirrorEffect_SetOff(MirrorEffect* me)
{
	if (me->mIsOn)
	{
		Do_ResetFrameTimer2(&me->mTimer);
		me->mIsOn = false;
	}
}
