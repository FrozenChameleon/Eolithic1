/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "LevelCameraData.h"

#include "limits.h"
#include "float.h"
#include "../render/Color.h"
#include "../io/BufferReader.h"
#include "../io/BufferWriter.h"
//#include "OeMetaMapChunk.h"
#include "../render/SpriteBatch.h"
#include "../math/PointRectangle.h"

#define DEFAULT_STR_NOT_SET "NOT_SET"

//static std::vector<OeLevelCameraData> _mDummyCameraData = {};

PointRectangle* LevelCameraData_GetActiveBoundsPointRectangle(LevelCameraData* lcd)
{
	if (LevelCameraData_HasBounds(lcd))
	{
		return &lcd->mVolumeBounds;
	}
	else
	{
		return &lcd->mVolumeTrigger;
	}
}
bool LevelCameraData_HasBounds(LevelCameraData* lcd)
{
	return !PointRectangle_IsEmpty(&lcd->mVolumeBounds);
}
void LevelCameraData_Read(LevelCameraData* lcd, int version, BufferReader* reader)
{
	PointRectangle_Read(&lcd->mVolumeTrigger, reader);
	PointRectangle_Read(&lcd->mVolumeBounds, reader);
	lcd->mDirectionX =  BufferReader_ReadI32(reader);
	lcd->mDirectionY = BufferReader_ReadI32(reader);
	lcd->mIsPersistent = BufferReader_ReadBoolean(reader);
	lcd->mIsDualX = BufferReader_ReadBoolean(reader);
	lcd->mIsDualY = BufferReader_ReadBoolean(reader);
	lcd->mIsUpFrozen = BufferReader_ReadBoolean(reader);
	lcd->mIsRightFrozen = BufferReader_ReadBoolean(reader);
	lcd->mIsDownFrozen = BufferReader_ReadBoolean(reader);
	lcd->mIsLeftFrozen = BufferReader_ReadBoolean(reader);
	lcd->mScript = BufferReader_ReadMString(reader);
	if (version >= 2)
	{
		lcd->mId = BufferReader_ReadI32(reader);
		lcd->mIsTransition = BufferReader_ReadBoolean(reader);
		lcd->mNumberTransitionTo = BufferReader_ReadI32(reader);
		lcd->mNumberTransitionFrom = BufferReader_ReadI32(reader);
		lcd->mIsTransitionX = BufferReader_ReadBoolean(reader);
		lcd->mIsTransitionY = BufferReader_ReadBoolean(reader);
	}
	if (version >= 4)
	{
		for (int i = 0; i < LEVELCAMERADATA_STRING_DATA_LIMIT; i++)
		{
			lcd->mStringData[i] = BufferReader_ReadMString(reader);
		}
	}
}