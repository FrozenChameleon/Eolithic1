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

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "Point.h"

typedef struct Rectangle
{
	int32_t X;
	int32_t Y;
	int32_t Width;
	int32_t Height;
} Rectangle;

void Rectangle_Init(Rectangle* value, int x, int y, int width, int height);
bool Rectangle_EqualTo(const Rectangle* value1, const Rectangle* value2);
bool Rectangle_NotEqual(const Rectangle* value1, const Rectangle* value2);
void Rectangle_Inflate(Rectangle* value, int horizontalValue, int verticalValue);
Point Rectangle_Center(const Rectangle* value);
int32_t Rectangle_Left(const Rectangle* value);
int32_t Rectangle_Right(const Rectangle* value);
int32_t Rectangle_Top(const Rectangle* value);
int32_t Rectangle_Bottom(const Rectangle* value);
bool Rectangle_Intersects(const Rectangle* value1, const Rectangle* value2);
bool Rectangle_Contains(const Rectangle* value, int x, int y);
bool Rectangle_ContainsPoint(const Rectangle* value1, Point value2);
bool Rectangle_ContainsRectangle(const Rectangle* value1, const Rectangle* value2);
bool Rectangle_IsEmpty(const Rectangle* value);
Rectangle Rectangle_Empty();
