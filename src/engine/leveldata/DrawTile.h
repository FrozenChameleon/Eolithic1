#pragma once

#include "../math/Point.h"
#include "../render/Color.h"
#include "../utils/MString.h"

typedef struct Texture Texture;
typedef struct SpriteBatch SpriteBatch;
typedef struct BufferWriter BufferWriter;
typedef struct BufferReader BufferReader;

typedef struct DrawTile
{
	MString* mAnimation;
	Point mPoint;
	bool mFlipX;
	bool mFlipY;
	float mRotation;
	Point mOffsetPoint;
} DrawTile;

void DrawTile_Init(DrawTile* drawTile);
void DrawTile_Write(DrawTile* drawTile, BufferWriter* writer);
void DrawTile_Read(DrawTile* drawTile, int version, BufferReader* reader);
void DrawTile_LoadSheet(DrawTile* drawTile, int x, int y);
void DrawTile_LoadAnimation(DrawTile* drawTile, const char* animation);
void DrawTile_Draw(DrawTile* drawTile, SpriteBatch* spriteBatch, Texture* texture, Color color, int depth, int x, int y);
Point DrawTile_GetCorrectPoint(DrawTile* drawTile);
bool DrawTile_IsZero(DrawTile* drawTile);
bool DrawTile_IsAnimation(DrawTile* drawTile);
bool DrawTile_IsSheet(DrawTile* drawTile);
bool DrawTile_IsEqualTo(DrawTile* drawTile, DrawTile* otherDrawTile);
