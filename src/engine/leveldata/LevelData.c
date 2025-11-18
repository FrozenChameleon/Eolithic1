/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "LevelData.h"
#include "../utils/Utils.h"
#include "../io/BufferReader.h"
#include "../globals/Globals.h"
#include "../math/Points.h"
#include "../../third_party/stb_ds.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

LevelData* LevelData_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	LevelData* levelData = Utils_calloc(1, sizeof(LevelData));
	LevelData_ReadIni(levelData, br);
	return levelData;
}
void LevelData_Dispose(LevelData* ld)
{
	Utils_free(ld);
}
void LevelData_ReadIni(LevelData* ld, BufferReader* reader)
{
	LevelData_ReadHeader(ld, reader);

	if (Globals_IsDebugFileMode())
	{
		//WILLNOTDO 05152023
		
		//if (mStringData.Length < STRING_DATA_LENGTH) //if debug then correct custom data if wrong size...
		//{
		//	OeLogger::LogInformation("Correcting custom data amount...");

		//	string[] newCustom = new string[CUSTOM_DATA_AMOUNT];
		//	for (int i = 0; i < newCustom.Length; i++)
		//	{
		//		newCustom[i] = OeUtils::NOT_SET;
		//	}
		//	for (int i = 0; i < mStringData.Length; i++)
		//	{
		//		newCustom[i] = mStringData[i];
		//	}

		//	mStringData = newCustom;
		//}
	}

	if (MString_EqualToString(ld->mLevelName, ""))
	{
		MString_Assign(&ld->mLevelName, EE_STR_NOT_SET);
	}

	//TODO C99
	/*if (ld->_mIsMetaMap)
	{
		SetupAsMetaMap();
		_mMetaMap.Read(reader);
		_mMetaMap.TestAndRemoveInvalidChunks();
		if (OeGlobals::IsDebugFileMode())
		{
			_mMetaMap.DebugAlignLevelIni();
		}
		mTileData = _mMetaMap.CreateTileData();
		mCameraData.clear();
		_mMetaMap.HandleCameraStuff(mCameraData);
		return;
	}*/

	LevelData_ReadData(ld, reader);
	LevelData_LoadSetupOffsets(ld);
	LevelData_LoadSetupTileData(ld);
}
void LevelData_ReadHeader(LevelData* ld, BufferReader* reader)
{
	int version = BufferReader_ReadI32(reader); // <-

	ld->_mIsMetaMap = BufferReader_ReadBoolean(reader); // <- Add these two to CometStriker/Mute Crimson+ for parity

	ld->mLevelName = BufferReader_ReadMString(reader);
	ld->mTilesetName = BufferReader_ReadMString(reader);

	int customDataSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < customDataSize; i++)
	{
		ld->mStringData[i] = BufferReader_ReadMString(reader);
	}

	BufferReader_ReadFloat(reader); //Unused - Player Position X
	BufferReader_ReadFloat(reader); //Unused - Player Position Y

	int layerDataSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < layerDataSize; i++)
	{
		LayerData_ReadIni(&ld->mLayerData[i], i, reader);
	}
}
void LevelData_ReadData(LevelData* ld, BufferReader* reader)
{
	int version = BufferReader_ReadI32(reader);

	if (version >= 3)
	{
		int temp = BufferReader_ReadI32(reader); //Unused - Thing Instance ID Counter
	}

	int saveTileSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < saveTileSize; i++)
	{
		Tile* tile = Utils_calloc(1, sizeof(Tile));
		Tile_Read(tile, version, reader);
		arrput(ld->arr_save_tiles, tile);
	}

	int gridWidth = BufferReader_ReadI32(reader);
	int gridHeight = BufferReader_ReadI32(reader);

	ld->_mGridSize.Width = gridWidth;
	ld->_mGridSize.Height = gridHeight;
	ld->_mSaveTileMap = BufferReader_ReadIntArray2D(reader, gridWidth, gridHeight);

	int cameraDataSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < cameraDataSize; i++)
	{
		LevelCameraData cameraData = { 0 };
		LevelCameraData_Read(&cameraData, version, reader);
		arrput(ld->arr_camera_data, cameraData);
	}

	if (version >= 5)
	{
		int lineInfoSize = BufferReader_ReadI32(reader);
		for (int i = 0; i < lineInfoSize; i++)
		{
			Line line = { 0 };
			Line_Read(version, &line, reader);
			arrput(ld->arr_lines, line);
		}
	}
}
void LevelData_LoadSetupOffsets(LevelData* ld)
{
	if (Globals_IsDebugFileMode() && !GLOBALS_DEBUG_ENGINE_FORCE_LOAD_DATS)
	{
		return;
	}
	
	for (int i = 0; i < arrlen(ld->arr_save_tiles); i += 1)
	{
		Tile* t = ld->arr_save_tiles[i];
		for (int j = 0; j < LEVELDATA_LAYER_DATA_LENGTH; j += 1)
		{
			//TODO C99 TilesetOffset_LoadOffsetPoint(&t->mDrawTiles[j], ld->mTilesetName->text);
		}
	}
}
bool LevelData_LoadSetupTileData(LevelData* ld)
{
	Tile** tiles = ld->arr_save_tiles;
	int* map = ld->_mSaveTileMap;
	int gridWidth = LevelData_GetGridSizeWidth(ld);
	int gridHeight = LevelData_GetGridSizeHeight(ld);
	int tileDataLen = gridWidth * gridHeight;
	ld->mTileData = Utils_calloc(tileDataLen, sizeof(LevelData*));
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			int gridPos = LevelData_GetTilePos1D(ld, i, j);
			//WILLNOTDO 06262023 DEBUG
			/*
			if (OeGlobals::IsDebugFileMode())
			{
				if (_mIsMetaMap && OeGlobals::DEBUG_IS_META_MAP_EDIT_TILE_MODE_AT_MAP_LOAD || !_mIsMetaMap) //if debug and editing, we use clones of tiles so they can be manipulated...
				{
					 mTileData[gridPos] = tiles[map[gridPos]].GetClone();
				}
				else //otherwise we just use a reference...
				{
					mTileData[gridPos] = &tiles[map[gridPos]];
				}
			}
			else
			{
			*/
			int tileLocInSaveTiles = map[gridPos];
			Tile* tileToSet = tiles[tileLocInSaveTiles];
			ld->mTileData[gridPos] = tileToSet;
			//}
		}
	}

	return true;
}
int LevelData_GetGridSizeWidth(LevelData* ld)
{
	return ld->_mGridSize.Width;
}
int LevelData_GetGridSizeHeight(LevelData* ld)
{
	return ld->_mGridSize.Height;
}
int LevelData_GetGridSizeX(LevelData* ld)
{
	return ld->_mGridSize.Width;
}
int LevelData_GetGridSizeY(LevelData* ld)
{
	return ld->_mGridSize.Height;
}
int LevelData_GetRealSizeWidth(LevelData* ld)
{
	return ld->_mGridSize.Width * TILE_SIZE;
}
int LevelData_GetRealSizeHeight(LevelData* ld)
{
	return ld->_mGridSize.Height * TILE_SIZE;
}
int LevelData_GetRealSizeX(LevelData* ld)
{
	return ld->_mGridSize.Width * TILE_SIZE;
}
int LevelData_GetRealSizeY(LevelData* ld)
{
	return ld->_mGridSize.Height * TILE_SIZE;
}
int LevelData_GetTilePos1D(LevelData* ld, int i, int j)
{
	return i + (j * ld->_mGridSize.Width);
}
Tile* LevelData_GetTile(LevelData* ld, int x, int y)
{
	if (!LevelData_IsSafe(ld, x, y))
	{
		return NULL;
	}

	return ld->mTileData[LevelData_GetTilePos1D(ld, x, y)];
}
Tile* LevelData_GetTilePoint(LevelData* ld, Point p)
{
	return LevelData_GetTile(ld, p.X, p.Y);
}
bool LevelData_IsSafe(LevelData* ld, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= ld->_mGridSize.Width) || (y >= ld->_mGridSize.Height))
	{
		return false;
	}
	return true;
}
int32_t* LevelData_CreateCollisionArray(LevelData* ld)
{
	int32_t* collisionArray = LevelData_CreateEmptyCollisionArray(ld);
	LevelData_ImprintToCollisionArray(ld, 0, 0, collisionArray);
	return collisionArray;
}
int32_t* LevelData_CreateEmptyCollisionArray(LevelData* ld)
{
	return Utils_calloc(ld->_mGridSize.Width * ld->_mGridSize.Height, sizeof(int32_t));
}
void LevelData_ImprintToCollisionArray(LevelData* ld, int x, int y, int32_t* collisionArray)
{
	int width = ld->_mGridSize.Width;
	int height = ld->_mGridSize.Height;
	for (int i = 0; i < width; i += 1)
	{
		for (int j = 0; j < height; j += 1)
		{
			collisionArray[LevelData_GetTilePos1D(ld, x + i, y + j)] = ld->mTileData[LevelData_GetTilePos1D(ld, i, j)]->mCollisionType;
		}
	}
}
Rectangle LevelData_GetLevelBoundsRectangle(LevelData* ld)
{
	return Rectangle_Create(0, 0, LevelData_GetRealSizeX(ld), LevelData_GetRealSizeY(ld));
}
