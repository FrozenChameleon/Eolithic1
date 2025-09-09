#pragma once

#include "../utils/Timer.h"
#include "../render/Color.h"

struct MirrorEffect final
{
	int mDepth;
	bool mIsOn;
	Timer mTimer;
	Color mColor;
	float mListPositionsX[3];
	float mListPositionsY[3];
	float mListRotations[3];
};

void MirrorEffect_SetOn();
void MirrorEffect_SetOff();