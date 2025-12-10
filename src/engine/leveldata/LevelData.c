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
#include "../utils/Cvars.h"
#include "../render/SpriteBatch.h"
#include "../resources/TextureManager.h"
#include "../utils/MString.h"
#include "../render/TilesetOffset.h"
#include "../utils/Utils.h"

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
		//	OeLogger_LogInformation("Correcting custom data amount...");

		//	string[] newCustom = new string[CUSTOM_DATA_AMOUNT];
		//	for (int i = 0; i < newCustom.Length; i++)
		//	{
		//		newCustom[i] = OeUtils_NOT_SET;
		//	}
		//	for (int i = 0; i < mStringData.Length; i++)
		//	{
		//		newCustom[i] = mStringData[i];
		//	}

		//	mStringData = newCustom;
		//}
	}

	if (Utils_StringEqualTo(ld->mLevelName, EE_STR_EMPTY))
	{
		Utils_strlcpy(ld->mLevelName, EE_STR_NOT_SET, EE_FILENAME_MAX);
	}

	//TODO C99
	/*if (ld->_mIsMetaMap)
	{
		SetupAsMetaMap();
		_mMetaMap.Read(reader);
		_mMetaMap.TestAndRemoveInvalidChunks();
		if (OeGlobals_IsDebugFileMode())
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

	BufferReader_ReadString(reader, ld->mLevelName, EE_FILENAME_MAX);
	BufferReader_ReadString(reader, ld->mTilesetName, EE_FILENAME_MAX);

	int customDataSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < customDataSize; i++)
	{
		BufferReader_ReadString(reader, ld->mStringData[i], EE_FILENAME_MAX);
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
			TilesetOffset_LoadOffsetPoint(&t->mDrawTiles[j], ld->mTilesetName);
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
			if (OeGlobals_IsDebugFileMode())
			{
				if (_mIsMetaMap && OeGlobals_DEBUG_IS_META_MAP_EDIT_TILE_MODE_AT_MAP_LOAD || !_mIsMetaMap) //if debug and editing, we use clones of tiles so they can be manipulated...
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
int LevelData_GetTilePos1D(LevelData* ld, int32_t i, int32_t j)
{
	return i + (j * ld->_mGridSize.Width);
}
Tile* LevelData_GetTile(LevelData* ld, int32_t x, int32_t y)
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
bool LevelData_IsSafe(LevelData* ld, int32_t x, int32_t y)
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
void LevelData_ImprintToCollisionArray(LevelData* ld, int32_t x, int32_t y, int32_t* collisionArray)
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
bool LevelData_IsTilesetNameSet(LevelData* ld)
{
	if (Utils_StringEqualTo(ld->mTilesetName, EE_STR_NOT_SET))
	{
		return false;
	}
	return true;
}
void LevelData_DrawTiles(LevelData* ld, SpriteBatch* spriteBatch, Camera* camera)
{
	int32_t preferredLayer = -1;
	float mul = 1;

#if EDITOR
	if (!Cvars_GetAsBool(CVARS_EDITOR_SHOW_TILES))
	{
		return;
	}
#endif

	if (!LevelData_IsTilesetNameSet(ld))
	{
		return;
	}

	Texture* texture = LevelData_GetTilesetTexture(ld);
	if (texture == NULL)
	{
		return;
	}
	if (Texture_GetTexture2D(texture) == NULL)
	{
		return;
	}

	int x1 = Camera_GetX1Mul(camera, mul);
	int x2 = Camera_GetX2Mul(camera, ld->_mGridSize.Width, mul);
	int y1 = Camera_GetY1Mul(camera, mul);
	int y2 = Camera_GetY2Mul(camera, ld->_mGridSize.Height, mul);

	for (int i = 0; i < LEVELDATA_LAYER_DATA_LENGTH; i++)
	{
		Color color = COLOR_WHITE;
		int depth = ld->mLayerData[i].mDepth;
		if (preferredLayer != -1)
		{
			if (preferredLayer == i)
			{
				depth = 100;
			}
			else
			{
				color = COLOR_GRAY;
			}
		}

		bool showLayer = true;
#if EDITOR
		//TODO C99 showLayer = Cvars_GetAsBool(Cvars_GetEditorShowLayer(i));
#endif
		if (showLayer)
		{
			SpriteBatch_DrawLayer(spriteBatch, texture, color, ld->mTileData, ld->_mGridSize, depth, i, x1, x2, y1, y2);
		}
	}

#if EDITOR
	//TODO C99 DrawTileInfo(spriteBatch, preferredLayer, x1, x2, y1, y2);
#endif
}
Texture* LevelData_GetTilesetTexture(LevelData* ld)
{
	Resource* resource = TextureManager_GetResource(ld->mTilesetName);
	if ((resource == NULL) || (resource->mData == NULL))
	{
		return NULL;
	}
	return resource->mData;
}
void LevelData_DrawProps(LevelData* ld, SpriteBatch* spriteBatch, Camera* camera)
{
	bool drawInfo = false;

#if EDITOR
	if (!Cvars_GetAsBool(CVARS_EDITOR_SHOW_PROPS))
	{
		return;
	}
#endif

	int dist = Cvars_GetAsInt(CVARS_ENGINE_PROP_DISTANCE);

	int x1 = Camera_GetX1Mul(camera, (float)dist);
	int x2 = Camera_GetX2Mul(camera, LevelData_GetGridSizeWidth(ld), (float)dist);
	int y1 = Camera_GetY1Mul(camera, (float)dist);
	int y2 = Camera_GetY2Mul(camera, LevelData_GetGridSizeHeight(ld), (float)dist);

	for (int i = x1; i < x2; i += 1)
	{
		for (int j = y1; j < y2; j += 1)
		{
			Tile* t = ld->mTileData[LevelData_GetTilePos1D(ld, i, j)];
			Tile_DrawProps2(t, spriteBatch, camera, i, j, false, drawInfo);
		}
	}
}
