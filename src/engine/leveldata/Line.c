/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Line.h"

#include "../math/Vectors.h"
#include "../math/PointRectangle.h"
#include "../math/Points.h"
#include "../render/DrawTool.h"
#include "../render/Color.h"
#include "../globals/Align.h"
#include "../utils/Utils.h"
#include "../math/Math.h"
#include "../../GlobalDefs.h"
#include "../io/BufferReader.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE
#define HALF_TILE_SIZE GLOBAL_DEF_HALF_TILE_SIZE

enum
{
	LINE_DELAY = 16,
	LINE_THICKNESS = 4
};

Point Line_GetMiddle(Point begin, Point end)
{
	Point diff = Point_Sub(end, begin);
	return Point_Create(begin.X + (diff.X / 2), begin.Y + (diff.Y / 2));
}
void Line_DrawLineCamera(Line* line, SpriteBatch* spriteBatch, const char* font, Color color, int cameraWidth, int cameraHeight)
{
	Point beginPoint = Line_GetRealBegin(line);
	Point endPoint = Line_GetRealEnd(line);

	int halfCameraWidth = cameraWidth / 2;
	int halfCameraHeight = cameraHeight / 2;

	Point upperLeft = Point_Create(beginPoint.X - halfCameraWidth, beginPoint.Y - halfCameraHeight);
	Point upperRight = Point_Create(endPoint.X + halfCameraWidth, beginPoint.Y - halfCameraHeight);
	Point lowerRight = Point_Create(endPoint.X + halfCameraWidth, endPoint.Y + halfCameraHeight);
	Point lowerLeft = Point_Create(beginPoint.X - halfCameraWidth, endPoint.Y + halfCameraHeight);

	int depth = 200;
	int lineDelay = 4;
	int lineThickness = 4;
	DrawTool_DrawLine(spriteBatch, color, depth, lineDelay, 0, lineThickness, upperLeft, upperRight);
	DrawTool_DrawLine(spriteBatch, color, depth, lineDelay, 0, lineThickness, upperRight, lowerRight);
	DrawTool_DrawLine(spriteBatch, color, depth, lineDelay, 0, lineThickness, lowerRight, lowerLeft);
	DrawTool_DrawLine(spriteBatch, color, depth, lineDelay, 0, lineThickness, lowerLeft, upperLeft);
}
void Line_DrawLine(Line* line, SpriteBatch* spriteBatch, const char* font, Color color, int lineNumber, int offset)
{
	//TODO C99
	/*
	Point beginPoint = Line_GetRealBegin(line);
	Point endPoint = Line_GetRealEnd(line);
	Line_DrawLineText(line, spriteBatch, font, lineNumber, Vectors_ToVector2(beginPoint));
	DrawTool_DrawRectangle2(spriteBatch, COLOR_COMETSTRIKER_RED, 100, Rectangle_Create(beginPoint.X, beginPoint.Y, HALF_TILE_SIZE, HALF_TILE_SIZE), 0, true);
	int lineDelay = 16;
	int lineThickness = 4;
	DrawTool_DrawLine(spriteBatch, color, 99, lineDelay, offset, lineThickness, beginPoint, endPoint);
	DrawTool_DrawRectangle2(spriteBatch, COLOR_COMETSTRIKER_BLUE, 100, Rectangle_Create(endPoint.X, endPoint.Y, HALF_TILE_SIZE, HALF_TILE_SIZE), 0, true);
	*/
}
void Line_DrawLineText(Line* line, SpriteBatch* spriteBatch, const char* font, int lineNumber, Vector2 pos)
{
	int align = ALIGN_CENTER;
	Vector2 textPos = Vector2_Create(pos.X, pos.Y - HALF_TILE_SIZE);
	int depth = 100;
	Color textColor = COLOR_RED;
	//TODO C99
	/*
	spriteBatch->DrawString(font, OeUtils_ToString(lineNumber), textColor, depth, textPos, align, align);
	if (line->mEnterDownOnly)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Enter Down Only", textColor, depth, textPos, align, align);
	}
	if (line->mEnterLeftOnly)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Enter Left Only", textColor, depth, textPos, align, align);
	}
	if (line->mEnterUpOnly)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Enter Up Only", textColor, depth, textPos, align, align);
	}
	if (line->mEnterRightOnly)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Enter Right Only", textColor, depth, textPos, align, align);
	}
	if (line->mOneWayUp)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "One Way Up", textColor, depth, textPos, align, align);
	}
	if (line->mOneWayRight)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "One Way Right", textColor, depth, textPos, align, align);
	}
	if (line->mOneWayDown)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "One Way Down", textColor, depth, textPos, align, align);
	}
	if (line->mOneWayLeft)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "One Way Left", textColor, depth, textPos, align, align);
	}
	if (line->mIsGap)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Is Gap", textColor, depth, textPos, align, align);
	}
	if (line->mIsFirstLine)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Is First Line", textColor, depth, textPos, align, align);
	}
	if (line->mIsLastLine)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Is Last Line", textColor, depth, textPos, align, align);
	}
	if (line->mOverrideSpeedFromPlayer != 0)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Override Speed From Player: " + std_to_string(line->mOverrideSpeedFromPlayer), textColor, depth, textPos, align, align);
	}
	if (line->mOverrideSpeedFromMinecart != 0)
	{
		textPos.Y -= HALF_TILE_SIZE;
		spriteBatch->DrawString(font, "Override Speed From Minecart: " + std_to_string(line->mOverrideSpeedFromMinecart), textColor, depth, textPos, align, align);
	}*/
}
double Line_GetDistance(Line* line)
{
	return Math_GetDistanceEuclideanPoint(line->mBegin, line->mEnd);
}
bool Line_DoLinesConnect(Line* line1, Line* line2)
{
	if (!Point_EqualTo(Line_GetJunction(line1, line2), Points_NegativeOne))
	{
		return true;
	}
	else
	{
		return false;
	}
}
Point Line_GetJunction(Line* line1, Line* line2)
{
	if (Point_EqualTo(line1->mBegin, line2->mBegin))
	{
		return line1->mBegin;
	}
	else if (Point_EqualTo(line1->mBegin, line2->mEnd))
	{
		return line1->mBegin;
	}
	else if (Point_EqualTo(line1->mEnd, line2->mBegin))
	{
		return line1->mEnd;
	}
	else if (Point_EqualTo(line1->mEnd, line2->mEnd))
	{
		return line1->mEnd;
	}
	return Points_NegativeOne;
}
void Line_CorrectPoints(Line* line)
{
	if (!Line_IsVertical(line))
	{
		if (line->mBegin.X > line->mEnd.X)
		{
			Point temp = line->mBegin;
			line->mBegin = line->mEnd;
			line->mEnd = temp;
		}
	}
	else
	{
		if (line->mBegin.Y > line->mEnd.Y)
		{
			Point temp = line->mBegin;
			line->mBegin = line->mEnd;
			line->mEnd = temp;
		}
	}
}
bool Line_IsVertical(Line* line)
{
	return Math_GetDistanceInt(line->mBegin.X, line->mEnd.X) < Math_GetDistanceInt(line->mBegin.Y, line->mEnd.Y);
}
int Line_GetReal(int point)
{
	return (point * TILE_SIZE) + HALF_TILE_SIZE;
}
Point Line_GetRealPoint(Point point)
{
	Point tileSize = Points_TileSize();
	Point halfTileSize = Points_HalfTileSize();
	Point returnPoint = { 0 };
	returnPoint.X = (point.X * tileSize.X) + halfTileSize.X;
	returnPoint.Y = (point.Y * tileSize.Y) + halfTileSize.Y;
	return returnPoint;
}
Point Line_GetRealBegin(Line* line)
{
	return Line_GetRealPoint(line->mBegin);
}
Point Line_GetRealEnd(Line* line)
{
	return Line_GetRealPoint(line->mEnd);
}
/*void Line_Write(Line* line, std_shared_ptr<OeIniWriter> writer)
{
	OePoints_Write(line->mBegin, writer);
	OePoints_Write(line->mEnd, writer);
	writer->WriteBoolean(line->mEnterDownOnly);
	writer->WriteBoolean(line->mEnterLeftOnly);
	writer->WriteBoolean(line->mEnterUpOnly);
	writer->WriteBoolean(line->mEnterRightOnly);
	writer->WriteBoolean(line->mIsGap);
	writer->WriteBoolean(line->mIsFirstLine);
	writer->WriteBoolean(line->mIsLastLine);
	writer->WriteBoolean(line->mOneWayUp);
	writer->WriteBoolean(line->mOneWayRight);
	writer->WriteBoolean(line->mOneWayDown);
	writer->WriteBoolean(line->mOneWayLeft);
	writer->WriteInt32(line->mOverrideSpeedFromPlayer);
	writer->WriteInt32(line->mOverrideSpeedFromMinecart);
}*/
void Line_Read(int version, Line* line, BufferReader* reader)
{
	Points_Read(&line->mBegin, reader);
	Points_Read(&line->mEnd, reader);
	line->mEnterDownOnly = BufferReader_ReadBoolean(reader);
	line->mEnterLeftOnly = BufferReader_ReadBoolean(reader);
	line->mEnterUpOnly = BufferReader_ReadBoolean(reader);
	line->mEnterRightOnly = BufferReader_ReadBoolean(reader);
	line->mIsGap = BufferReader_ReadBoolean(reader);
	if (version >= 6)
	{
		line->mIsFirstLine = BufferReader_ReadBoolean(reader);
		line->mIsLastLine = BufferReader_ReadBoolean(reader);
	}
	if (version >= 7)
	{
		line->mOneWayUp = BufferReader_ReadBoolean(reader);
		line->mOneWayRight = BufferReader_ReadBoolean(reader);
		line->mOneWayDown = BufferReader_ReadBoolean(reader);
		line->mOneWayLeft = BufferReader_ReadBoolean(reader);
	}
	if (version >= 8)
	{
		line->mOverrideSpeedFromPlayer = BufferReader_ReadI32(reader);
		line->mOverrideSpeedFromMinecart = BufferReader_ReadI32(reader);
	}
}
Rectangle Line_GetTouchBounds(Line* line, int inflation)
{
	Rectangle rect = PointRectangle_GetRectanglePoint(Line_GetRealBegin(line), Line_GetRealEnd(line));
	Rectangle_Inflate(&rect, inflation, inflation);
	return rect;
}
/*const char* Line_ToString()
{
	return "";
	//WILLNOTDO 05152023 return mBegin.ToString() + "/" + mEnd.ToString();
}*/
