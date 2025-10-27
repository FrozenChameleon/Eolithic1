/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../math/Point.h"
#include "../math/Vector2.h"
#include "../render/Color.h"
#include "../math/Rectangle.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct SpriteBatch SpriteBatch;

typedef struct Line
{
	Point mBegin;
	Point mEnd;
	bool mEnterDownOnly;
	bool mEnterLeftOnly;
	bool mEnterUpOnly;
	bool mEnterRightOnly;
	bool mIsGap;
	bool mIsFirstLine;
	bool mIsLastLine;
	bool mOneWayUp;
	bool mOneWayRight;
	bool mOneWayDown;
	bool mOneWayLeft;
	int mOverrideSpeedFromPlayer;
	int mOverrideSpeedFromMinecart;
} Line;

Point Line_GetMiddle(Point begin, Point end);
void Line_DrawLineCamera(Line* line, SpriteBatch* spriteBatch, const char* font, Color color, int cameraWidth, int cameraHeight);
void Line_DrawLine(Line* line, SpriteBatch* spriteBatch, const char* font, Color color, int lineNumber, int offset);
void Line_DrawLineText(Line* line, SpriteBatch* spriteBatch, const char* font, int lineNumber, Vector2 pos);
double Line_GetDistance(Line* line);
bool Line_DoLinesConnect(Line* line1, Line* line2);
Point Line_GetJunction(Line* line1, Line* line2);
void Line_CorrectPoints(Line* line);
bool Line_IsVertical(Line* line);
int Line_GetReal(int point);
Point Line_GetRealByPoint(Point point);
Point Line_GetRealBegin(Line* line);
Point Line_GetRealEnd(Line* line);
//void Write(Line* line, std::shared_ptr<OeIniWriter> writer);
//void Read(int version, Line* line, std::shared_ptr<OeIniReader> reader);
Rectangle Line_GetTouchBounds(Line* line, int inflation);
//std::string ToString();

