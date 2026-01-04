#pragma once

#include "../utils/Macros.h"

typedef struct LeaderboardEntry
{
	int mGlobalRank;
	int mDisplayRank;
	int mScore;
	bool mIsCurrentUser;
	char mName[EE_FILENAME_MAX];
} LeaderboardEntry;