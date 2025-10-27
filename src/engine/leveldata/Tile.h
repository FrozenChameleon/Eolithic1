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

void Tile_Init(Tile* tile);
void Tile_Write(Tile* tile, BufferWriter* writer);
void Tile_Read(Tile* tile, int version, BufferReader* reader);
void Tile_DeleteCollision(Tile* tile);
void Tile_DeleteDrawTiles(Tile* tile );
void Tile_DeleteDrawTiles2(Tile* tile, int layer);
void Tile_DeleteThings(Tile* tile);
void Tile_DeleteProps(Tile* tile);
Tile* Tile_GetClone(Tile* tile);
Tile* Tile_GetClone2(Tile* tile, bool limited);
bool Tile_IsEqualTo(Tile* tile, Tile* tile2);
void Tile_DrawThis(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, LevelData* level, bool overrideDepth, Texture* wrapper);
void Tile_DrawCollision(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
Rectangle Tile_GetCollisionRectangle(Tile* tile, int gridX, int gridY);
void Tile_DrawThings(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
void Tile_DrawProps(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth);
void Tile_DrawProps2(Tile* tile, SpriteBatch* spriteBatch, const Camera* camera, int gridX, int gridY, bool overrideDepth, bool drawInfo);