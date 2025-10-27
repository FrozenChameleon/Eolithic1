/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../utils/MString.h"
#include "DynamicByteBuffer.h"

typedef struct BufferWriter BufferWriter;

FixedByteBuffer* BufferWriter_WriteBytes(BufferWriter* br, int64_t length);
int64_t BufferWriter_Position(BufferWriter* br);
FixedByteBuffer* BufferWriter_GetBuffer(BufferWriter* br);
uint64_t BufferWriter_GetSize(BufferWriter* br);
uint8_t* BufferWriter_GetBufferData(BufferWriter* br);
int64_t BufferWriter_Tell(BufferWriter* br);
void BufferWriter_WriteU8(BufferWriter* br);
void BufferWriter_WriteBoolean(BufferWriter* br);
void BufferWriter_WriteU16(BufferWriter* br);
void BufferWriter_WriteI16(BufferWriter* br);
void BufferWriter_WriteU32(BufferWriter* br);
void BufferWriter_WriteI32(BufferWriter* br);
void BufferWriter_WriteU64(BufferWriter* br);
void BufferWriter_WriteI64(BufferWriter* br);
void BufferWriter_WriteSingle(BufferWriter* br);
void BufferWriter_WriteDouble(BufferWriter* br);
void BufferWriter_WriteJustTheStringLength(BufferWriter* br);
void BufferWriter_WriteJustTheStringData(BufferWriter* br, uint8_t stringLength, char* dst, size_t maxlen);
void BufferWriter_WriteString(BufferWriter* br, char* dst, size_t maxlen);
MString* BufferWriter_WriteStringToMString(BufferWriter* br);
bool BufferWriter_HasNext(BufferWriter* br);
BufferWriter* BufferWriter_Create();
BufferWriter* BufferWriter_CreateFromPath(const char* path);
void BufferWriter_Dispose(BufferWriter* br, bool doNotDisposeBuffer);
uint64_t BufferWriter_GetRefs();
