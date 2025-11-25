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

#include "Color.h"

#include "../globals/Globals.h"
#include "../math/Random32.h"

const Color Color_Red = { 255, 0, 0, 255 };
const Color Color_White = { 255, 255, 255, 255 };
const Color Color_Yellow = {255, 255, 0, 255 };
const Color Color_Black = {0, 0, 0, 255 };
const Color Color_LightGray = {211, 211, 211, 255 };
const Color Color_Gray = { 128, 128, 128, 255 };

const Color COLOR_MUTE_DGRAY = {102, 102, 102, 255};
const Color COLOR_MUTE_LGRAY = {172, 172, 172, 255 };
const Color COLOR_MUTE_RED = {181, 48, 31, 255 };
const Color COLOR_MUTE_DARKRED = {107, 8, 0, 255 };
const Color COLOR_MUTE_DARKERRED = {64, 5, 0, 255 };
const Color COLOR_MUTE_YELLOW = {234, 158, 33, 255 };
const Color COLOR_CYAN = {0, 255, 255, 255 };
const Color COLOR_LIGHT_GRAY = {191, 191, 191, 255 };
const Color COLOR_GRAY = {128, 128, 128, 255 };
const Color COLOR_BLACK = {0, 0, 0, 255 };
const Color COLOR_BLACK_ONE_FOURTH_ALPHA = {0, 0, 0, 64};
const Color COLOR_BLACK_TWO_FOURTH_ALPHA = {0, 0, 0, 128};
const Color COLOR_BLACK_THREE_FOURTH_ALPHA = {0, 0, 0, 192};
const Color COLOR_YELLOW = {255, 255, 0, 255 };
const Color COLOR_ORANGE = {255, 164, 0, 255 };
const Color COLOR_WHITE = {255, 255, 255, 255 };
const Color COLOR_NOTHING = {0, 0, 0, 0};
const Color COLOR_RED = {255, 0, 0, 255 };
const Color COLOR_GREEN = {0, 255, 0, 255 };
const Color COLOR_MAGENTA = {255, 0, 255, 255 };
const Color COLOR_BLUE = {0, 0, 255, 255 };
const Color COLOR_PINK = {255, 191, 202, 255 };
const Color COLOR_CORNFLOWER_BLUE = {99, 148, 237, 255 };
const Color COLOR_PURPLE = {127, 0, 127, 255 };
const Color COLOR_VIOLET = {237, 130, 237, 255 };
const Color COLOR_COMETSTRIKER_BLUE = {0, 128, 205, 255 };
const Color COLOR_COMETSTRIKER_GREEN = {18, 148, 0, 255 };
const Color COLOR_COMETSTRIKER_RED = {255, 63, 63, 255 };
const Color COLOR_COMETSTRIKER_PINK = {255, 0, 240, 255 };
const Color COLOR_COMETSTRIKER_BORDER_INNER_GRAY = {166, 166, 166, 255 };
const Color COLOR_COMETSTRIKER_BORDER_OUTER_GRAY = {76, 76, 76, 255 };

void Color_Init(Color* color)
{
	color->R = 0;
	color->G = 0;
	color->B = 0;
	color->A = 255;
}
void Color_Init3(Color* color, int r, int g, int b)
{
	color->R = r;
	color->G = g;
	color->B = b;
	color->A = 255;
}
void Color_Init4(Color* color, int r, int g, int b, int alpha)
{
	color->R = r;
	color->G = g;
	color->B = b;
	color->A = alpha;
}
bool Color_EqualTo(Color value1, Color value2)
{
	return (value1.R == value2.R) &&
		(value1.G == value2.G) &&
		(value1.B == value2.B) &&
		(value1.A == value2.A);
}
bool Color_NotEqual(Color value1, Color value2)
{
	return !Color_EqualTo(value1, value2);
}
Color Color_ToColor(Color color, int alpha)
{
	Color tempColor = { color.R, color.G, color.B, alpha };
	return tempColor;
}
float Color_RedF(Color color)
{
	return color.R / 255.0f;
}
float Color_GreenF(Color color)
{
	return color.G / 255.0f;
}
float Color_BlueF(Color color)
{
	return color.B / 255.0f;
}
Color Color_Create4(int red, int green, int blue, int alpha)
{
	Color tempColor;
	Color_Init4(&tempColor, red, green, blue, alpha);
	return tempColor;
}
Color Color_Create3(int red, int green, int blue)
{
	Color tempColor;
	Color_Init3(&tempColor, red, green, blue);
	return tempColor;
}
Color Color_Create2(Color color, int alpha)
{
	color.A = alpha;
	return color;
}
Color Color_Create(Color color)
{
	return color;
}
void Color_Randomize(Color* color)
{
	Random32* sharedRandom = Globals_GetSharedRandom();
	color->R = Random32_NextInt(sharedRandom, 255);
	color->G = Random32_NextInt(sharedRandom, 255);
	color->B = Random32_NextInt(sharedRandom, 255);
}