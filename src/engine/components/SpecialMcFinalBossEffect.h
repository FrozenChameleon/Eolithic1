#pragma once

#include "../render/Animation.h"
#include "../math/Point.h"
#include "../math/Vector2.h"

typedef struct SpecialMcFinalBossEffect
{
	int mLineCounter;
	Point mRandomOffset;
	Vector2 mPosition;
	Timer mTimerBleed;
	Timer mTimerLine;
	Animation mAnimation;
	const char* mAnimationName;
	Vector2 mBloodOffset;
	bool mDisableShaking;
	int mBloodCutoff;
	int mForcedDirection;
} SpecialMcFinalBossEffect;

