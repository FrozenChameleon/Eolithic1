#include "limits.h"
#include "Points.h"
#include "Math.h"
#include "../utils/Utils.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE
#define HALF_TILE_SIZE GLOBAL_DEF_HALF_TILE_SIZE

const Point Points_MinValue = {INT_MIN, INT_MIN};
const Point Points_MaxValue = {INT_MAX, INT_MAX};
const Point Points_NegativeOne = {-1, -1};
const Point Points_Up = {0, -1};
const Point Points_UpRight = {1, -1};
const Point Points_Right = {1, 0};
const Point Points_DownRight = {1, 1};
const Point Points_Down = {0, 1};
const Point Points_DownLeft = {-1, 1};
const Point Points_Left = {-1, 0};
const Point Points_UpLeft = {-1, -1};

Point Points_TileSize()
{
	return Points_ToPointFromInt(TILE_SIZE);
}
Point Points_HalfTileSize()
{
	return Points_ToPointFromInt(HALF_TILE_SIZE);
}
Point Points_ToPointFromInt(int value)
{
	Point temp = { value, value };
	return temp;
}
Point Points_ToPointFromVector2(Vector2 value)
{
	Point temp = { (int)value.X, (int)value.Y };
	return temp;
}
Point Points_GetEightWay(int direction)
{
	switch (direction)
	{
	case POINTS_EIGHTWAY_UP:
		return Points_Up;
	case POINTS_EIGHTWAY_UPRIGHT:
		return Points_UpRight;
	case POINTS_EIGHTWAY_RIGHT:
		return Points_Right;
	case POINTS_EIGHTWAY_DOWNRIGHT:
		return Points_DownRight;
	case POINTS_EIGHTWAY_DOWN:
		return Points_Down;
	case POINTS_EIGHTWAY_DOWNLEFT:
		return Points_DownLeft;
	case POINTS_EIGHTWAY_LEFT:
		return Points_Left;
	case POINTS_EIGHTWAY_UPLEFT:
		return Points_UpLeft;
	default:
		return Point_Zero;
	}
}
Point Points_GetFourWay(int direction)
{
	switch (direction)
	{
	case POINTS_FOURWAY_UP:
		return Points_Up;
	case POINTS_FOURWAY_RIGHT:
		return Points_Right;
	case POINTS_FOURWAY_DOWN:
		return Points_Down;
	case POINTS_FOURWAY_LEFT:
		return Points_Left;
	default:
		return Point_Zero;
	}
}
void Points_Rotate(Point* point, int degree)
{
	int amount = degree / 90;

	for (int i = 0; i < amount; i++)
	{
		int tempX = point->X;
		point->X = point->Y;
		point->Y = -tempX;
	}
}
double Points_GetAngle(Point point)
{
	return Math_atan2(point.Y, point.X);
}
void Points_ReverseX(Point* point)
{
	point->X = -point->X;
}
void Points_ReverseY(Point* point)
{
	point->Y = -point->Y;
}
void Points_Reverse(Point* point)
{
	Points_ReverseX(point);
	Points_ReverseY(point);
}
float Points_GetDegree(Point point)
{
	if (Points_IsUp(point))
	{
		return 0;
	}
	else if (Points_IsUpRight(point))
	{
		return 45;
	}
	else if (Points_IsRight(point))
	{
		return 90;
	}
	else if (Points_IsDownRight(point))
	{
		return 135;
	}
	else if (Points_IsDown(point))
	{
		return 180;
	}
	else if (Points_IsDownLeft(point))
	{
		return 225;
	}
	else if (Points_IsLeft(point))
	{
		return 270;
	}
	else if (Points_IsUpLeft(point))
	{
		return 315;
	}
	else
	{
		return -1;
	}
}
int Points_GetFourWayInt(Point point)
{
	if (Points_IsUp(point))
	{
		return POINTS_FOURWAY_UP;
	}
	else if (Points_IsRight(point))
	{
		return POINTS_FOURWAY_RIGHT;
	}
	else if (Points_IsDown(point))
	{
		return POINTS_FOURWAY_DOWN;
	}
	else if (Points_IsLeft(point))
	{
		return POINTS_FOURWAY_LEFT;
	}
	else
	{
		return -1;
	}
}
float Points_GetDiagCorrectedX(Point point)
{
	if (Points_IsUpRight(point) || Points_IsDownRight(point) || Points_IsDownLeft(point) || Points_IsUpLeft(point))
	{
		return point.X * MATH_DIAGONAL_LIMITER_MUL;
	}
	else
	{
		return point.X;
	}
}
float Points_GetDiagCorrectedY(Point point)
{
	if (Points_IsUpRight(point) || Points_IsDownRight(point) || Points_IsDownLeft(point) || Points_IsUpLeft(point))
	{
		return point.Y * MATH_DIAGONAL_LIMITER_MUL;
	}
	else
	{
		return point.Y;
	}
}
void Points_SetDirectionFromFourWayInt(Point* point, int direction)
{
	switch (direction)
	{
	case POINTS_FOURWAY_UP:
		Points_SetUp(point);
		break;
	case POINTS_FOURWAY_RIGHT:
		Points_SetRight(point);
		break;
	case POINTS_FOURWAY_DOWN:
		Points_SetDown(point);
		break;
	case POINTS_FOURWAY_LEFT:
		Points_SetLeft(point);
		break;
	default:
		break;
	}
}
void Points_SetDirectionFromEightWayInt(Point* point, int direction)
{
	switch (direction)
	{
	case POINTS_EIGHTWAY_UP:
		Points_SetUp(point);
		break;
	case POINTS_EIGHTWAY_UPRIGHT:
		Points_SetUpRight(point);
		break;
	case POINTS_EIGHTWAY_RIGHT:
		Points_SetRight(point);
		break;
	case POINTS_EIGHTWAY_DOWNRIGHT:
		Points_SetDownRight(point);
		break;
	case POINTS_EIGHTWAY_DOWN:
		Points_SetDown(point);
		break;
	case POINTS_EIGHTWAY_DOWNLEFT:
		Points_SetDownLeft(point);
		break;
	case POINTS_EIGHTWAY_LEFT:
		Points_SetLeft(point);
		break;
	case POINTS_EIGHTWAY_UPLEFT:
		Points_SetUpLeft(point);
		break;
	default:
		break;
	}
}
void Points_RotateClockwise(Point* point, int amount)
{
	int value = Points_GetEightWayInt(*point);
	for (int i = 0; i < amount; i++)
	{
		value += 1;
		if (value > POINTS_EIGHTWAY_UPLEFT)
		{
			value = 0;
		}
	}
	Points_SetDirectionFromEightWayInt(point, value);
}
void Points_RotateCounterClockwise(Point* point, int amount)
{
	int value = Points_GetEightWayInt(*point);
	for (int i = 0; i < amount; i++)
	{
		value -= 1;
		if (value < 0)
		{
			value = POINTS_EIGHTWAY_UPLEFT;
		}
	}
	Points_SetDirectionFromEightWayInt(point, value);
}
void Points_SetUp(Point* point)
{
	point->X = 0;
	point->Y = -1;
}
void Points_SetUpRight(Point* point)
{
	point->X = 1;
	point->Y = -1;
}
void Points_SetRight(Point* point)
{
	point->X = 1;
	point->Y = 0;
}
void Points_SetDownRight(Point* point)
{
	point->X = 1;
	point->Y = 1;
}
void Points_SetDown(Point* point)
{
	point->X = 0;
	point->Y = 1;
}
void Points_SetDownLeft(Point* point)
{
	point->X = -1;
	point->Y = 1;
}
void Points_SetLeft(Point* point)
{
	point->X = -1;
	point->Y = 0;
}
void Points_SetUpLeft(Point* point)
{
	point->X = -1;
	point->Y = -1;
}
bool Points_IsDiagonal(Point point)
{
	if (point.X != 0 && point.Y != 0)
	{
		return true;
	}
	return false;
}
bool Points_IsUp(Point point)
{
	return (point.X == 0) && (point.Y == -1);
}
bool Points_IsUpRight(Point point)
{
	return (point.X == 1) && (point.Y == -1);
}
bool Points_IsRight(Point point)
{
	return (point.X == 1) && (point.Y == 0);
}
bool Points_IsDownRight(Point point)
{
	return (point.X == 1) && (point.Y == 1);
}
bool Points_IsDown(Point point)
{
	return (point.X == 0) && (point.Y == 1);
}
bool Points_IsDownLeft(Point point)
{
	return (point.X == -1) && (point.Y == 1);
}
bool Points_IsLeft(Point point)
{
	return (point.X == -1) && (point.Y == 0);
}
bool Points_IsUpLeft(Point point)
{
	return (point.X == -1) && (point.Y == -1);
}
int Points_GetEightWayInt(Point point)
{
	if (Points_IsUp(point))
	{
		return POINTS_EIGHTWAY_UP;
	}
	else if (Points_IsUpRight(point))
	{
		return POINTS_EIGHTWAY_UPRIGHT;
	}
	else if (Points_IsRight(point))
	{
		return POINTS_EIGHTWAY_RIGHT;
	}
	else if (Points_IsDownRight(point))
	{
		return POINTS_EIGHTWAY_DOWNRIGHT;
	}
	else if (Points_IsDown(point))
	{
		return POINTS_EIGHTWAY_DOWN;
	}
	else if (Points_IsDownLeft(point))
	{
		return POINTS_EIGHTWAY_DOWNLEFT;
	}
	else if (Points_IsLeft(point))
	{
		return POINTS_EIGHTWAY_LEFT;
	}
	else if (Points_IsUpLeft(point))
	{
		return POINTS_EIGHTWAY_UPLEFT;
	}
	else
	{
		return -1;
	}
}
void Points_SetFromDegree(Point* point, int degree)
{
	int offset = 22;
	int halfOffset = offset / 2;

	int firstUp = 360;
	int secondUp = 0;
	int upRight = 45;
	int right = 90;
	int downRight = 135;
	int down = 180;
	int downLeft = 225;
	int left = 270;
	int upLeft = 315;

	if (degree >= (firstUp - halfOffset) || degree <= (secondUp + halfOffset)) //UP
	{
		point->X = 0;
		point->Y = -1;
	}
	else if (degree >= (upRight - offset) && degree <= (upRight + offset)) //UPRIGHT
	{
		point->X = 1;
		point->Y = -1;
	}
	else if (degree >= (right - offset) && degree <= (right + offset)) //RIGHT
	{
		point->X = 1;
		point->Y = 0;
	}
	else if (degree >= (downRight - offset) && degree <= (downRight + offset)) //DOWNRIGHT
	{
		point->X = 1;
		point->Y = 1;
	}
	else if (degree >= (down - offset) && degree <= (down + offset)) //DOWN
	{
		point->X = 0;
		point->Y = 1;
	}
	else if (degree >= (downLeft - offset) && degree <= (downLeft + offset)) //DOWNLEFT
	{
		point->X = -1;
		point->Y = 1;
	}
	else if (degree >= (left - offset) && degree <= (left + offset)) //LEFT
	{
		point->X = -1;
		point->Y = 0;
	}
	else if (degree >= (upLeft - offset) && degree <= (upLeft + offset)) //UPLEFT
	{
		point->X = -1;
		point->Y = -1;
	}
}
/*
void Points_Write(Point point, std::shared_ptr<OeIniWriter> writer)
{
	writer->WriteInt32(point.X);
	writer->WriteInt32(point.Y);
}
void Points_Read(Point* point, std::shared_ptr<OeIniReader> reader)
{
	point->X = reader->ReadInt32();
	point->Y = reader->ReadInt32();
}
*/
const char* Points_ToString(Point point) //FROM FNA
{
	return NULL;
	/*
	return (
		"{X:" + std::to_string(point.X) +
		" Y:" + std::to_string(point.Y) +
		"}"
		);
		*/
}
