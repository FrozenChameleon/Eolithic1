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

#include "Point.h"

Point Point_Create(int x, int y)
{
	Point point;
	point.X = x;
	point.Y = y;
	return point;
}
void Point_Init(Point* point, int x, int y)
{
	point->X = x;
	point->Y = y;
}
Point Point_Zero()
{
	Point point = { 0 };
	return point;
}

bool Point_EqualTo(Point value1, Point value2)
{
	return (value1.X == value2.X) && (value1.Y == value2.Y);
}
bool Point_NotEqual(Point value1, Point value2)
{
	return !Point_EqualTo(value1, value2);
}
void Point_AddAssign(Point* value1, Point value2)
{
	value1->X += value2.X;
	value1->Y += value2.Y;
}
void Point_SubAssign(Point* value1, Point value2)
{
	value1->X -= value2.X;
	value1->Y -= value2.Y;
}
Point Point_Add(Point value1, Point value2)
{
	Point tempPoint;
	tempPoint.X = (value1.X + value2.X);
	tempPoint.Y = (value1.Y + value2.Y);
	return tempPoint;
}
Point Point_Sub(Point value1, Point value2)
{
	Point tempPoint;
	tempPoint.X = (value1.X - value2.X);
	tempPoint.Y = (value1.Y - value2.Y);
	return tempPoint;
}
Point Point_Mul(Point value1, Point value2)
{
	Point tempPoint;
	tempPoint.X = (value1.X * value2.X);
	tempPoint.Y = (value1.Y * value2.Y);
	return tempPoint;
}
Point Point_Div(Point value1, Point value2)
{
	Point tempPoint;
	tempPoint.X = (value1.X / value2.X);
	tempPoint.Y = (value1.Y / value2.Y);
	return tempPoint;
}