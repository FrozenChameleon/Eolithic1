#include "RenderStream.h"

void RenderStream_Clear(RenderStream* rs)
{
	DynamicByteBuffer_SetLength(rs->_mBuffer, 0);
}
RenderCommandTileLayer* RenderStream_GetRenderCommandLayerUninitialized(RenderStream* rs)
{
	return DynamicByteBuffer_GetUninitializedMemoryBlock(rs->_mBuffer, sizeof(RenderCommandTileLayer));
}
RenderCommandManyRectangle* RenderStream_GetRenderCommandManyRectangleUninitialized(RenderStream* rs)
{
	return DynamicByteBuffer_GetUninitializedMemoryBlock(rs->_mBuffer, sizeof(RenderCommandManyRectangle));
}
//RenderCommandString* GetRenderCommandStringUninitialized();
RenderCommandSheet* RenderStream_GetRenderCommandSheetUninitialized(RenderStream* rs)
{
	return DynamicByteBuffer_GetUninitializedMemoryBlock(rs->_mBuffer, sizeof(RenderCommandSheet));
}
DynamicByteBuffer* RenderStream_GetBuffer(RenderStream* rs)
{
	return rs->_mBuffer;
}
void RenderStream_PreallocateBuffer(RenderStream* rs, int32_t initialCapacity)
{
	if (initialCapacity <= 4) //No change.
	{
		return;
	}

	DynamicByteBuffer_GetUninitializedMemoryBlock(rs->_mBuffer, initialCapacity - 1);
	RenderStream_Clear(rs);
}