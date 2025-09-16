#include "RenderStream.h"

void RenderStream_Clear(RenderStream* rs)
{
	DynamicByteBuffer_SetLength(rs->_mBuffer, 0);
}
//RenderCommandTileLayer* GetRenderCommandLayerUninitialized();
//RenderCommandManyRectangle* GetRenderCommandManyRectangleUninitialized();
//RenderCommandString* GetRenderCommandStringUninitialized();
RenderCommandSheet* RenderStream_GetRenderCommandSheetUninitialized(RenderStream* rs)
{
	return (RenderCommandSheet*)DynamicByteBuffer_GetUninitializedMemoryBlock(rs->_mBuffer, sizeof(RenderCommandSheet));
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