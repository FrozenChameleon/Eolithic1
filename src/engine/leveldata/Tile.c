#include "Tile.h"

#include "../components/Camera.h"
#include "../utils/Cvars.h"
#include "../render/DrawTool.h"
#include "../core/GameHelper.h"
#include "../io/BufferReader.h"
#include "../io/BufferWriter.h"
#include "../utils/Utils.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE
#define HALF_TILE_SIZE GLOBAL_DEF_HALF_TILE_SIZE

void Tile_Init(Tile* tile)
{
	/*tile->mCollisionType = 0;
	tile->mInstances = {};
	tile->mProps = {};
	for (int i = 0; i < DRAW_LAYER_LENGTH; i++)
	{
		DrawTile_Init(&tile->mDrawTiles[i]);
	}*/
}

void Tile_Write(Tile* tile, BufferWriter* writer)
{
	/*
	writer->WriteInt32(1); //
	writer->WriteInt32(1); //Unused - Multi Array Collision
	writer->WriteInt32(mCollisionType);

	writer->WriteInt32(DRAW_LAYER_LENGTH);
	for (int i = 0; i < DRAW_LAYER_LENGTH; i++)
	{
		OeDrawTile_Write(&mDrawTiles[i], writer);
	}

	writer->WriteInt32(mInstances.size());
	for (int i = 0; i < mInstances.size(); i++)
	{
		mInstances[i].Write(writer);
	}

	writer->WriteInt32(mProps.size());
	for (int i = 0; i < mProps.size(); i++)
	{
		OePropInstance_Write(&mProps[i], writer);
	}
	*/
}
void Tile_Read(Tile* tile, int version, BufferReader* reader)
{
	BufferReader_ReadI32(reader); //
	BufferReader_ReadI32(reader); //Unused - Multi Array Collision
	tile->mCollisionType = BufferReader_ReadI32(reader);

	int arrayDrawTilesSize = BufferReader_ReadI32(reader);
	for (int i = 0; i < arrayDrawTilesSize; i += 1)
	{
		DrawTile_Read(&tile->mDrawTiles[i], version, reader);
	}

	int arrayThingDataSize = BufferReader_ReadI32(reader);
	/*//TODO C99
	for (int i = 0; i < arrayThingDataSize; i++)
	{
		ThingInstance instance = OeThingInstance();
		instance.Read(version, reader);
		mInstances.push_back(instance);
	}

	int arrayPropDataSize = reader->BufferReader_ReadInt32();
	for (int i = 0; i < arrayPropDataSize; i++)
	{
		PropInstance instance;
		PropInstance_Init(&instance);
		PropInstance_Read(&instance, version, reader);
		mProps.push_back(instance);
	}*/
}
void Tile_DeleteCollision(Tile* tile)
{
	tile->mCollisionType = 0;
}
void Tile_DeleteDrawTiles(Tile* tile)
{
	for (int i = 0; i < DRAW_LAYER_LENGTH; i++)
	{
		Tile_DeleteDrawTiles2(tile, i);
	}
}
void Tile_DeleteDrawTiles2(Tile* tile, int layer)
{
	//TODO C99 DrawTile_Init(&mDrawTiles[layer]);
}
void Tile_DeleteThings(Tile* tile)
{
	//TODO C99mInstances.clear();
}
void Tile_DeleteProps(Tile* tile)
{
	//TODO C99mProps.clear();
}
Tile* Tile_GetClone(Tile* tile)
{
	return NULL;
	//TODO C99 return GetClone(false);
}
Tile* Tile_GetClone2(Tile* tile, bool limited)
{
	return NULL;
	/*Tile newTile = Tile();

	bool copyCollision = false;
	bool copyTiles = false;
	bool copyLayerOnly = false;
	int currentLayer = -1;
	bool copyProps = false;
	bool copyThings = false;

#if EDITOR
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
		for (int i = 0; i < DRAW_LAYER_LENGTH; i++)
		{
			if (!limited || !copyLayerOnly || i == currentLayer)
			{
				newTile.mDrawTiles[i] = mDrawTiles[i];
			}
		}
	}

	if (!limited || copyProps)
	{
		for (int i = 0; i < mProps.size(); i++)
		{
			newTile.mProps.push_back(mProps[i]);
		}
	}

	if (!limited || copyThings)
	{
		for (int i = 0; i < mInstances.size(); i++)
		{
			newTile.mInstances.push_back(mInstances[i]); //WILLNOTDO 05152023 CHECK THIS, ORIGINALLY IT USED "GETCLONE".. SHOULD NOT NEED IT NOW
		}
	}

	return newTile;*/
}
bool Tile_IsEqualTo(Tile* tile, Tile* tile2)
{
	return false;
	//WILLNOTDO 05152023
	//if (mCollisionType != tile->mCollisionType)
	//{
	//	return false;
	//}

	//for (int i = 0; i < LAYER_AMOUNT; i++)
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
void Tile_DrawThis(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, LevelData* level, bool overrideDepth, Texture* wrapper)
{
	//WILLNOTDO 05152023
}
void Tile_DrawCollision(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth)
{
	//TODO C99
	/*if (tile->mCollisionType == 0)
	{
		return;
	}

	int depth = 100;
	if (overrideDepth)
	{
		depth = OVERRIDE_DEPTH;
	}

	Rectangle rect = Tile_GetCollisionRectangle(gridX, gridY);
	Color color = Utils_GetCollisionColor(mCollisionType);
	DrawTool_DrawRectangle(spriteBatch, color, depth, rect, 0, false);*/
}
Rectangle Tile_GetCollisionRectangle(Tile* tile, int gridX, int gridY)
{
	int rectX = gridX * TILE_SIZE;
	int rectY = gridY * TILE_SIZE;
	int rectWidth = TILE_SIZE;
	int rectHeight = TILE_SIZE;
	if ((tile->mCollisionType == GAMEHELPER_PLATFORM_UP) || (tile->mCollisionType == GAMEHELPER_PLATFORM_DOWN))
	{
		rectHeight /= 2;
		if (tile->mCollisionType == GAMEHELPER_PLATFORM_DOWN)
		{
			rectY += HALF_TILE_SIZE;
		}
	}
	if ((tile->mCollisionType == GAMEHELPER_PLATFORM_LEFT) || (tile->mCollisionType == GAMEHELPER_PLATFORM_RIGHT))
	{
		rectWidth /= 2;
		if (tile->mCollisionType == GAMEHELPER_PLATFORM_RIGHT)
		{
			rectX += HALF_TILE_SIZE;
		}
	}
	return Rectangle_Create(rectX, rectY, rectWidth, rectHeight);
}
void Tile_DrawThings(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth)
{
	/*if (mInstances.size() == 0)
	{
		return;
	}

	Color thingColor = Color(255, 0, 0, 127);
	for (int k = 0; k < mInstances.size(); k++)
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
void Tile_DrawProps(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth)
{
	/*DrawProps(spriteBatch, camera, gridX, gridY, overrideDepth, false);*/
}
void Tile_DrawProps2(Tile* tile, SpriteBatch* spriteBatch, const  Camera* camera, int gridX, int gridY, bool overrideDepth, bool drawInfo)
{
	/*if (mProps.size() == 0)
	{
		return;
	}

	Rectangle cameraRect = camera->GetRectangle(camera, 1.0f);
	Vector2 position = Vector2(gridX * TILE_SIZE, gridY * TILE_SIZE);
	for (int k = 0; k < mProps.size(); k++)
	{
		OePropInstance* propInstance = &mProps[k];

		Rectangle cameraCheck = OePropInstance_GetRectangle(propInstance, position);
		//To compensate for possible rotation around its upper left, which is how it is done for some reason.
		if (cameraCheck.Width < cameraCheck.Height)
		{
			cameraCheck.Width = cameraCheck.Height;
		}
		else
		{
			cameraCheck.Height = cameraCheck.Width;
		}
		cameraCheck.Inflate(cameraCheck.Width + HALF_TILE_SIZE, cameraCheck.Height + HALF_TILE_SIZE);
		//
		if (!cameraRect.Intersects(cameraCheck))
		{
			continue;
		}

		if (!overrideDepth)
		{
			OePropInstance_Draw(propInstance, spriteBatch, position, drawInfo);
		}
		else
		{
			OePropInstance_Draw(propInstance, spriteBatch, OVERRIDE_DEPTH, position, drawInfo);
		}*/

		//Debug stuff to draw the camera check rectangle
		//Color color = Color_Red;
		//color.A = 122;
		//OeDrawTool_DrawRectangle(spriteBatch, color, 100, cameraCheck, 0, false);
}