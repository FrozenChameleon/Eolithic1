/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "StringPair.h"

#include "../utils/Macros.h"
#include "../io/BufferReader.h"

const StringPair StringPair_Empty = { EE_STR_EMPTY, EE_STR_EMPTY };

void StringPair_Read(StringPair* pair, BufferReader* reader)
{
	//TODO C99 MEMORY LEAK!!!!!
	MString* key = BufferReader_ReadMString(reader);
	MString* value = BufferReader_ReadMString(reader);

	pair->mKey = MString_GetText(key);
	pair->mValue = MString_GetText(value);
}
