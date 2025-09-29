#include "Vectors.h"

#include "limits.h"
#include "float.h"

const Vector2 Vectors_MinValue = { FLT_MIN, FLT_MIN };
const Vector2 Vectors_MaxValue = { FLT_MAX, FLT_MAX };
const Vector2 Vectors_NegativeOne = { -1, -1 };
const Vector2 Vectors_Up = { 0, -1 };
const Vector2 Vectors_UpRight = { 1, -1 };
const Vector2 Vectors_Right = { 1, 0 };
const Vector2 Vectors_DownRight = { 1, 1 };
const Vector2 Vectors_Down = { 0, 1 };
const Vector2 Vectors_DownLeft = { -1, 1 };
const Vector2 Vectors_Left = { -1, 0 };
const Vector2 Vectors_UpLeft = { -1, -1 };

Vector2 Vectors_ToVector2(Point point)
{
	Vector2 temp = { point.X, point.Y };
	return temp;
}
const char* Vectors_ToString(Vector2 vec)
{
	return NULL;
	//return ("{X:" + std::to_string(vec.X) + " Y:" + std::to_string(vec.Y) + "}");
}
