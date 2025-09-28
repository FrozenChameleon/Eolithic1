#pragma once

#include "../math/Vector2.h"
#include "../utils/Timer.h"

typedef struct Sheet Sheet;

typedef struct SpecialMcDeathEffect
{
	int mDisplayType;
	int mCounter;
	float mSectionWidth;
	float mSectionHeight;
	float mSpeed;
	Vector2 mPositionOne;
	Vector2 mLastPositionOne;
	Vector2 mPositionTwo;
	Vector2 mLastPositionTwo;
	Vector2 mInitialPosition;
	Timer mTimer;
	Sheet* mSheetReference;
	Sheet* mSheetUpperLeft;
	Sheet* mSheetUpperRight;
	Sheet* mSheetLowerRight;
	Sheet* mSheetLowerLeft;
} SpecialMcDeathEffect;

