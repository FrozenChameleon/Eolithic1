#pragma once

#include "../math/Vector2.h"
#include "../utils/IStringArray.h"
#include "../utils/MString.h"

typedef struct SpriteBatch SpriteBatch;

typedef struct RecordingPlayerData
{
	bool mBool0;
	bool mBool1;
	bool mBool2;
	bool mBool3;
	bool mBool4;
	bool mBool5;
	bool mBool6;
	bool mBool7;
	bool mBool8;
	bool mBool9;
	bool mBool10;
	bool mBool11;
	bool mBool12;
	bool mBool13;
	bool mBool14;
	bool mBool15;
	Vector2 mLeftAxis;
	Vector2 mRightAxis;
	float mLeftTrigger;
	float mRightTrigger;
} RecordingPlayerData;

typedef struct RecordingData
{
	bool mIsInUse;
	RecordingPlayerData mPlayerOne;
	RecordingPlayerData mPlayerTwo;
	RecordingPlayerData mPlayerThree;
	RecordingPlayerData mPlayerFour;
} RecordingData;

typedef struct PerMapReaderData
{
	int mLowestFps;
	int mPlayerReadCounter;
	int mReaderFailsafe;
	bool mWasSessionSuccessCounterTicked;
	bool mIsAtEndOfRecording;
} PerMapReaderData;

typedef struct ReaderData
{
	PerMapReaderData mPerLevelData;
	int mSessionCounter;
	bool mIsReadyForNext;
	const char* mCurrentRecording;
	IStringArray* mRecordings;
} ReaderData;

typedef struct HeaderData
{
	MString* mLevelFileName;
	int mAmountOfPlayers;
	int mBoolLength;
	bool mUseLeftAxis;
	bool mUseRightAxis;
	bool mUseLeftTrigger;
	bool mUseRightTrigger;
	int mSuccessNumber;
	int mRecordingVersion;
} HeaderData;

enum FromArguments
{
	RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_OFF = 0,
	RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_SOAK_NORMAL = 1,
	RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_SOAK_FAST = 2,
	RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_SESSION_NORMAL = 3,
	RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_SESSION_FAST = 4
};

const char* RecordingTool_GetCurrentRecordingName();
bool RecordingTool_IsFromArgumentsPlaybackEnabled();
void RecordingTool_EnableFromArgumentsPlayback(int state);
bool RecordingTool_IsDisplayingSessionReadout();
void RecordingTool_DrawReadSessionReadout(SpriteBatch* spriteBatch, const char* font);
void RecordingTool_CheckForDebugReadSessionCode();
bool RecordingTool_IsWriting();
bool RecordingTool_IsReading();
RecordingPlayerData* RecordingTool_Get(int amountOfPlayers, int32_t playerNumber, int32_t boolLength, bool useLeftAxis, bool useRightAxis, bool useLeftTrigger, bool useRightTrigger);
int RecordingTool_GetPlayerReadCounter();
void RecordingTool_SetPlayerReadCounter(int value);
bool RecordingTool_IsRunning();
void RecordingTool_SetupWriteSession(int priority, const char* mapToLoad);
bool RecordingTool_LoadNextRecordingIfAtEndOfRecording(bool isMapLoad);
void RecordingTool_SetupReadSession(IStringArray* givenRecordings, int32_t priority, bool goFast);
bool RecordingTool_IsGoFastFlagSet();
void RecordingTool_TickReadSessionSuccessCounter(int successNumber);
void RecordingTool_RewriteAllRecordings();
int RecordingTool_GetCurrentRecordingVersion();