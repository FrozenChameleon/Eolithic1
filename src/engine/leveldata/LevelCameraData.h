/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

#pragma once

#include "MetaMapChunk.h"
#include "../math/PointRectangle.h"
#include "../utils/MString.h"

enum { LEVELCAMERADATA_STRING_DATA_LIMIT = 10 };

typedef struct SpriteBatch SpriteBatch;
typedef struct BufferReader BufferReader;

typedef struct LevelCameraData
{
	MetaMapChunk* mAttachedChunk;
	PointRectangle mVolumeTrigger;
	PointRectangle mVolumeBounds;
	int32_t mDirectionX;
	int32_t mDirectionY;
	bool mIsPersistent;
	bool mIsDualX;
	bool mIsDualY;
	bool mIsUpFrozen;
	bool mIsRightFrozen;
	bool mIsDownFrozen;
	bool mIsLeftFrozen;
	char mScript[EE_FILENAME_MAX];
	int32_t mId;
	bool mIsTransition;
	int32_t mNumberTransitionTo;
	int32_t mNumberTransitionFrom;
	bool mIsTransitionX;
	bool mIsTransitionY;
	char mStringData[LEVELCAMERADATA_STRING_DATA_LIMIT][EE_FILENAME_MAX];
} LevelCameraData;

//void LevelCameraData_Ctor1();
//void LevelCameraData_Ctor2(const std::vector<OeLevelCameraData>& list);

bool LevelCameraData_IsDataSet(LevelCameraData* lcd, int32_t index);
//void LevelCameraData_GenerateNewId(LevelCameraData* lcd, const std::vector<OeLevelCameraData>& list);
bool LevelCameraData_HasTrigger(LevelCameraData* lcd);
bool LevelCameraData_HasBounds(LevelCameraData* lcd);
PointRectangle* LevelCameraData_GetActiveBoundsPointRectangle(LevelCameraData* lcd);
void LevelCameraData_Add(LevelCameraData* lcd, int32_t amountX, int32_t amountY);
//void LevelCameraData_Write(LevelCameraData* lcd, std::shared_ptr<OeIniWriter> writer);
void LevelCameraData_Read(LevelCameraData* lcd, int32_t version, BufferReader* reader);
bool LevelCameraData_IsScriptSet(LevelCameraData* lcd);
void LevelCameraData_Draw(LevelCameraData* lcd, SpriteBatch* spriteBatch, bool isSelected, bool drawBounds);
const char* LevelCameraData_ToString(LevelCameraData* lcd);