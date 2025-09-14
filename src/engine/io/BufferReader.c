/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "BufferReader.h"

#include "SDL3/SDL.h"
#include "../utils/Utils.h"
#include "File.h"

static uint64_t _mRefs;

typedef struct BufferReader
{
	FixedByteBuffer* mBuffer;
	SDL_IOStream* mIOStream;
	FixedChar260 mPath;
} BufferReader;

FixedByteBuffer* BufferReader_ReadBytes(BufferReader* br, int64_t length)
{
	FixedByteBuffer* fbb = FixedByteBuffer_Create(length);
	SDL_ReadIO(br->mIOStream, FixedByteBuffer_GetBuffer(fbb), length);
	return fbb;
}
int64_t BufferReader_Position(BufferReader* br)
{
	return BufferReader_Tell(br);
}
void BufferReader_Seek(BufferReader* br, int64_t offset, SeekFrom type)
{
	SDL_SeekIO(br->mIOStream, offset, type);
}
FixedByteBuffer* BufferReader_GetBuffer(BufferReader* br)
{
	return br->mBuffer;
}
uint64_t BufferReader_GetSize(BufferReader* br)
{
	return FixedByteBuffer_GetLength(br->mBuffer);
}
uint8_t* BufferReader_GetBufferData(BufferReader* br)
{
	return FixedByteBuffer_GetBuffer(br->mBuffer);
}
int64_t BufferReader_Tell(BufferReader* br)
{
	return SDL_TellIO(br->mIOStream);
}
uint8_t BufferReader_ReadU8(BufferReader* br)
{
	uint8_t value;
	SDL_ReadU8(br->mIOStream, &value);
	return value;
}
bool BufferReader_ReadBoolean(BufferReader* br)
{
	return (BufferReader_ReadU8(br) != 0);
}
uint16_t BufferReader_ReadU16(BufferReader* br)
{
	uint16_t value;
	SDL_ReadU16LE(br->mIOStream, &value);
	return value;
}
int16_t BufferReader_ReadI16(BufferReader* br)
{
	uint16_t source = BufferReader_ReadU16(br);
	int16_t dst;
	Utils_memcpy(&dst, &source, sizeof(int16_t));
	return dst;
}
uint32_t BufferReader_ReadU32(BufferReader* br)
{
	uint32_t value;
	SDL_ReadU32LE(br->mIOStream, &value);
	return value;
}
int32_t BufferReader_ReadI32(BufferReader* br)
{
	uint32_t source = BufferReader_ReadU32(br);
	int32_t dst;
	Utils_memcpy(&dst, &source, sizeof(int32_t));
	return dst;
}
uint64_t BufferReader_ReadU64(BufferReader* br)
{
	uint64_t value;
	SDL_ReadU64LE(br->mIOStream, &value);
	return value;
}
int64_t BufferReader_ReadI64(BufferReader* br)
{
	uint64_t source = BufferReader_ReadU64(br);
	int64_t dst;
	Utils_memcpy(&dst, &source, sizeof(int64_t));
	return dst;
}
float BufferReader_ReadSingle(BufferReader* br)
{
	uint32_t source = BufferReader_ReadU32(br);
	float dst;
	Utils_memcpy(&dst, &source, sizeof(float));
	return dst;
}
double BufferReader_ReadDouble(BufferReader* br)
{
	uint64_t source = BufferReader_ReadU64(br);
	double dst;
	Utils_memcpy(&dst, &source, sizeof(double));
	return dst;
}
uint8_t BufferReader_ReadJustTheStringLength(BufferReader* br)
{
	return BufferReader_ReadU8(br);
}
void BufferReader_ReadJustTheStringData(BufferReader* br, uint8_t stringLength, char* dst, size_t maxlen)
{
	memset(dst, 0, maxlen);
	for (int i = 0; i < stringLength; i += 1)
	{
		uint8_t c = BufferReader_ReadU8(br);
		if (i < maxlen)
		{
			dst[i] = c;
		}
	}
	if (stringLength < maxlen)
	{
		dst[stringLength] = '\0';
	}
}
void BufferReader_ReadString(BufferReader* br, char* dst, size_t maxlen)
{
	uint8_t stringLength = BufferReader_ReadJustTheStringLength(br);
	BufferReader_ReadJustTheStringData(br, stringLength, dst, maxlen);
}
bool BufferReader_HasNext(BufferReader* br)
{
	int64_t cur = BufferReader_Tell(br);
	uint64_t end = BufferReader_GetSize(br);
	if (cur >= end)
	{
		return false;
	}
	return true;
}
BufferReader* BufferReader_Create(FixedByteBuffer* fbb)
{
	_mRefs += 1;
	BufferReader* br = Utils_malloc(sizeof(BufferReader));
	br->mBuffer = fbb;
	br->mIOStream = SDL_IOFromConstMem(FixedByteBuffer_GetBuffer(fbb), FixedByteBuffer_GetLength(fbb));
	return br;
}
BufferReader* BufferReader_CreateFromPath(const char* path)
{
	return BufferReader_Create(File_ReadAll(path));
}
void BufferReader_Dispose(BufferReader* br, bool doNotDisposeBuffer)
{
	_mRefs -= 1;
	if (!doNotDisposeBuffer)
	{
		FixedByteBuffer_Dispose(br->mBuffer);
	}
	SDL_CloseIO(br->mIOStream);
	Utils_free(br);
}
uint64_t BufferReader_GetRefs()
{
	return _mRefs;
}
