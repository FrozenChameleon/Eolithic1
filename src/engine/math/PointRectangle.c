/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "PointRectangle.h"

#include "../math/Math.h"
#include "../math/Points.h"
#include "../math/RectangleTools.h"

bool PointRectangle_IsEmpty(PointRectangle* prect)
{
	if (Point_EqualTo(prect->mPointOne, Point_Zero) && Point_EqualTo(prect->mPointTwo, Point_Zero))
	{
		return true;
	}
	return false;
}
void PointRectangle_CorrectPoints(PointRectangle* prect)
{
	if (prect->mPointTwo.X < prect->mPointOne.X)
	{
		int tempX = prect->mPointOne.X;
		prect->mPointOne.X = prect->mPointTwo.X;
		prect->mPointTwo.X = tempX;
	}
	if (prect->mPointTwo.Y < prect->mPointOne.Y)
	{
		int tempY = prect->mPointOne.Y;
		prect->mPointOne.Y = prect->mPointTwo.Y;
		prect->mPointTwo.Y = tempY;
	}
}
// void PointRectangle_Write(OePointRectangle* prect, std::shared_ptr<OeIniWriter> writer);
void PointRectangle_Read(PointRectangle* prect, BufferReader* reader)
{
	Points_Read(&prect->mPointOne, reader);
	Points_Read(&prect->mPointTwo, reader);
	Rectangle dummy = { 0 }; //To maintain compatibility
	RectangleTools_Read(&dummy, reader);
}
Rectangle PointRectangle_GetRectangle(PointRectangle* prect)
{
	return PointRectangle_GetRectanglePoint(prect->mPointOne, prect->mPointTwo);
}
Rectangle PointRectangle_GetRectanglePoint(Point pointOne, Point pointTwo)
{
	int diffX = pointTwo.X - pointOne.X;
	int diffY = pointTwo.Y - pointOne.Y;

	int x = diffX < 0 ? pointTwo.X : pointOne.X;
	int y = diffY < 0 ? pointTwo.Y : pointOne.Y;

	int width = Math_abs(diffX);
	int height = Math_abs(diffY);

	Rectangle tempRect = { x, y, width, height };
	return tempRect;
}
void PointRectangle_Add(PointRectangle* prect, int32_t amountX, int32_t amountY)
{
	Point temp = { amountX, amountY };
	Point_AddAssign(&prect->mPointOne, temp);
	Point_AddAssign(&prect->mPointTwo, temp);
}
// void PointRectangle_Draw(OePointRectangle* prect, OeSpriteBatch* spriteBatch, Color rectangleColor, bool isHollow);
// void PointRectangle_Draw(OePointRectangle* prect, OeSpriteBatch* spriteBatch, Color rectangleColor, Color pointColor1, Color pointColor2, bool isHollow);