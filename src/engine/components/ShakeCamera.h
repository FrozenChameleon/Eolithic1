#pragma once

#include "../utils/Timer.h"

typedef struct ShakeCamera
{
	int mMinX;
	int mMaxX;
	int mMinY;
	int mMaxY;
	Timer mTimer;
} ShakeCamera;