/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "DrawTile.h"
#include "PropInstance.h"
#include "ThingInstance.h"

enum
{
	TILE_DRAW_LAYER_LENGTH = 10,
	TILE_OVERRIDE_DEPTH = 190
};

typedef struct Tile
{
	int mCollisionType;
	DrawTile mDrawTiles[TILE_DRAW_LAYER_LENGTH];
	ThingInstance* mDynamicInstances;
	PropInstance* mDynamicProps;
} Tile;

