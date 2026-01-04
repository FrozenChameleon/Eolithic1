#pragma once

#include "../utils/Macros.h"

typedef struct LeaderboardRequestData
{
	int mScopeType;
	bool mIsAscending;
	bool mIsMilliseconds;
	char mName[EE_FILENAME_MAX];
} LeaderboardRequestData;
