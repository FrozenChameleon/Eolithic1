/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Point.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct Line
{
	Point mBegin;
	Point mEnd;
	bool mEnterDownOnly;
	bool mEnterLeftOnly;
	bool mEnterUpOnly;
	bool mEnterRightOnly;
	bool mIsGap;
	bool mIsFirstLine;
	bool mIsLastLine;
	bool mOneWayUp;
	bool mOneWayRight;
	bool mOneWayDown;
	bool mOneWayLeft;
	int mOverrideSpeedFromPlayer;
	int mOverrideSpeedFromMinecart;
} Line;

