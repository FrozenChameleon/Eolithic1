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

typedef struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
} Color;

const extern Color Color_Red;
const extern Color Color_White;
const extern Color Color_Yellow;
const extern Color Color_Black;
const extern Color Color_LightGray;
const extern Color Color_Gray;

const extern Color COLOR_MUTE_DGRAY;
const extern Color COLOR_MUTE_LGRAY;
const extern Color COLOR_MUTE_RED;
const extern Color COLOR_MUTE_DARKRED;
const extern Color COLOR_MUTE_DARKERRED;
const extern Color COLOR_MUTE_YELLOW;
const extern Color COLOR_CYAN;
const extern Color COLOR_LIGHT_GRAY;
const extern Color COLOR_GRAY;
const extern Color COLOR_BLACK;
const extern Color COLOR_BLACK_ONE_FOURTH_ALPHA;
const extern Color COLOR_BLACK_TWO_FOURTH_ALPHA;
const extern Color COLOR_BLACK_THREE_FOURTH_ALPHA;
const extern Color COLOR_YELLOW;
const extern Color COLOR_ORANGE;
const extern Color COLOR_WHITE;
const extern Color COLOR_NOTHING;
const extern Color COLOR_RED;
const extern Color COLOR_GREEN;
const extern Color COLOR_MAGENTA;
const extern Color COLOR_BLUE;
const extern Color COLOR_PINK;
const extern Color COLOR_CORNFLOWER_BLUE;
const extern Color COLOR_PURPLE;
const extern Color COLOR_VIOLET;
const extern Color COLOR_COMETSTRIKER_BLUE;
const extern Color COLOR_COMETSTRIKER_GREEN;
const extern Color COLOR_COMETSTRIKER_RED;
const extern Color COLOR_COMETSTRIKER_PINK;
const extern Color COLOR_COMETSTRIKER_BORDER_INNER_GRAY;
const extern Color COLOR_COMETSTRIKER_BORDER_OUTER_GRAY;

void Color_Init(Color* color);
void Color_Init3(Color* color, int r, int g, int b);
void Color_Init4(Color* color, int r, int g, int b, int alpha);
bool Color_EqualTo(const Color* value1, const Color* value2);
bool Color_NotEqual(const Color* value1, const Color* value2);
Color Color_ToColor(Color color, int alpha);
float Color_RedF(Color color);
float Color_GreenF(Color color);
float Color_BlueF(Color color);
Color Color_Create4(int red, int green, int blue, int alpha);
Color Color_Create3(int red, int green, int blue);
Color Color_Create2(Color color, int alpha);
Color Color_Create(Color color);
void Color_Randomize(Color* color);