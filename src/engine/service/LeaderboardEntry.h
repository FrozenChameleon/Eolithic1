#pragma once

#include "../utils/Macros.h"

typedef struct LeaderboardEntry
{
	int32_t mGlobalRank;
	int32_t mDisplayRank;
	int32_t mScore;
	bool mIsCurrentUser;
	char mName[EE_FILENAME_MAX];
} LeaderboardEntry;