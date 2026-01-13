/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Point.h"
#include "../resources/Resource.h"
#include "../render/Color.h"
#include "../utils/Macros.h"
#include "../utils/MString.h"

typedef struct MetaMapChunk
{
	Point _mPosition;
	Resource* _mLevelDataResource;
	int mMyId;
	Color mColor;
	char mFileName[EE_FILENAME_MAX];
} MetaMapChunk;

