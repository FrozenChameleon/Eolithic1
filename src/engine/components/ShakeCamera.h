#pragma once

#include "../utils/Timer.h"

struct ShakeCamera
{
	int mMinX;
	int mMaxX;
	int mMinY;
	int mMaxY;
	Timer mTimer;
};

