/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "MetaMapChunk.h"
#include "../math/PointRectangle.h"
#include "../utils/FixedChar260.h"

enum { LEVEL_CAMERA_DATA_STRING_DATA_LIMIT = 10 };

typedef struct SpriteBatch SpriteBatch;

typedef struct LevelCameraData
{
	MetaMapChunk* mAttachedChunk;
	PointRectangle mVolumeTrigger;
	PointRectangle mVolumeBounds;
	int mDirectionX;
	int mDirectionY;
	bool mIsPersistent;
	bool mIsDualX;
	bool mIsDualY;
	bool mIsUpFrozen;
	bool mIsRightFrozen;
	bool mIsDownFrozen;
	bool mIsLeftFrozen;
	const char* mScript;
	int mId;
	bool mIsTransition;
	int mNumberTransitionTo;
	int mNumberTransitionFrom;
	bool mIsTransitionX;
	bool mIsTransitionY;
	FixedChar260 mStringData[LEVEL_CAMERA_DATA_STRING_DATA_LIMIT];
} LevelCameraData;

//void LevelCameraData_Ctor1();
//void LevelCameraData_Ctor2(const std::vector<OeLevelCameraData>& list);

bool LevelCameraData_IsDataSet(LevelCameraData* lcd, int index);
//void LevelCameraData_GenerateNewId(LevelCameraData* lcd, const std::vector<OeLevelCameraData>& list);
bool LevelCameraData_HasTrigger(LevelCameraData* lcd);
bool LevelCameraData_HasBounds(LevelCameraData* lcd);
PointRectangle* LevelCameraData_GetActiveBoundsPointRectangle(LevelCameraData* lcd);
void LevelCameraData_Add(LevelCameraData* lcd, int amountX, int amountY);
//void LevelCameraData_Write(LevelCameraData* lcd, std::shared_ptr<OeIniWriter> writer);
//void LevelCameraData_Read(LevelCameraData* lcd, int version, std::shared_ptr<OeIniReader> reader);
bool LevelCameraData_IsScriptSet(LevelCameraData* lcd);
void LevelCameraData_Draw(LevelCameraData* lcd, SpriteBatch* spriteBatch, bool isSelected, bool drawBounds);
const char* LevelCameraData_ToString(LevelCameraData* lcd);