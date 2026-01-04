#pragma once

#include "stdbool.h"
#include "LeaderboardEntry.h"
#include "LeaderboardRequestData.h"

//supposed to be private
bool Service_IsLeaderboardRequestQueued();
bool Service_IsLeaderboardRateLimited();
int Service_GetPageThatYouAreOn();

//supposed to be protected
void Service_NullLeaderboardEntries();
void Service_CreateLeaderboardEntries();
int Service_GetLeaderboardAmountOfRowsToRetrieve();
void Service_SetLeaderboardSendStatus(int status);
void Service_SetLeaderboardSendStatus2(int status, int frames);
void Service_UpdateScoreKeepBestHelper(const char* leaderboard, int score, bool isAscending, bool isMilliseconds);
const char* Service_GetCurrentLeaderboardName();
int Service_GetCurrentLeaderboardScope();
bool Service_IsCurrentLeaderboardAscending();
bool Service_IsCurrentLeaderboardMilliseconds();
int Service_GetHighestPossiblePage();
void Service_RetrieveLeaderboardEntriesHelper(int leaderboardPage, bool isInitialRequest, int direction);
int Service_GetMinimumRank();
int Service_GetMaximumRank();
void Service_ReadyLeaderboard(const LeaderboardEntry* entries, size_t entries_len);
const LeaderboardRequestData* Service_GetLeaderboardRequestData();

//Supposed to be public
typedef enum ServiceLeaderboardSendStatus
{
	SERVICE_LEADERBOARD_SEND_STATUS_NOTHING = 0,
	SERVICE_LEADERBOARD_SEND_STATUS_SENDING = 1,
	SERVICE_LEADERBOARD_SEND_STATUS_SENT = 2,
	SERVICE_LEADERBOARD_SEND_STATUS_FAILED = 3
} ServiceLeaderboardSendStatus;

typedef enum ServiceLeaderboardScope
{
	SERVICE_LEADERBOARD_SCOPE_GLOBAL = 0,
	SERVICE_LEADERBOARD_SCOPE_USER = 1,
	SERVICE_LEADERBOARD_SCOPE_FRIENDS = 2
} ServiceLeaderboardScope;

typedef enum ServiceLeaderboardQueueState
{
	SERVICE_LEADERBOARD_QUEUE_STATE_NOTHING = 0,
	SERVICE_LEADERBOARD_QUEUE_STATE_NEW_REQUEST = 1,
	SERVICE_LEADERBOARD_QUEUE_STATE_NEXT_PAGE = 2
} ServiceLeaderboardQueueState;

void Service_ResetLeaderboardRequestStuff();
void Service_SetSilenceLeaderboardSendStatusNotification(bool value);
void Service_FlushStatsToServiceForXbox();
void Service_SetLeaderboardAmountOfRowsToRetrieve(int range);
bool Service_IsSimplifiedLeaderboard();
bool Service_IsShowingLeaderboardCannotConnectError();
void Service_DisableLeaderboards();
bool Service_AreLeaderboardDisabled();
void Service_UpdateScoreKeepBest(const char* leaderboard, int score, bool isAscending, bool isMilliseconds);
void Service_RetrieveLeaderboardEntries(const char* leaderboard, int scopeType, bool isAscending, bool isMilliseconds);
int Service_CheckLeaderboardSendStatus(bool update);
void Service_SimulateSendingLeaderboardStatus(int frames, int status);
bool Service_IsLeaderboardRetrievalInProgress();
LeaderboardEntry* Service_GetLeaderboardEntries();
LeaderboardEntry Service_GetLeaderboardEntry(int i);
bool Service_IsLeaderboardReady();
int64_t Service_GetLeaderboardEntryCount();
int Service_GetCurrentHighestRank();
int Service_GetCurrentLowestRank();
bool Service_IsLeaderboardNullOrEmpty();
bool Service_CanLeaderboardGoLeft();
bool Service_CanLeaderboardGoRight();
void Service_LeaderboardGoRight();
void Service_LeaderboardGoLeft();
double Service_GetPlatformLeaderboardDelayTime();
bool Service_PlatformDoesNotAllowLeaderboardScrollingForFriendScope();
void Service_TurnOffLeaderboardCannotConnectError();
bool Service_LeaveTheLeaderboardMenuRightNow();
void Service_TellServiceIfOnLeaderboardMenuRightNow(bool isOnLeaderboardMenuRightNow);
bool Service_IsOnLeaderboardMenuRightNow();