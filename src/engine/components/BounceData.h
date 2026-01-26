/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

#pragma once

typedef struct BounceData
{
	int32_t mBounces;
	float mVelocity;
	bool mIsNotFirstFrame;
	bool mWasUsed;
} BounceData;

