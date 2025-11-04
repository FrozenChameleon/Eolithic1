/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;

typedef struct LayerData
{
	float mSpeedX;
	float mSpeedY;
	int mDepth;
} LayerData;


const char* LayerData_GetNameSpeedX(LayerData* layer, int i);
const char* LayerData_GetNameSpeedY(LayerData* layer, int i);
const char* LayerData_GetNameDepth(LayerData* layer, int i);
void LayerData_WriteIni(LayerData* layer, int i, BufferWriter* writer);
void LayerData_ReadIni(LayerData* layer, int i, BufferReader* reader);