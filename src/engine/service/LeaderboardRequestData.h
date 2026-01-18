#pragma once

#include "../utils/Macros.h"

typedef struct LeaderboardRequestData
{
	int32_t mScopeType;
	bool mIsAscending;
	bool mIsMilliseconds;
	char mName[EE_FILENAME_MAX];
} LeaderboardRequestData;
