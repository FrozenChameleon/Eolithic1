#pragma once

#include "../utils/Timer.h"
#include "../render/Color.h"

typedef struct MirrorEffect
{
	int mDepth;
	bool mIsOn;
	Timer mTimer;
	Color mColor;
	float mListPositionsX[3];
	float mListPositionsY[3];
	float mListRotations[3];
} MirrorEffect;

void MirrorEffect_SetOn(MirrorEffect* me);
void MirrorEffect_SetOff(MirrorEffect* me);