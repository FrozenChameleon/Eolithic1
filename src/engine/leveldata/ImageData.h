/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../utils/Macros.h"

typedef struct ImageData
{
	bool mIsAdditive;
	Vector2 mOrigin;
	Point mOffset;
	int mAnimationLoopPoint;
	bool mCanAnimate;
	bool mAnimationStops;
	bool mAnimationBlanks;
	int mFlipSpeed;
	int mDepth;
	float mInitialRotation;
	char mImage[EE_FILENAME_MAX];
	int mScaler;
} ImageData;

