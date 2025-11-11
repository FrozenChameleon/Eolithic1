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

typedef struct BufferReader BufferReader;

enum
{
	LEVELDATA_CURRENT_HEADER_VERSION = 0,
	LEVELDATA_CURRENT_DATA_VERSION = 8,
	LEVELDATA_STRING_DATA_LENGTH = 20,
	LEVELDATA_LAYER_DATA_LENGTH = 10
};

typedef struct LevelData
{
	Rectangle _mGridSize;
	Tile** arr_save_tiles;
	int* _mSaveTileMap;
	bool _mIsMetaMap;
	MetaMap _mMetaMap;
	DrawRectangle* _mDynamicManyRectangles;
	MString* mLevelName;
	MString* mTilesetName;
	MString* mStringData[LEVELDATA_STRING_DATA_LENGTH];
	LayerData mLayerData[LEVELDATA_LAYER_DATA_LENGTH];
	Tile** mTileData;
	LevelCameraData* arr_camera_data;
	Line* arr_lines;
} LevelData;

LevelData* LevelData_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void LevelData_Dispose(LevelData* ld);
void LevelData_ReadIni(LevelData* ld, BufferReader* reader);
void LevelData_ReadHeader(LevelData* ld, BufferReader* reader);
void LevelData_ReadData(LevelData* ld, BufferReader* reader);
void LevelData_LoadSetupOffsets(LevelData* ld);
bool LevelData_LoadSetupTileData(LevelData* ld);
int LevelData_GetGridSizeWidth(LevelData* ld);
int LevelData_GetGridSizeHeight(LevelData* ld);
int LevelData_GetGridSizeX(LevelData* ld);
int LevelData_GetGridSizeY(LevelData* ld);
int LevelData_GetRealSizeWidth(LevelData* ld);
int LevelData_GetRealSizeHeight(LevelData* ld);
int LevelData_GetRealSizeX(LevelData* ld);
int LevelData_GetRealSizeY(LevelData* ld);
int LevelData_GetTilePos1D(LevelData* ld, int i, int j);
Tile* LevelData_GetTile(LevelData* ld, int x, int y);
Tile* LevelData_GetTilePoint(LevelData* ld, Point p);
bool LevelData_IsSafe(LevelData* ld, int x, int y);
int32_t* LevelData_CreateCollisionArray(LevelData* ld);
int32_t* LevelData_CreateEmptyCollisionArray(LevelData* ld);
void LevelData_ImprintToCollisionArray(LevelData* ld, int x, int y, int32_t* collisionArray);