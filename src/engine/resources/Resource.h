/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "../utils/Macros.h"
#include "../utils/FixedChar260.h"

typedef struct Resource
{
	void* mData;
	ResourceID mID;
	IString mPath;
	IString mFileNameWithoutExtension;
} Resource;