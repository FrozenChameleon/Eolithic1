/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "Prop.h"
#include "../math/Vector2.h"
#include "../utils/FixedChar260.h"

typedef struct PropInstance
{
	Prop* INTERNAL_mCachedPropData;
	int mDepth;
	float mScale;
	float mRotation;
	bool mFlipX;
	bool mFlipY;
	FixedChar260 mName;
	Vector2 mOffset;
	Vector2 mDrawOffset;
} PropInstance;

