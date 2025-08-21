/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "MetaMapChunk.h"
#include "../math/PointRectangle.h"
#include "../utils/FixedChar260.h"

enum { LEVEL_CAMERA_DATA_STRING_DATA_LIMIT = 10 };

typedef struct LevelCameraData
{
	MetaMapChunk* mAttachedChunk;
	PointRectangle mVolumeTrigger;
	PointRectangle mVolumeBounds;
	int mDirectionX;
	int mDirectionY;
	bool mIsPersistent;
	bool mIsDualX;
	bool mIsDualY;
	bool mIsUpFrozen;
	bool mIsRightFrozen;
	bool mIsDownFrozen;
	bool mIsLeftFrozen;
	const char* mScript;
	int mId;
	bool mIsTransition;
	int mNumberTransitionTo;
	int mNumberTransitionFrom;
	bool mIsTransitionX;
	bool mIsTransitionY;
	FixedChar260 mStringData[LEVEL_CAMERA_DATA_STRING_DATA_LIMIT];
} LevelCameraData;

