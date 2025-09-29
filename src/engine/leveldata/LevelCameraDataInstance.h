/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "LevelCameraData.h"

typedef struct LevelCameraDataInstance
{
	bool mIsComplete;
	bool mIsCompletePermanently;
	LevelCameraData mData;
} LevelCameraDataInstance;

//CTOR1OeLevelCameraDataInstance(LevelCameraDataInstance* lcdi);
//CTOR2OeLevelCameraDataInstance(LevelCameraDataInstance* lcdi, OeLevelCameraData& data);

void LevelCameraDataInstance_Reset(LevelCameraDataInstance* lcdi);
void LevelCameraDataInstance_ResetFullyNoMatterWhat(LevelCameraDataInstance* lcdi);
void LevelCameraDataInstance_ResetIfNotCompletePermanently(LevelCameraDataInstance* lcdi);
void LevelCameraDataInstance_SetCompletePermanently(LevelCameraDataInstance* lcdi);
void LevelCameraDataInstance_SetComplete(LevelCameraDataInstance* lcdi);
bool LevelCameraDataInstance_IsComplete(LevelCameraDataInstance* lcdi);
void LevelCameraDataInstance_ResetState(LevelCameraDataInstance* lcdi);