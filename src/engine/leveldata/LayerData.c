/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "LayerData.h"

#include "../io/BufferReader.h"

const char* LayerData_GetNameSpeedX(LayerData* layer, int32_t i)
{
	return NULL;
	//return "layer_" + std::to_string(i) + "_speed_x";
}
const char* LayerData_GetNameSpeedY(LayerData* layer, int32_t i)
{
	return NULL;
	//return "layer_" + std::to_string(i) + "_speed_y";
}
const char* LayerData_GetNameDepth(LayerData* layer, int32_t i)
{
	return NULL;
	//return "layer_" + std::to_string(i) + "_depth";
}
void LayerData_WriteIni(LayerData* layer, int32_t i, BufferWriter* writer)
{
	//writer->WriteSingle(GetNameSpeedX(i), mSpeedX);
	//writer->WriteSingle(GetNameSpeedY(i), mSpeedY);
	//writer->WriteInt32(GetNameDepth(i), mDepth);
}
void LayerData_ReadIni(LayerData* layer, int32_t i, BufferReader* reader)
{
	layer->mSpeedX = BufferReader_ReadFloat(reader);
	layer->mSpeedY = BufferReader_ReadFloat(reader);
	layer->mDepth = BufferReader_ReadI32(reader);
}