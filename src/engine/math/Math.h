/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "Point.h"
#include "Vector2.h"

extern const double MATH_TICK_15HZ;
extern const double MATH_TICK_30HZ;
extern const double MATH_TICK_60HZ;
extern const float MATH_DIAGONAL_LIMITER_MUL;
extern const double MATH_PI;
extern const double MATH_HALFPI;
extern const double MATH_TWOPI;

double Math_cos(double x);
double Math_sin(double x);
double Math_sqrt(double x);
int32_t Math_SignumInt32(int32_t value);
int32_t Math_SignumInt64(int64_t value);
int32_t Math_SignumSingle(float value);
int32_t Math_SignumDouble(double value);
float Math_ToDegrees(float value);
float Math_ToRadians(float value);
int32_t Math_abs(int value);
float Math_fabsf(float value);
double Math_fabs(double value);
float Math_ceilf(float value);
double Math_ceil(double value);
float Math_floorf(float value);
double Math_floor(double value);
double Math_atan(double x);
double Math_atan2(double y, double x);
int32_t Math_MinInt32(int32_t valueA, int32_t valueB);
float Math_MinSingle(float valueA, float valueB);
double Math_MinDouble(double valueA, double valueB);
int32_t Math_MaxInt32(int32_t valueA, int32_t valueB);
float Math_MaxSingle(float valueA, float valueB);
double Math_MaxDouble(double valueA, double valueB);
int Math_GetDistanceInt32(int32_t x1, int32_t x2);
float Math_GetDistanceSingle(float x1, float x2);
double Math_GetDistanceDouble(double x1, double x2);
double Math_GetDistanceEuclideanPoint(Point begin, Point end);
double Math_GetDistanceEuclideanVector2(Vector2 begin, Vector2 end);
double Math_GetDistanceEuclideanSingle(float x1, float y1, float x2, float y2);