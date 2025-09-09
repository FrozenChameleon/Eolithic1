#pragma once

#include "../math/Vector2.h"
#include "../utils/Timer.h"

struct Sheet;

struct SpecialDrawExplosion final
{
	int mCounter;
	Vector2 mInitialPosition;
	float mSectionWidth;
	float mSectionHeight;
	float mOffsetsX[3];
	float mOffsetsY[3];
	float mWidths[3];
	bool mDraw;
	int mSides[3]; //Was booleans...
	Sheet* mSheetReference;
	Timer mTimer;
};

