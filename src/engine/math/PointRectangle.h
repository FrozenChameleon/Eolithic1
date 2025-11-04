/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "Point.h"
#include "Rectangle.h"

typedef struct BufferReader BufferReader;

typedef struct PointRectangle
{
	Point mPointOne;
	Point mPointTwo;
} PointRectangle;

bool PointRectangle_IsEmpty(PointRectangle* prect);
void PointRectangle_CorrectPoints(PointRectangle* prect);
// void PointRectangle_Write(OePointRectangle* prect, std::shared_ptr<OeIniWriter> writer);
void PointRectangle_Read(PointRectangle* prect, BufferReader* reader);
Rectangle PointRectangle_GetRectangle(PointRectangle* prect);
Rectangle PointRectangle_GetRectanglePoint(Point pointOne, Point pointTwo);
void PointRectangle_Add(PointRectangle* prect, int amountX, int amountY);
// void PointRectangle_Draw(OePointRectangle* prect, OeSpriteBatch* spriteBatch, Color rectangleColor, bool isHollow);
// void PointRectangle_Draw(OePointRectangle* prect, OeSpriteBatch* spriteBatch, Color rectangleColor, Color pointColor1, Color pointColor2, bool isHollow);