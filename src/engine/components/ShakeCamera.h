#pragma once

#include "../utils/Timer.h"

typedef struct ShakeCamera
{
	int32_t mMinX;
	int32_t mMaxX;
	int32_t mMinY;
	int32_t mMaxY;
	Timer mTimer;
} ShakeCamera;