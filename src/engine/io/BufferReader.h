/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "FixedByteBuffer.h"
#include "../utils/MString.h"

typedef struct BufferReader BufferReader;

typedef enum SeekFrom
{
	BUFFER_READER_SEEK_FROM_BEGIN = 0,
	BUFFER_READER_SEEK_FROM_CURRENT = 1,
	BUFFER_READER_SEEK_FROM_END = 2
} SeekFrom;

FixedByteBuffer* BufferReader_ReadBytes(BufferReader* br, int64_t length);
int64_t BufferReader_Position(BufferReader* br);
void BufferReader_Seek(BufferReader* br, int64_t offset, SeekFrom type);
FixedByteBuffer* BufferReader_GetBuffer(BufferReader* br);
uint64_t BufferReader_GetSize(BufferReader* br);
uint8_t* BufferReader_GetBufferData(BufferReader* br);
int64_t BufferReader_Tell(BufferReader* br);
uint8_t BufferReader_ReadU8(BufferReader* br);
bool BufferReader_ReadBoolean(BufferReader* br);
uint16_t BufferReader_ReadU16(BufferReader* br);
int16_t BufferReader_ReadI16(BufferReader* br);
uint32_t BufferReader_ReadU32(BufferReader* br);
int32_t BufferReader_ReadI32(BufferReader* br);
uint64_t BufferReader_ReadU64(BufferReader* br);
int64_t BufferReader_ReadI64(BufferReader* br);
float BufferReader_ReadFloat(BufferReader* br);
double BufferReader_ReadDouble(BufferReader* br);
int* BufferReader_ReadIntArray2D(BufferReader* br, int width, int height);
uint8_t BufferReader_ReadJustTheStringLength(BufferReader* br);
void BufferReader_ReadJustTheStringData(BufferReader* br, uint8_t stringLength, char* dst, size_t maxlen);
void BufferReader_ReadString(BufferReader* br, char* dst, size_t maxlen);
MString* BufferReader_ReadMString(BufferReader* br);
bool BufferReader_HasNext(BufferReader* br);
BufferReader* BufferReader_Create(FixedByteBuffer* fbb);
BufferReader* BufferReader_CreateFromPath(const char* path);
void BufferReader_Dispose(BufferReader* br, bool doNotDisposeBuffer);
uint64_t BufferReader_GetRefs();
