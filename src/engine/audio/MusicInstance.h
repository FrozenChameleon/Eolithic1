/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Timer.h"
#include "SoundEffectInstance.h"

typedef struct MusicInstance
{
	int _mWillFadeInTime;
	int _mState;
	bool _mPaused;
	bool _mWillFadeIn;
	const char* _mPreviousTrack;
	const char* _mCurrentTrack;
	const char* _mNextTrack;
	Timer _mFadeTimer;
	SoundEffectInstance _mCurrentMusicInstance;
} MusicInstance;

void MusicInstance_HandleFadeIn(float musicVolume);
void MusicInstance_HandleFadeOut(float musicVolume);

enum MusicInstanceState
{
	STATE_FADE_IN = 0,
	STATE_WORKING = 1,
	STATE_FADE_OUT = 2,
	STATE_COMPLETE = 3
};

void MusicInstance_Init();

bool MusicInstance_IsLooped();
void MusicInstance_SetIsLooped(bool value);
const char* MusicInstance_CurrentTrack();
const char* MusicInstance_PreviousTrack();
void MusicInstance_Play(const char* nextTrack, bool isLooping, bool isUsingForcedVolume, float forcedVolume);
float MusicInstance_GetMusicVolume();
void MusicInstance_Stop();
void MusicInstance_Pause();
void MusicInstance_Resume();
void MusicInstance_Update();
void MusicInstance_SetupQueuedFadeIn(int fadeInTime);
void MusicInstance_SetupFadeIn(int fadeInTime);
void MusicInstance_SetupFadeOut(const char* nextTrack, int fadeOutTime);
bool MusicInstance_IsFadingOut();
void MusicInstance_ClearTrackNames();
bool MusicInstance_IsPlaying();