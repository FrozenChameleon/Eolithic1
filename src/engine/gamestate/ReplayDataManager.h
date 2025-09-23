#pragma once

#include "../utils/Macros.h"
#include "GameStateInputData.h"
#include "GameStateData.h"
#include "../../GlobalDefs.h"

#define REPLAY_DATA_MANAGER_REPLAY_BUFFER_SIZE GLOBAL_DEF_REPLAY_BUFFER_SIZE
//Real frame once every interval
#define REPLAY_DATA_MANAGER_REPLAY_INTERVAL GLOBAL_DEF_REPLAY_INTERVAL 

typedef struct ReplayDataManager
{
	bool _mIsActive;
	int _mLength;
	uint64_t _mReplayFrames[REPLAY_DATA_MANAGER_REPLAY_BUFFER_SIZE];
	GameStateInputData _mReplayInputData[REPLAY_DATA_MANAGER_REPLAY_BUFFER_SIZE];
	GameStateData* _mReplayGameStateData[REPLAY_DATA_MANAGER_REPLAY_BUFFER_SIZE / REPLAY_DATA_MANAGER_REPLAY_INTERVAL];
	uint64_t _mReplayFrameToGivePlayer;
	uint64_t _mDebugRewindLoopReplayFrame;
} ReplayDataManager;

int ReplayDataManager_GetIndexFromReplayFrame(ReplayDataManager* rdm, uint64_t replayFrame);
int ReplayDataManager_GetIndexForLowestFrame(ReplayDataManager* rdm);
int ReplayDataManager_GetIndexForLowestFrameKeyFrame(ReplayDataManager* rdm, bool mustBeKeyFrame);

void ReplayDataManager_Init(ReplayDataManager* rdm, const char* name);

void ReplayDataManager_RewindLoop(ReplayDataManager* rdm, bool justStarted, GameStateData* actualCurrentGameState);
uint64_t ReplayDataManager_GetLowestReplayFrame(ReplayDataManager* rdm);
void ReplayDataManager_RewindToSnapshot(ReplayDataManager* rdm, uint64_t replayFrameToRewindTo, GameStateData* actualCurrentGameState);
void ReplayDataManager_Snapshot(ReplayDataManager* rdm, uint64_t currentReplayFrame, GameStateData* actualCurrentGameState);
void ReplayDataManager_GiveReplayInput(ReplayDataManager* rdm, uint64_t currentReplayFrame, const GameStateInputData* replayInputData);
const GameStateInputData* ReplayDataManager_GetReplayInput(ReplayDataManager* rdm);
void ReplayDataManager_Clear(ReplayDataManager* rdm);