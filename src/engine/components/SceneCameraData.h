#pragma once

#include "../leveldata/LevelCameraDataInstance.h"

struct SceneCameraData final
{
	LevelCameraDataInstance* mLastCamera;
	//std::vector<LevelCameraDataInstance> mCameraData;
	LevelCameraDataInstance* mCameraData;
};

