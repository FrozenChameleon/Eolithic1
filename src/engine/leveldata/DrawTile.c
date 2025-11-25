#include "DrawTile.h"

#include "../math/Points.h"
#include "../globals/Globals.h"
#include "../render/SpriteBatch.h"
#include "../io/BufferWriter.h"
#include "../io/BufferReader.h"
#include "../io/File.h"
#include "AnimTile.h"
#include "../resources/Resource.h"
#include "../render/DrawTool.h"
#include "../render/Color.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

//static const std_string TILE_OFFSET_DIRECTORY = OeFile_Combine("data", "gfx", "generated_tilesets");

void DrawTile_Init(DrawTile* drawTile)
{
	MString_Assign(&drawTile->mAnimation, EE_STR_EMPTY);
	drawTile->mPoint = Points_NegativeOne;
	drawTile->mOffsetPoint = Points_NegativeOne;
}
void DrawTile_Write(DrawTile* drawTile, BufferWriter* writer)
{
	/*writer->WriteString(drawTile->mAnimation);
	OePoints_Write(drawTile->mPoint, writer);
	writer->WriteBoolean(drawTile->mFlipX);
	writer->WriteBoolean(drawTile->mFlipY);
	writer->WriteSingle(drawTile->mRotation);*/
}
void DrawTile_Read(DrawTile* drawTile, int version, BufferReader* reader)
{
	drawTile->mAnimation = BufferReader_ReadMString(reader);
	Points_Read(&drawTile->mPoint, reader);
	drawTile->mFlipX = BufferReader_ReadBoolean(reader);
	drawTile->mFlipY = BufferReader_ReadBoolean(reader);
	drawTile->mRotation = BufferReader_ReadFloat(reader);
}
void DrawTile_LoadSheet(DrawTile* drawTile, int x, int y)
{
	drawTile->mPoint.X = x;
	drawTile->mPoint.Y = y;

	MString_Assign(&drawTile->mAnimation, EE_STR_EMPTY);
}
void DrawTile_LoadAnimation(DrawTile* drawTile, const char* animation)
{
	MString_Assign(&drawTile->mAnimation, animation);
	drawTile->mPoint = Points_NegativeOne;
}
void DrawTile_Draw(DrawTile* drawTile, SpriteBatch* spriteBatch, Texture* texture, Color color, int depth, int x, int y)
{
	/*if (drawTile->mAnimation.size() != 0)
	{
		OeAnimTile* tile = OeResourceManagers_AnimTileManager.GetResourceData(drawTile->mAnimation);

		if (tile != nullptr)
		{
			tile->Draw(spriteBatch, color, depth, x, y, drawTile->mRotation, drawTile->mFlipX, drawTile->mFlipY);
		}
		else
		{
			OeDrawTool_DrawRectangle(spriteBatch, OeColors_RED, 100, Rectangle(x, y, TILE_SIZE, TILE_SIZE), 0, false);
		}
	}
	else if (drawTile->mPoint.X != -1 || drawTile->mPoint.Y != -1)
	{
		Point point = GetCorrectPoint(drawTile);

		spriteBatch->Draw(texture, color, depth, nullptr, Vector2(x, y), Rectangle(point.X, point.Y, TILE_SIZE, TILE_SIZE),
			Vector2_One, drawTile->mRotation, drawTile->mFlipX, drawTile->mFlipY, Vector2(TILE_SIZE / 2));
	}*/
}
Point DrawTile_GetCorrectPoint(DrawTile* drawTile)
{
	if (!Globals_IsDebugFileMode() || GLOBALS_DEBUG_ENGINE_FORCE_LOAD_DATS)
	{
		return drawTile->mOffsetPoint;
	}
	else
	{
		return drawTile->mPoint;
	}
}
bool DrawTile_IsZero(DrawTile* drawTile)
{
	if (MString_EqualToString(drawTile->mAnimation, EE_STR_EMPTY) &&
		(drawTile->mPoint.X == -1) &&
		(drawTile->mPoint.Y == -1))
	{
		return true;
	}
	return false;
}
bool DrawTile_IsAnimation(DrawTile* drawTile)
{
	if (MString_EqualToString(drawTile->mAnimation, EE_STR_EMPTY))
	{
		return false;
	}
	return true;
}
bool DrawTile_IsSheet(DrawTile* drawTile)
{
	if ((drawTile->mPoint.X == -1) &&
		(drawTile->mPoint.Y == -1))
	{
		return false;
	}
	return true;
}
bool DrawTile_IsEqualTo(DrawTile* drawTile, DrawTile* otherDrawTile)
{
	return false;
	//TODO C99
	/*if (drawTile->mPoint == otherDrawTile->mPoint && drawTile->mAnimation == otherDrawTile->mAnimation &&
		drawTile->mFlipX == otherDrawTile->mFlipX && drawTile->mFlipY == otherDrawTile->mFlipY && drawTile->mRotation == otherDrawTile->mRotation)
	{
		return true;
	}
	return false;*/
}