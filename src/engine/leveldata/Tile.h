#pragma once

#include "DrawTile.h"
#include "ThingInstance.h"
#include "PropInstance.h"
#include "../components/Camera.h"

typedef struct LevelData LevelData;
typedef struct Texture Texture;
typedef struct BufferReader BufferReader;
typedef struct BufferWriter BufferWriter;
typedef struct SpriteBatch SpriteBatch;

enum
{
	DRAW_LAYER_LENGTH = 10,
	OVERRIDE_DEPTH = 190
};

typedef struct Tile
{
	int mCollisionType;
	DrawTile mDrawTiles[DRAW_LAYER_LENGTH];
	ThingInstance* arr_instances;
	PropInstance* arr_props;
} Tile;

void Tile_Init(Tile* t);
void Tile_Write(Tile* t, BufferWriter* writer);
void Tile_Read(Tile* t, int version, BufferReader* reader);
void Tile_DeleteCollision(Tile* t);
void Tile_DeleteDrawTiles(Tile* t);
void Tile_DeleteDrawTiles2(Tile* t, int layer);
void Tile_DeleteThings(Tile* t);
void Tile_DeleteProps(Tile* t);
Tile* Tile_GetClone(Tile* t);
Tile* Tile_GetClone2(Tile* t, bool limited);
bool Tile_IsEqualTo(Tile* t, Tile* tile2);
void Tile_DrawThis(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, LevelData* level, bool overrideDepth, Texture* wrapper);
void Tile_DrawCollision(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
Rectangle Tile_GetCollisionRectangle(Tile* t, int gridX, int gridY);
void Tile_DrawThings(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
void Tile_DrawProps(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
void Tile_DrawProps2(Tile* t, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth, bool drawInfo);