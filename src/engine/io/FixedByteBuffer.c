/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "FixedByteBuffer.h"

#include "../utils/Utils.h"

#define INITIAL_CAPACITY 1024

static uint64_t _mRefs;

typedef struct FixedByteBuffer
{
	uint64_t mLength;
	uint8_t* mBuffer;
} FixedByteBuffer;

uint8_t* FixedByteBuffer_GetBuffer(const FixedByteBuffer* fbb)
{
	return fbb->mBuffer;
}
uint64_t FixedByteBuffer_GetLength(const FixedByteBuffer* fbb)
{
	return fbb->mLength;
}
FixedByteBuffer* FixedByteBuffer_CreateAndTakeOwnership(uint64_t length, uint8_t* buffer)
{
	_mRefs += 1;
	FixedByteBuffer* fbb = Utils_malloc(sizeof(FixedByteBuffer));
	fbb->mLength = length;
	fbb->mBuffer = buffer;
	return fbb;
}
FixedByteBuffer* FixedByteBuffer_Create(uint64_t length)
{
	return FixedByteBuffer_CreateAndTakeOwnership(length, Utils_malloc(sizeof(uint8_t) * length));
}
void FixedByteBuffer_Dispose(FixedByteBuffer* fbb)
{
	_mRefs -= 1;
	Utils_free(fbb->mBuffer);
	Utils_free(fbb);
}
uint64_t FixedByteBuffer_GetRefs()
{
	return _mRefs;
}
