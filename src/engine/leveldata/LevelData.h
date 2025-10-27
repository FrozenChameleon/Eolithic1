/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "Line.h"
#include "Tile.h"
#include "MetaMap.h"
#include "LayerData.h"
#include "LevelCameraData.h"
#include "../math/Rectangle.h"
#include "../render/DrawRectangle.h"
#include "../utils/MString.h"
#include "../utils/Macros.h"

enum
{
	LEVEL_DATA_CURRENT_HEADER_VERSION = 0,
	LEVEL_DATA_CURRENT_DATA_VERSION = 8,
	LEVEL_DATA_STRING_DATA_LENGTH = 20,
	LEVEL_DATA_LAYER_DATA_LENGTH = 10
};

typedef struct LevelData
{
	Rectangle _mGridSize;
	Tile* _mDynamicSaveTiles;
	int* _mDynamicSaveTileMap;
	bool _mIsMetaMap;
	MetaMap _mMetaMap;
	DrawRectangle* _mDynamicManyRectangles;
	MString* mLevelName;
	MString* mTilesetName;
	MString* mStringData[LEVEL_DATA_STRING_DATA_LENGTH];
	LayerData mLayerData[LEVEL_DATA_LAYER_DATA_LENGTH];
	Tile** mDynamicTileData;
	LevelCameraData mDynamicCameraData;
	Line* mDynamicLines;
} LevelData;

LevelData* LevelData_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void LevelData_Dispose(LevelData* ld);