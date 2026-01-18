#pragma once

typedef struct BounceData
{
	int32_t mBounces;
	float mVelocity;
	bool mIsNotFirstFrame;
	bool mWasUsed;
} BounceData;

