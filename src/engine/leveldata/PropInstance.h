/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "Prop.h"
#include "../math/Vector2.h"
#include "../utils/Macros.h"

typedef struct PropInstance
{
	Prop* INTERNAL_mCachedPropData;
	int mDepth;
	float mScale;
	float mRotation;
	bool mFlipX;
	bool mFlipY;
	char mName[EE_FILENAME_MAX];
	Vector2 mOffset;
	Vector2 mDrawOffset;
} PropInstance;

