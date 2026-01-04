#pragma once

#include "../io/FixedByteBuffer.h"

typedef enum BufferRequestState
{
	BUFFER_REQUEST_STATE_DOING_NOTHING = 0,
	BUFFER_REQUEST_STATE_RETRIEVING = 1,
	BUFFER_REQUEST_STATE_RETRIEVED = 2
} BufferRequestState;

typedef struct BufferRequest
{
	bool mIsBufferReady;
	FixedByteBuffer* mBuffer;
	BufferRequestState mBufferRequestState;
}BufferRequest;