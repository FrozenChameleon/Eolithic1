/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"

typedef struct StringPair
{
	char mKey[EE_FILENAME_MAX];
	char mValue[EE_FILENAME_MAX];
} StringPair;

typedef struct BufferReader BufferReader;

extern const StringPair StringPair_Empty;

void StringPair_Read(StringPair* pair, BufferReader* reader);