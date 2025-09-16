#pragma once

#include "../io/DynamicByteBuffer.h"
#include "RenderCommands.h"

typedef struct RenderStream
{
	DynamicByteBuffer* _mBuffer;
} RenderStream;

void RenderStream_Clear(RenderStream* rs);
//RenderCommandTileLayer* GetRenderCommandLayerUninitialized();
//RenderCommandManyRectangle* GetRenderCommandManyRectangleUninitialized();
//RenderCommandString* GetRenderCommandStringUninitialized();
RenderCommandSheet* RenderStream_GetRenderCommandSheetUninitialized(RenderStream* rs);
DynamicByteBuffer* RenderStream_GetBuffer(RenderStream* rs);
void RenderStream_PreallocateBuffer(RenderStream* rs, int32_t initialCapacity);