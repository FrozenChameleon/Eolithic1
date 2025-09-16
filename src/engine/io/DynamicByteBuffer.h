/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "FixedByteBuffer.h"

typedef struct DynamicByteBuffer DynamicByteBuffer;

void* DynamicByteBuffer_GetUninitializedMemoryBlock(DynamicByteBuffer* dbb, uint64_t memoryBlockLength);
void DynamicByteBuffer_WriteUInt8(DynamicByteBuffer* dbb, uint8_t value);
void DynamicByteBuffer_WriteInt32(DynamicByteBuffer* dbb, int32_t value);
void DynamicByteBuffer_WriteSingle(DynamicByteBuffer* dbb, float value);
uint8_t* DynamicByteBuffer_GetBuffer(const DynamicByteBuffer* dbb);
uint64_t DynamicByteBuffer_GetLength(const DynamicByteBuffer* dbb);
void DynamicByteBuffer_SetLength(DynamicByteBuffer* dbb, uint64_t value);
FixedByteBuffer* DynamicByteBuffer_ConvertToFixedByteBufferAndDispose(DynamicByteBuffer* dbb);
DynamicByteBuffer* DynamicByteBuffer_Create();
void DynamicByteBuffer_Dispose(DynamicByteBuffer* dbb);
uint64_t DynamicByteBuffer_GetRefs();