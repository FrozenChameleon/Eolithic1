#pragma once

typedef struct LeaderboardEntry
{
	int mGlobalRank;
	int mDisplayRank;
	int mScore;
	bool mIsCurrentUser;
	const char* mName;
} LeaderboardEntry;