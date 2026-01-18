#include "DrawTool.h"

#include "SpriteBatch.h"
#include "../math/Math.h"
#include "../math/Point.h"
#include "../resources/ResourceManagerList.h"

static Resource* _mSinglePixel;

static BmFont* GetFont(const char* font)
{
	return ResourceManager_GetResourceData(ResourceManagerList_Font(), font);
}

Texture* DrawTool_GetSinglePixel()
{
	if (_mSinglePixel == NULL)
	{
		_mSinglePixel = ResourceManager_GetResource(ResourceManagerList_Texture(), "one_by_one_pixel");
		if (_mSinglePixel == NULL)
		{
			return NULL;
		}
	}

	return _mSinglePixel->mData;
}
void DrawTool_DrawRectangle(SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t x, int32_t y, int32_t width, int32_t height, float rotation, bool isCenter)
{
	DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create(x, y, width, height), rotation, isCenter);
}
void DrawTool_DrawRectangle2(SpriteBatch* spriteBatch, Color color, int32_t depth, Rectangle destinationRect, float rotation, bool isCenter)
{
	int32_t newX = destinationRect.X;
	int32_t newY = destinationRect.Y;
	if (isCenter)
	{
		newX -= destinationRect.Width / 2;
		newY -= destinationRect.Height / 2;
	}
	Vector2 origin = Vector2_Create((float)(destinationRect.Width / 2), (float)(destinationRect.Height / 2));
	SpriteBatch_DrawRectangle(spriteBatch, DrawTool_GetSinglePixel(), color, depth, NULL, Rectangle_Create(newX, newY, destinationRect.Width, destinationRect.Height),
		Rectangle_Create(0, 0, 1, 1), rotation, false, false, origin);
}
void DrawTool_DrawRectangleHollow(SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t x, int32_t y, int32_t width, int32_t height, float rotation, bool isCenter, int32_t thickness)
{
	DrawTool_DrawRectangleHollow2(spriteBatch, color, depth, Rectangle_Create(x, y, width, height), rotation, isCenter, thickness);
}
void DrawTool_DrawRectangleHollow2(SpriteBatch* spriteBatch, Color color, int32_t depth, Rectangle destinationRect, float rotation, bool isCenter, int32_t thickness)
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
void DrawTool_DrawLine(SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t delay, int32_t offset, int32_t size, Point begin, Point end)
{
	DrawTool_DrawLine3(spriteBatch, color, depth, delay, offset, size, (float)begin.X, (float)begin.Y, (float)end.X, (float)end.Y);
}
void DrawTool_DrawLine2(SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t delay, int32_t offset, int32_t size, Vector2 begin, Vector2 end)
{
	DrawTool_DrawLine3(spriteBatch, color, depth, delay, offset, size, begin.X, begin.Y, end.X, end.Y);
}
void DrawTool_DrawLine3(SpriteBatch* spriteBatch, Color color, int32_t depth, int32_t delay, int32_t offset, int32_t size, float x1, float y1, float x2, float y2)
{
	double distance = Math_GetLineDistance(x1, y1, x2, y2);
	double seg = (x2 - x1) / distance;
	int32_t counter = 0;
	for (int32_t i = 0; i < distance; i += 1)
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
			DrawTool_DrawRectangle2(spriteBatch, color, depth, Rectangle_Create((int32_t)x, (int32_t)y, size, size), 0, true);
		}
		counter += 1;
	}
}