/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/MString.h"

typedef struct DatInfo
{
	MString* mPath;
	int64_t mLength;
	int64_t mPosition;
} DatInfo;

