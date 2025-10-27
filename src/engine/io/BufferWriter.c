/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "BufferWriter.h"

#include "SDL3/SDL.h"
#include "../utils/Utils.h"
#include "File.h"

static uint64_t _mRefs;

typedef struct BufferWriter
{
	DynamicByteBuffer* mBuffer;
} BufferWriter;

FixedByteBuffer* BufferWriter_WriteBytes(BufferWriter* br, int64_t length)
{
	//FixedByteBuffer* fbb = FixedByteBuffer_Create(length);
	//SDL_WriteIO(br->mIOStream, FixedByteBuffer_GetBuffer(fbb), length);
	return NULL;
}
int64_t BufferWriter_Position(BufferWriter* br)
{
	return BufferWriter_Tell(br);
}
FixedByteBuffer* BufferWriter_GetBuffer(BufferWriter* br)
{
	return br->mBuffer;
}
uint64_t BufferWriter_GetSize(BufferWriter* br)
{
	return FixedByteBuffer_GetLength(br->mBuffer);
}
uint8_t* BufferWriter_GetBufferData(BufferWriter* br)
{
	return FixedByteBuffer_GetBuffer(br->mBuffer);
}
int64_t BufferWriter_Tell(BufferWriter* br)
{
	return 0;
	//return SDL_TellIO(br->mIOStream);
}
void BufferWriter_WriteU8(BufferWriter* br)
{
	//uint8_t value;
	//SDL_WriteU8(br->mIOStream, &value);
	//return value;
}
void BufferWriter_WriteBoolean(BufferWriter* br)
{
	//return (BufferWriter_WriteU8(br) != 0);
}
void BufferWriter_WriteU16(BufferWriter* br)
{
	/*
	uint16_t value;
	SDL_WriteU16LE(br->mIOStream, &value);
	return value;*/
}
void BufferWriter_WriteI16(BufferWriter* br)
{
	/*
	uint16_t source = BufferWriter_WriteU16(br);
	int16_t dst;
	Utils_memcpy(&dst, &source, sizeof(int16_t));
	return dst;*/
}
void BufferWriter_WriteU32(BufferWriter* br)
{
	/*
	uint32_t value;
	SDL_WriteU32LE(br->mIOStream, &value);
	return value;*/
}
void BufferWriter_WriteI32(BufferWriter* br)
{
	/*
	uint32_t source = BufferWriter_WriteU32(br);
	int32_t dst;
	Utils_memcpy(&dst, &source, sizeof(int32_t));
	return dst;*/
}
void BufferWriter_WriteU64(BufferWriter* br)
{
	/*
	uint64_t value;
	SDL_WriteU64LE(br->mIOStream, &value);
	return value;*/
}
void BufferWriter_WriteI64(BufferWriter* br)
{
	/*
	uint64_t source = BufferWriter_WriteU64(br);
	int64_t dst;
	Utils_memcpy(&dst, &source, sizeof(int64_t));
	return dst;*/
}
void BufferWriter_WriteSingle(BufferWriter* br)
{
	/*
	uint32_t source = BufferWriter_WriteU32(br);
	float dst;
	Utils_memcpy(&dst, &source, sizeof(float));
	return dst;*/
}
void BufferWriter_WriteDouble(BufferWriter* br)
{
	/*
	uint64_t source = BufferWriter_WriteU64(br);
	double dst;
	Utils_memcpy(&dst, &source, sizeof(double));
	return dst;*/
}
void BufferWriter_WriteJustTheStringLength(BufferWriter* br)
{
	return BufferWriter_WriteU8(br);
}
void BufferWriter_WriteJustTheStringData(BufferWriter* br, uint8_t stringLength, char* dst, size_t maxlen)
{
	/*
	memset(dst, 0, maxlen);
	for (int i = 0; i < stringLength; i += 1)
	{
		uint8_t c = BufferWriter_WriteU8(br);
		if (i < maxlen)
		{
			dst[i] = c;
		}
	}
	if (stringLength < maxlen)
	{
		dst[stringLength] = '\0';
	}
	*/
}
void BufferWriter_WriteString(BufferWriter* br, char* dst, size_t maxlen)
{
	//uint8_t stringLength = BufferWriter_WriteJustTheStringLength(br);
	//BufferWriter_WriteJustTheStringData(br, stringLength, dst, maxlen);
}
MString* BufferWriter_WriteStringToMString(BufferWriter* br)
{
	return NULL;
	/*
	int32_t newStringLength = BufferWriter_WriteJustTheStringLength(br);
	int32_t newStrCapacity = newStringLength + 1;
	MString* strToReturn = MString_CreateEmpty(newStrCapacity);
	BufferWriter_WriteJustTheStringData(br, newStringLength, strToReturn->text, newStrCapacity);
	return strToReturn;*/
}
bool BufferWriter_HasNext(BufferWriter* br)
{
	int64_t cur = BufferWriter_Tell(br);
	uint64_t end = BufferWriter_GetSize(br);
	if (cur >= end)
	{
		return false;
	}
	return true;
}
BufferWriter* BufferWriter_Create()
{
	_mRefs += 1;
	BufferWriter* br = Utils_malloc(sizeof(BufferWriter));
	br->mBuffer = DynamicByteBuffer_Create();
	return br;
}
BufferWriter* BufferWriter_CreateFromPath(const char* path)
{
	return NULL;
	//return BufferWriter_Create(File_WriteAll(path));
}
void BufferWriter_Dispose(BufferWriter* br, bool doNotDisposeBuffer)
{
	_mRefs -= 1;
	if (!doNotDisposeBuffer)
	{
		DynamicByteBuffer_Dispose(br->mBuffer);
	}
	//SDL_CloseIO(br->mIOStream);
	Utils_free(br);
}
uint64_t BufferWriter_GetRefs()
{
	return _mRefs;
}
