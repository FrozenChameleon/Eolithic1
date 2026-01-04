/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "DynamicByteBuffer.h"

#include "../utils/Utils.h"

#define INITIAL_CAPACITY 1024

static uint64_t _mRefs;

typedef struct DynamicByteBuffer
{
	uint64_t mLength;
	uint64_t mCapacity;
	uint8_t* mBuffer;
} DynamicByteBuffer;

static void CheckLength(DynamicByteBuffer* dbb, size_t size)
{
	if ((dbb->mLength + size) < dbb->mCapacity)
	{
		return;
	}

	uint64_t newCapacity = dbb->mCapacity * 2;
	uint8_t* tempBuffer = Utils_malloc(sizeof(uint8_t) * newCapacity);
	Utils_memcpy(tempBuffer, dbb->mBuffer, dbb->mCapacity);
	Utils_free(dbb->mBuffer);
	dbb->mBuffer = tempBuffer;
	dbb->mCapacity = newCapacity;
}

void* DynamicByteBuffer_GetUninitializedMemoryBlock(DynamicByteBuffer* dbb, uint64_t memoryBlockLength)
{
	CheckLength(dbb, memoryBlockLength);
	void* memoryBlockStart = dbb->mBuffer + dbb->mLength;
	dbb->mLength += memoryBlockLength;
	return memoryBlockStart;
}

static void WriteSomething(DynamicByteBuffer* dbb, void* value, size_t size)
{
	CheckLength(dbb, size);
	Utils_memcpy(dbb->mBuffer + dbb->mLength, value, size);
	dbb->mLength += size;
}

void DynamicByteBuffer_WriteU8(DynamicByteBuffer* dbb, uint8_t value)
{
	WriteSomething(dbb, &value, sizeof(uint8_t));
}
void DynamicByteBuffer_WriteU16(DynamicByteBuffer* dbb, uint16_t value)
{
	WriteSomething(dbb, &value, sizeof(uint16_t));
}
void DynamicByteBuffer_WriteU32(DynamicByteBuffer* dbb, uint32_t value)
{
	WriteSomething(dbb, &value, sizeof(uint32_t));
}
void DynamicByteBuffer_WriteU64(DynamicByteBuffer* dbb, uint64_t value)
{
	WriteSomething(dbb, &value, sizeof(uint64_t));
}
void DynamicByteBuffer_WriteI8(DynamicByteBuffer* dbb, int8_t value)
{
	WriteSomething(dbb, &value, sizeof(int8_t));
}
void DynamicByteBuffer_WriteI16(DynamicByteBuffer* dbb, int16_t value)
{
	WriteSomething(dbb, &value, sizeof(int16_t));
}
void DynamicByteBuffer_WriteI32(DynamicByteBuffer* dbb, int32_t value)
{
	WriteSomething(dbb, &value, sizeof(int32_t));
}
void DynamicByteBuffer_WriteI64(DynamicByteBuffer* dbb, int64_t value)
{
	WriteSomething(dbb, &value, sizeof(int64_t));
}
void DynamicByteBuffer_WriteFloat(DynamicByteBuffer* dbb, float value)
{
	WriteSomething(dbb, &value, sizeof(float));
}
void DynamicByteBuffer_WriteDouble(DynamicByteBuffer* dbb, double value)
{
	WriteSomething(dbb, &value, sizeof(double));
}
void DynamicByteBuffer_WriteBoolean(DynamicByteBuffer* dbb, bool value)
{
	uint8_t valueToWrite = value ? 1 : 0;
	WriteSomething(dbb, &valueToWrite, sizeof(uint8_t));
}
uint8_t* DynamicByteBuffer_GetBuffer(const DynamicByteBuffer* dbb)
{
	return dbb->mBuffer;
}
uint64_t DynamicByteBuffer_GetLength(const DynamicByteBuffer* dbb)
{
	return dbb->mLength;
}
void DynamicByteBuffer_SetLength(DynamicByteBuffer* dbb, uint64_t value)
{
	dbb->mLength = value;
}
FixedByteBuffer* DynamicByteBuffer_ConvertToFixedByteBufferAndDispose(DynamicByteBuffer* dbb)
{
	FixedByteBuffer* fbb = FixedByteBuffer_Create(dbb->mLength);
	uint8_t* toBuffer = FixedByteBuffer_GetBuffer(fbb);
	Utils_memcpy(toBuffer, dbb->mBuffer, dbb->mLength);
	DynamicByteBuffer_Dispose(dbb);
	return fbb;
}
DynamicByteBuffer* DynamicByteBuffer_Create()
{
	_mRefs += 1;
	DynamicByteBuffer* dbb = Utils_malloc(sizeof(DynamicByteBuffer));
	dbb->mLength = 0;
	dbb->mCapacity = INITIAL_CAPACITY;
	dbb->mBuffer = Utils_malloc(sizeof(uint8_t) * INITIAL_CAPACITY);
	return dbb;
}
void DynamicByteBuffer_Dispose(DynamicByteBuffer* dbb)
{
	_mRefs -= 1;
	Utils_free(dbb->mBuffer);
	Utils_free(dbb);
}
uint64_t DynamicByteBuffer_GetRefs()
{
	return _mRefs;
}
