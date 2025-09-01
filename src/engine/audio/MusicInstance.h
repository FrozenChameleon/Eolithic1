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

void MusicInstance_HandleFadeIn(MusicInstance* mi, float musicVolume);
void MusicInstance_HandleFadeOut(MusicInstance* mi, float musicVolume);

enum MusicInstanceState
{
	STATE_FADE_IN = 0,
	STATE_WORKING = 1,
	STATE_FADE_OUT = 2,
	STATE_COMPLETE = 3
};

void MusicInstance_Init(MusicInstance* mi);

bool MusicInstance_IsLooped(MusicInstance* mi);
void MusicInstance_SetIsLooped(MusicInstance* mi, bool value);
const char* MusicInstance_CurrentTrack(MusicInstance* mi);
const char* MusicInstance_PreviousTrack(MusicInstance* mi);
void MusicInstance_Play(MusicInstance* mi, const char* nextTrack, bool isLooping, bool isUsingForcedVolume, float forcedVolume);
float MusicInstance_GetMusicVolume(MusicInstance* mi);
void MusicInstance_Stop(MusicInstance* mi);
void MusicInstance_Pause(MusicInstance* mi);
void MusicInstance_Resume(MusicInstance* mi);
void MusicInstance_Update(MusicInstance* mi);
void MusicInstance_SetupQueuedFadeIn(MusicInstance* mi, int fadeInTime);
void MusicInstance_SetupFadeIn(MusicInstance* mi, int fadeInTime);
void MusicInstance_SetupFadeOut(MusicInstance* mi, const char* nextTrack, int fadeOutTime);
bool MusicInstance_IsFadingOut(MusicInstance* mi);
void MusicInstance_ClearTrackNames(MusicInstance* mi);
bool MusicInstance_IsPlaying(MusicInstance* mi);