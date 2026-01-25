/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

#pragma once

#include "stdint.h"

typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;

typedef struct LayerData
{
	float mSpeedX;
	float mSpeedY;
	int32_t mDepth;
} LayerData;

const char* LayerData_GetNameSpeedX(LayerData* layer, int32_t i);
const char* LayerData_GetNameSpeedY(LayerData* layer, int32_t i);
const char* LayerData_GetNameDepth(LayerData* layer, int32_t i);
void LayerData_WriteIni(LayerData* layer, int32_t i, BufferWriter* writer);
void LayerData_ReadIni(LayerData* layer, int32_t i, BufferReader* reader);