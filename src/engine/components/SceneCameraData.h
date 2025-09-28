#pragma once

#include "../leveldata/LevelCameraDataInstance.h"

typedef struct SceneCameraData
{
	LevelCameraDataInstance* mLastCamera;
	//std::vector<LevelCameraDataInstance> mCameraData;
	LevelCameraDataInstance* mCameraData;
} SceneCameraData;