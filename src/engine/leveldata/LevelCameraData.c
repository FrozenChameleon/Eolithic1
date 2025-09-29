/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "LevelCameraData.h"

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