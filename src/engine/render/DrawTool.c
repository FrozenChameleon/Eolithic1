#include "DrawTool.h"

#include "SpriteBatch.h"
#include "../math/Math.h"
#include "../math/Point.h"
#include "../resources/TextureManager.h"
#include "../resources/BmFontManager.h"

static Resource* _mSinglePixel;

static BmFont* GetFont(const char* font)
{
	return BmFontManager_GetResourceData(font);
}

Texture* DrawTool_GetSinglePixel()
{
	if (_mSinglePixel == NULL)
	{
		_mSinglePixel = TextureManager_GetResource("one_by_one_pixel");
		if (_mSinglePixel == NULL)
		{
			return NULL;
		}
	}

	return _mSinglePixel->mData;
}
void DrawTool_DrawRectangle(SpriteBatch* spriteBatch, Color color, int depth, int x, int y, int width, int height, float rotation, bool isCenter)
{
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(x, y, width, height), rotation, isCenter);
}
void DrawTool_DrawRectangle2(SpriteBatch* spriteBatch, Color color, int depth, Rectangle destinationRect, float rotation, bool isCenter)
{
	int newX = destinationRect.X;
	int newY = destinationRect.Y;
	if (isCenter)
	{
		newX -= destinationRect.Width / 2;
		newY -= destinationRect.Height / 2;
	}
	//TODO C99 Vector2 origin = Vector2(destinationRect.Width / 2, destinationRect.Height / 2);
	//spriteBatch->DrawRectangle(GetSinglePixel(), color, depth, nullptr, Rectangle(newX, newY, destinationRect.Width, destinationRect.Height),
//		Rectangle(0, 0, 1, 1), rotation, false, false, origin);
}
void DrawTool_DrawRectangleHollow(SpriteBatch* spriteBatch, Color color, int depth, int x, int y, int width, int height, float rotation, bool isCenter, int thickness)
{
	DrawTool_DrawRectangleHollow2(spriteBatch, color, depth, Rectangle_Create(x, y, width, height), rotation, isCenter, thickness);
}
void DrawTool_DrawRectangleHollow2(SpriteBatch* spriteBatch, Color color, int depth, Rectangle destinationRect, float rotation, bool isCenter, int thickness)
{
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(destinationRect.X, destinationRect.Y, destinationRect.Width, thickness), rotation, isCenter);
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(destinationRect.X, destinationRect.Y + destinationRect.Height - thickness, destinationRect.Width, thickness), rotation, isCenter);
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(destinationRect.X, destinationRect.Y, thickness, destinationRect.Height), rotation, isCenter);
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(destinationRect.X + destinationRect.Width - thickness, destinationRect.Y, thickness, destinationRect.Height), rotation, isCenter);
}
Rectangle DrawTool_GetBounds(const char* str, const char* font)
{
	return BmFont_GetBounds(GetFont(font), str, false);
}
void DrawTool_DrawLine(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, Point begin, Point end)
{
	DrawTool_DrawLine3(spriteBatch, color, depth, delay, offset, size, begin.X, begin.Y, end.X, end.Y);
}
void DrawTool_DrawLine2(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, Vector2 begin, Vector2 end)
{
	DrawTool_DrawLine3(spriteBatch, color, depth, delay, offset, size, begin.X, begin.Y, end.X, end.Y);
}
void DrawTool_DrawLine3(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, float x1, float y1, float x2, float y2)
{
	double distance = 0; //TODO C99 Math_GetLineDistance(x1, y1, x2, y2);
	double seg = (x2 - x1) / distance;
	int counter = 0;
	for (int i = 0; i < distance; i++)
	{
		float x;
		float y;
		if (x1 == x2) //undefined slope
		{
			x = x1;
			y = (float)(y1 + (y2 - y1) / distance * i);
		}
		else
		{
			x = (float)(x1 + i * seg);
			y = Math_GetSlopeInterceptY(x1, y1, x2, y2, x);
		}
		if ((counter + offset) % delay == 0)
		{
			DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create((int)x, (int)y, size, size), 0, true);
		}
		counter++;
	}
}