/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Point.h"
#include "../utils/Macros.h"

typedef struct DrawTile
{
	char mAnimation[EE_FILENAME_MAX];
	Point mPoint;
	bool mFlipX;
	bool mFlipY;
	float mRotation;
	Point mOffsetPoint;
} DrawTile;