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
#include "../utils/MString.h"

typedef struct DrawTile
{
	MString* mAnimation;
	Point mPoint;
	bool mFlipX;
	bool mFlipY;
	float mRotation;
	Point mOffsetPoint;
} DrawTile;