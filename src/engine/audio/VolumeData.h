#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct VolumeData
{
	struct { char* key; int32_t value; } _mVolumeMap;
	bool _mIsMusic;
} VolumeData;
