#pragma once

#include "../math/Point.h"
#include "../math/Rectangle.h"
#include "../math/Vector2.h"
#include "../render/Color.h"

typedef struct Texture Texture;
typedef struct SpriteBatch SpriteBatch;

Texture* DrawTool_GetSinglePixel();
void DrawTool_DrawRectangle(SpriteBatch* spriteBatch, Color color, int depth, int x, int y, int width, int height, float rotation, bool isCenter);
void DrawTool_DrawRectangle2(SpriteBatch* spriteBatch, Color color, int depth, Rectangle destinationRect, float rotation, bool isCenter);
void DrawTool_DrawRectangleHollow(SpriteBatch* spriteBatch, Color color, int depth, int x, int y, int width, int height, float rotation, bool isCenter, int thickness);
void DrawTool_DrawRectangleHollow2(SpriteBatch* spriteBatch, Color color, int depth, Rectangle destinationRect, float rotation, bool isCenter, int thickness);
Rectangle DrawTool_GetBounds(const char* str, const char* font);
void DrawTool_DrawLine(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, Point begin, Point end);
void DrawTool_DrawLine2(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, Vector2 begin, Vector2 end);
void DrawTool_DrawLine3(SpriteBatch* spriteBatch, Color color, int depth, int delay, int offset, int size, float x1, float y1, float x2, float y2);