/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

typedef struct StringPair
{
	const char* mKey;
	const char* mValue;
} StringPair;

typedef struct BufferReader BufferReader;

void StringPair_Read(StringPair* pair, BufferReader* reader);