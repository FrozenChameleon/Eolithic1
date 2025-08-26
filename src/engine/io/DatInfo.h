/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/FixedChar260.h"

typedef struct DatInfo
{
	FixedChar260 mPath;
	int64_t mLength;
	int64_t mPosition;
} DatInfo;

