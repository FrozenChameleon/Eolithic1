/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Math.h"

#include "SDL3/SDL.h"
#include "MathHelper.h"

#define VALUE_OF_PI 3.14159265358979323846

const double MATH_TICK_15HZ = (1.0 / 15.0);
const double MATH_TICK_30HZ = (1.0 / 30.0);
const double MATH_TICK_60HZ = (1.0 / 60.0);
const float MATH_DIAGONAL_LIMITER_MUL = 0.7071f;
const double MATH_PI = VALUE_OF_PI;
const double MATH_HALFPI = (VALUE_OF_PI / 2.0);
const double MATH_TWOPI = (VALUE_OF_PI * 2.0);

double Math_cos(double x)
{
	return SDL_cos(x);
}
double Math_sin(double x)
{
	return SDL_sin(x);
}
double Math_sqrt(double x)
{
	return SDL_sqrt(x);
}
int32_t Math_SignumInt32(int32_t value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int32_t Math_SignumInt64(int64_t value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int32_t Math_SignumSingle(float value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
int32_t Math_SignumDouble(double value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
float Math_ToDegrees(float value)
{
	return MathHelper_ToDegrees(value);
}
float Math_ToRadians(float value)
{
	return MathHelper_ToRadians(value);
}
int32_t Math_abs(int value)
{
	return SDL_abs(value);
}
float Math_fabsf(float value)
{
	return SDL_fabsf(value);
}
double Math_fabs(double value)
{
	return SDL_fabs(value);
}
float Math_ceilf(float value)
{
	return SDL_ceilf(value);
}
double Math_ceil(double value)
{
	return SDL_ceil(value);
}
float Math_floorf(float value)
{
	return SDL_floorf(value);
}
double Math_floor(double value)
{
	return SDL_floor(value);
}
double Math_atan(double x)
{
	return SDL_atan(x);
}
double Math_atan2(double y, double x)
{
	return SDL_atan2(y, x);
}
