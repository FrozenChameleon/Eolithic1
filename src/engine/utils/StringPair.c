/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "StringPair.h"

#include "../io/BufferReader.h"

void StringPair_Read(StringPair* pair, BufferReader* reader)
{
	//TODO C99 MEMORY LEAK!!!!!
	MString* key = BufferReader_ReadMString(reader);
	MString* value = BufferReader_ReadMString(reader);

	pair->mKey = MString_GetText(key);
	pair->mValue = MString_GetText(value);
}
