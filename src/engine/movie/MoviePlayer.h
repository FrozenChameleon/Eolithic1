#pragma once

#include "../math/Vector2.h"
#include "MovieOperation.h"
#include "MovieImage.h"

typedef struct NewMovieTextData
{
	char mFont[EE_FILENAME_MAX];
	Vector2 mPosition;
	int mSpeed;
	int mRate;
	int mWait;
	char mColor[EE_FILENAME_MAX];
	int mFadeRampSpeed;
	int mFadeHoldTime;
	bool mIsCentered;
} NewMovieTextData;

typedef struct MovieTextData
{
	char mFont[EE_FILENAME_MAX];
	Vector2 mPosition;
	int mSpeed;
	int mRate;
} MovieTextData;

typedef struct MovieFadeTextData
{
	char mFont[EE_FILENAME_MAX];
	Vector2 mPosition;
	int mRampSpeed;
	int mHoldTime;
} MovieFadeTextData;

typedef struct MoviePlayer
{
	int _mFrameCounter;
	int _mScale;
	int _mSkipPoint;
	int _mCounter;
	bool _mIsStarted;
	bool _mIsEnded;
	bool _mIsBlocking;
	bool _mIsWaiting;
	bool _mIsSkipping;
	bool _mIsComplete;
	bool _mDisableSpeedUp;
	bool _mUseSwappedImages;
	char _mNextSwappedImage[EE_FILENAME_MAX];
	bool _mShowFrameTimer;
	char _mMovieName[EE_FILENAME_MAX];
	int _mCurrentTiming;
	int32_t* _mTimingsToUse;
	int32_t* _mTimingsToWrite;
	bool _mUseStrictTiming;
	NewMovieTextData _mTextData;
	NewMovieTextData _mNextTextData;
	int _mReaderLoc;
	//std::vector<std::string> _mReader;
	//std::vector<std::shared_ptr<OeMovieOperation>> _mOperations;
	//std::unordered_map<std::string, std::shared_ptr<OeMovieImage>> _mImages;
} MoviePlayer;

void MoviePlayer_WriteTimings(MoviePlayer* mp);
void MoviePlayer_AddOperation(MoviePlayer* mp, const char* operation, IStringArray* arguments);
void MoviePlayer_OperationSwapNextImage(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetNextTextColor(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationRemove(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationGoTo(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationPan(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationClear(MoviePlayer* mp);
void MoviePlayer_OperationPlaySound(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationPlayMusic(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationFadeOutMusic(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationAddImage(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationAddScreen(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationNewText(MoviePlayer* mp, const char* operation, IStringArray* arguments);
void MoviePlayer_OperationNewFadeText(MoviePlayer* mp, const char* operation, IStringArray* arguments);
const char* MoviePlayer_GetCurrentTextColor(MoviePlayer* mp);
void MoviePlayer_OperationSetTextFont(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextPosition(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextSpeed(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextRate(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextWait(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextFadeRampSpeed(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextFadeHoldTime(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationSetTextColor(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationRemoveScreen(MoviePlayer* mp);
void MoviePlayer_OperationAddAnimation(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationWait(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationStopShake(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationShake(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationText(MoviePlayer* mp, const char* operation, IStringArray* arguments);
void MoviePlayer_OperationGiveTime(MoviePlayer* mp);
MovieTextData MoviePlayer_GetTextData(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_OperationFadeText(MoviePlayer* mp, const char* operation, IStringArray* arguments);
MovieFadeTextData MoviePlayer_GetFadeTextData(MoviePlayer* mp, IStringArray* arguments);
void MoviePlayer_Broadcast(MoviePlayer* mp, const char* key, const char* value);

void MoviePlayer_Init(MoviePlayer* mp, bool useSwappedImages, int scale, const char* movieName);

void MoviePlayer_DisableSpeedUp(MoviePlayer* mp);
void MoviePlayer_SetComplete(MoviePlayer* mp);
bool MoviePlayer_IsComplete(MoviePlayer* mp);
void MoviePlayer_Update(MoviePlayer* mp);
void MoviePlayer_Update2(MoviePlayer* mp, bool doNotAllowMovieSkip);
void MoviePlayer_DrawHud(MoviePlayer* mp, SpriteBatch* spriteBatch);