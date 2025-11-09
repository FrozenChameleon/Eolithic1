/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "StringPair.h"

#include "../io/BufferReader.h"

void StringPair_Read(StringPair* pair, BufferReader* reader)
{
	pair->mKey = BufferReader_ReadMString(reader);
	pair->mValue = BufferReader_ReadMString(reader);
}
