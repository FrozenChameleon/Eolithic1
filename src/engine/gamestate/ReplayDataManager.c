#include "ReplayDataManager.h"

static GameStateInputData _mDummy;

int ReplayDataManager_GetIndexFromReplayFrame(ReplayDataManager* rdm, uint64_t replayFrame)
{
	return 0;
}
int ReplayDataManager_GetIndexForLowestFrame(ReplayDataManager* rdm)
{
	return 0;
}
int ReplayDataManager_GetIndexForLowestFrameKeyFrame(ReplayDataManager* rdm, bool mustBeKeyFrame)
{
	return 0;
}

void ReplayDataManager_Init(ReplayDataManager* rdm, const char* name)
{

}

void ReplayDataManager_RewindLoop(ReplayDataManager* rdm, bool justStarted, GameStateData* actualCurrentGameState)
{

}
uint64_t ReplayDataManager_GetLowestReplayFrame(ReplayDataManager* rdm)
{
	return 0;
}
void ReplayDataManager_RewindToSnapshot(ReplayDataManager* rdm, uint64_t replayFrameToRewindTo, GameStateData* actualCurrentGameState)
{

}
void ReplayDataManager_Snapshot(ReplayDataManager* rdm, uint64_t currentReplayFrame, GameStateData* actualCurrentGameState)
{

}
void ReplayDataManager_GiveReplayInput(ReplayDataManager* rdm, uint64_t currentReplayFrame, const GameStateInputData* replayInputData)
{

}
const GameStateInputData* ReplayDataManager_GetReplayInput(ReplayDataManager* rdm)
{
	return &_mDummy;
}
void ReplayDataManager_Clear(ReplayDataManager* rdm)
{

}