/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Vector2.h"
#include "MetaMapChunk.h"

typedef struct LevelData LevelData;

typedef struct MetaMap
{
	MetaMapChunk* _mDynamicChunks;
	//bool _mIsSelected;
	Vector2 _mAnchor;
	Vector2 _mAnchorDiff;
	LevelData* _mLevel;
} MetaMap;

