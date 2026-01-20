#include "Tile.h"

#include "../utils/Macros.h"
#include "../components/Camera.h"
#include "../utils/Cvars.h"
#include "../render/DrawTool.h"
#include "../core/GameHelper.h"
#include "../io/BufferReader.h"
#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE
#define HALF_TILE_SIZE GLOBAL_DEF_HALF_TILE_SIZE

void Tile_Init(Tile* t)
{
	/*tile->mCollisionType = 0;
	tile->mInstances = {};
	tile->mProps = {};
	for (int32_t i = 0; i < DRAW_LAYER_LENGTH; i += 1)
	{
		DrawTile_Init(&tile->mDrawTiles[i]);
	}*/
}
void Tile_Write(Tile* t, BufferWriter* writer)
{
	/*
	writer->WriteInt32(1); //
	writer->WriteInt32(1); //Unused - Multi Array Collision
	writer->WriteInt32(mCollisionType);

	writer->WriteInt32(DRAW_LAYER_LENGTH);
	for (int32_t i = 0; i < DRAW_LAYER_LENGTH; i += 1)
	{
		OeDrawTile_Write(&mDrawTiles[i], writer);
	}

	writer->WriteInt32(mInstances.size());
	for (int32_t i = 0; i < mInstances.size(); i += 1)
	{
		mInstances[i].Write(writer);
	}

	writer->WriteInt32(mProps.size());
	for (int32_t i = 0; i < mProps.size(); i += 1)
	{
		OePropInstance_Write(&mProps[i], writer);
	}
	*/
}
void Tile_Read(Tile* t, int32_t version, BufferReader* reader)
{
	BufferReader_ReadI32(reader); //
	BufferReader_ReadI32(reader); //Unused - Multi Array Collision
	t->mCollisionType = BufferReader_ReadI32(reader);

	int32_t arrayDrawTilesSize = BufferReader_ReadI32(reader);
	for (int32_t i = 0; i < arrayDrawTilesSize; i += 1)
	{
		DrawTile_Read(&t->mDrawTiles[i], version, reader);
	}

	int32_t arrayThingDataSize = BufferReader_ReadI32(reader);
	for (int32_t i = 0; i < arrayThingDataSize; i += 1)
	{
		ThingInstance instance = { 0 };
		ThingInstance_Read(&instance, version, reader);
		arrput(t->arr_instances, instance);
	}

	int32_t arrayPropDataSize = BufferReader_ReadI32(reader);
	for (int32_t i = 0; i < arrayPropDataSize; i += 1)
	{
		PropInstance instance = { 0 };
		PropInstance_Init(&instance);
		PropInstance_Read(&instance, version, reader);
		arrput(t->arr_props, instance);
	}
}
void Tile_DeleteCollision(Tile* t)
{
	t->mCollisionType = 0;
}
void Tile_DeleteDrawTiles(Tile* t)
{
	for (int32_t i = 0; i < DRAW_LAYER_LENGTH; i += 1)
	{
		Tile_DeleteDrawTiles2(t, i);
	}
}
void Tile_DeleteDrawTiles2(Tile* t, int32_t layer)
{
	//TODO C99 DrawTile_Init(&mDrawTiles[layer]);
}
void Tile_DeleteThings(Tile* t)
{
	//TODO C99mInstances.clear();
}
void Tile_DeleteProps(Tile* t)
{
	//TODO C99mProps.clear();
}
Tile* Tile_GetClone(Tile* t)
{
	return NULL;
	//TODO C99 return GetClone(false);
}
Tile* Tile_GetClone2(Tile* t, bool limited)
{
	return NULL;
	/*Tile newTile = Tile();

	bool copyCollision = false;
	bool copyTiles = false;
	bool copyLayerOnly = false;
	int32_t currentLayer = -1;
	bool copyProps = false;
	bool copyThings = false;

#ifdef EDITOR_MODE
	copyCollision = OeCvars_GetAsBool(OeCvars_EDITOR_COPY_COLLISION);
	copyTiles = OeCvars_GetAsBool(OeCvars_EDITOR_COPY_TILES);
	copyLayerOnly = OeCvars_GetAsBool(OeCvars_EDITOR_COPY_LAYER_ONLY);
	currentLayer = OeCvars_GetAsInt(OeCvars_EDITOR_CURRENT_LAYER);
	copyProps = OeCvars_GetAsBool(OeCvars_EDITOR_COPY_PROPS);
	copyThings = OeCvars_GetAsBool(OeCvars_EDITOR_COPY_THINGS);
#endif

	if (!limited || copyCollision)
	{
		newTile.mCollisionType = mCollisionType;
	}

	if (!limited || copyTiles)
	{
		for (int32_t i = 0; i < DRAW_LAYER_LENGTH; i += 1)
		{
			if (!limited || !copyLayerOnly || i == currentLayer)
			{
				newTile.mDrawTiles[i] = mDrawTiles[i];
			}
		}
	}

	if (!limited || copyProps)
	{
		for (int32_t i = 0; i < mProps.size(); i += 1)
		{
			newTile.mProps.push_back(mProps[i]);
		}
	}

	if (!limited || copyThings)
	{
		for (int32_t i = 0; i < mInstances.size(); i += 1)
		{
			newTile.mInstances.push_back(mInstances[i]); //WILLNOTDO 05152023 CHECK THIS, ORIGINALLY IT USED "GETCLONE".. SHOULD NOT NEED IT NOW
		}
	}

	return newTile;*/
}
bool Tile_IsEqualTo(Tile* t, Tile* tile2)
{
	return false;
	//WILLNOTDO 05152023
	//if (mCollisionType != tile->mCollisionType)
	//{
	//	return false;
	//}

	//for (int32_t i = 0; i < LAYER_AMOUNT; i += 1)
	//{
	//	if (!OeDrawTile_IsEqualTo(ref mDrawTiles[i], ref tile.mDrawTiles[i]))
	//	{
	//		return false;
	//	}
	//}

	//if (!OeUtils_IsArrayEqualTo(mProps, tile->mProps))
	//{
	//	return false;
	//}

	//if (!OeUtils.IsArrayEqualTo(mInstances, tile->mInstances))
	//{
	//	return false;
	//}

	//return true;
}
void Tile_DrawThis(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int32_t gridX, int32_t gridY, LevelData* level, bool overrideDepth, Texture* wrapper)
{
	//WILLNOTDO 05152023
}
void Tile_DrawCollision(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int32_t gridX, int32_t gridY, bool overrideDepth)
{
	//TODO C99
	/*if (tile->mCollisionType == 0)
	{
		return;
	}

	int32_t depth = 100;
	if (overrideDepth)
	{
		depth = OVERRIDE_DEPTH;
	}

	Rectangle rect = Tile_GetCollisionRectangle(gridX, gridY);
	Color color = Utils_GetCollisionColor(mCollisionType);
	DrawTool_DrawRectangle(spriteBatch, color, depth, rect, 0, false);*/
}
Rectangle Tile_GetCollisionRectangle(Tile* t, int32_t gridX, int32_t gridY)
{
	int32_t rectX = gridX * TILE_SIZE;
	int32_t rectY = gridY * TILE_SIZE;
	int32_t rectWidth = TILE_SIZE;
	int32_t rectHeight = TILE_SIZE;
	if ((t->mCollisionType == GAMEHELPER_PLATFORM_UP) || (t->mCollisionType == GAMEHELPER_PLATFORM_DOWN))
	{
		rectHeight /= 2;
		if (t->mCollisionType == GAMEHELPER_PLATFORM_DOWN)
		{
			rectY += HALF_TILE_SIZE;
		}
	}
	if ((t->mCollisionType == GAMEHELPER_PLATFORM_LEFT) || (t->mCollisionType == GAMEHELPER_PLATFORM_RIGHT))
	{
		rectWidth /= 2;
		if (t->mCollisionType == GAMEHELPER_PLATFORM_RIGHT)
		{
			rectX += HALF_TILE_SIZE;
		}
	}
	return Rectangle_Create(rectX, rectY, rectWidth, rectHeight);
}
void Tile_DrawThings(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int32_t gridX, int32_t gridY, bool overrideDepth)
{
	/*if (mInstances.size() == 0)
	{
		return;
	}

	Color thingColor = Color(255, 0, 0, 127);
	for (int32_t k = 0; k < mInstances.size(); k++)
	{
		if (!overrideDepth)
		{
			mInstances[k].Draw(spriteBatch, thingColor, Point(gridX * TILE_SIZE, gridY * TILE_SIZE), false);
		}
		else
		{
			mInstances[k].Draw(spriteBatch, thingColor, OVERRIDE_DEPTH, Point(gridX * TILE_SIZE, gridY * TILE_SIZE), false);
		}
	}*/
}
void Tile_DrawProps(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int32_t gridX, int32_t gridY, bool overrideDepth)
{
	Tile_DrawProps2(t, spriteBatch, camera, gridX, gridY, overrideDepth, false);
}
void Tile_DrawProps2(Tile* t, SpriteBatch* spriteBatch, const  Camera* camera, int32_t gridX, int32_t gridY, bool overrideDepth, bool drawInfo)
{
	if (t->arr_props == NULL)
	{
		return;
	}

	int64_t arr_props_len = arrlen(t->arr_props);
	if (arr_props_len == 0)
	{
		return;
	}

	Rectangle cameraRect = Camera_GetRectangle(camera, 1.0f);
	Vector2 position = Vector2_Create((float)(gridX * TILE_SIZE), (float)(gridY * TILE_SIZE));
	for (int32_t i = 0; i < arr_props_len; i += 1)
	{
		PropInstance* propInstance = &t->arr_props[i];

		Rectangle cameraCheck = PropInstance_GetRectangle(propInstance, position);
		//To compensate for possible rotation around its upper left, which is how it is done for some reason.
		if (cameraCheck.Width < cameraCheck.Height)
		{
			cameraCheck.Width = cameraCheck.Height;
		}
		else
		{
			cameraCheck.Height = cameraCheck.Width;
		}
		Rectangle_Inflate(&cameraCheck, cameraCheck.Width + HALF_TILE_SIZE, cameraCheck.Height + HALF_TILE_SIZE);
		//
		if (!Rectangle_Intersects(&cameraRect, &cameraCheck))
		{
			continue;
		}

		if (!overrideDepth)
		{
			PropInstance_Draw2(propInstance, spriteBatch, position, drawInfo);
		}
		else
		{
			PropInstance_Draw4(propInstance, spriteBatch, OVERRIDE_DEPTH, position, drawInfo);
		}

		//Debug stuff to draw the camera check rectangle
		//Color color = Color_Red;
		//color.A = 122;
		//OeDrawTool_DrawRectangle(spriteBatch, color, 100, cameraCheck, 0, false);
	}
}