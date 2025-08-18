/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "../utils/Macros.h"

typedef struct Resource
{
	ResourceID mID;
	void* mData;
} Resource;