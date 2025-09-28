/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

 /* Derived from code by Ethan Lee (Copyright 2009-2024).
  * Released under the Microsoft Public License.
  * See fna.LICENSE for details.

  * Derived from code by the Mono.Xna Team (Copyright 2006).
  * Released under the MIT License.
  * See monoxna.LICENSE for details.
  */

#include "Rectangle.h"

Rectangle Rectangle_Create(int x, int y, int width, int height)
{
	Rectangle rect;
	rect.X = x;
	rect.Y = y;
	rect.Width = width;
	rect.Height = height;
	return rect;
}
void Rectangle_Init(Rectangle* value, int x, int y, int width, int height)
{
	value->X = x;
	value->Y = y;
	value->Width = width;
	value->Height = height;
}
bool Rectangle_EqualTo(const Rectangle* value1, const Rectangle* value2)
{
	return (value1->X == value2->X) && (value1->Y == value2->Y) && (value1->Width == value2->Width) && (value1->Height == value2->Height);
}
bool Rectangle_NotEqual(const Rectangle* value1, const Rectangle* value2)
{
	return !Rectangle_EqualTo(value1, value2);
}
void Rectangle_Inflate(Rectangle* value, int horizontalValue, int verticalValue)
{
	value->X -= horizontalValue;
	value->Y -= verticalValue;
	value->Width += (horizontalValue * 2);
	value->Height += (verticalValue * 2);
}
Point Rectangle_Center(const Rectangle* value)
{
	Point tempPoint;
	tempPoint.X = (value->X + (value->Width / 2));
	tempPoint.Y = (value->Y + (value->Height / 2));
	return tempPoint;
}
int32_t Rectangle_Left(const Rectangle* value)
{
	return value->X;
}
int32_t Rectangle_Right(const Rectangle* value)
{
	return (value->X + value->Width);
}
int32_t Rectangle_Top(const Rectangle* value)
{
	return value->Y;
}
int32_t Rectangle_Bottom(const Rectangle* value)
{
	return (value->Y + value->Height);
}
bool Rectangle_Intersects(const Rectangle* value1, const Rectangle* value2)
{
	return ((Rectangle_Left(value2) < Rectangle_Right(value1)) &&
		(Rectangle_Left(value1) < Rectangle_Right(value2)) &&
		(Rectangle_Top(value2) < Rectangle_Bottom(value1)) &&
		(Rectangle_Top(value1) < Rectangle_Bottom(value2)));
}
bool Rectangle_Contains(const Rectangle* value, int x, int y)
{
	return ((value->X <= x) &&
		(x < (value->X + value->Width)) &&
		(value->Y <= y) &&
		(y < (value->Y + value->Height)));
}
bool Rectangle_ContainsPoint(const Rectangle* value1, Point value2)
{
	return ((value1->X <= value2.X) &&
		(value2.X < (value1->X + value1->Width)) &&
		(value1->Y <= value2.Y) &&
		(value2.Y < (value1->Y + value1->Height)));
}
bool Rectangle_ContainsRectangle(const Rectangle* value1, const Rectangle* value2)
{
	return ((value1->X <= value2->X) &&
		((value2->X + value2->Width) <= (value1->X + value1->Width)) &&
		(value1->Y <= value2->Y) &&
		((value2->Y + value2->Height) <= (value1->Y + value1->Height)));
}
bool Rectangle_IsEmpty(const Rectangle* value)
{
	return ((value->Width == 0) &&
		(value->Height == 0) &&
		(value->X == 0) &&
		(value->Y == 0));
}
Rectangle Rectangle_Empty()
{
	Rectangle tempRect = { 0 };
	return tempRect;
}