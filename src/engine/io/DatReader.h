/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "DatInfo.h"
#include "../utils/MString.h"
#include "BufferReader.h"

typedef struct DatReader DatReader;

FixedByteBuffer* DatReader_GetMemoryStream(DatReader* dr, int64_t length);
bool DatReader_HasInit(const DatReader* dr);
bool DatReader_HasNext(const DatReader* dr);
MString* DatReader_NextFilePath(DatReader* dr);
BufferReader* DatReader_NextStream(DatReader* dr, bool doNotReturnStream);
//std::shared_ptr<OeStream> DatReader_Find(const std::string& path);
DatReader* DatReader_Create(const char* path);
void DatReader_Dispose(DatReader* dr);