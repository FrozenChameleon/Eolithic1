/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct VolumeData
{
	struct { char* key; int32_t value; } _mVolumeMap;
	bool _mIsMusic;
} VolumeData;
