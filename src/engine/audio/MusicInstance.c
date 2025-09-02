/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "MusicInstance.h"
#include "../utils/Timer.h"
#include "../utils/Utils.h"
#include "../resources/MusicManager.h"
#include "Music.h"
#include "../utils/Macros.h"

void MusicInstance_HandleFadeIn(MusicInstance* mi, float musicVolume)
{
	float fadeInVol = Timer_GetPercentage(&mi->_mFadeTimer) * musicVolume;
	SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, fadeInVol);
	if (Timer_Update(&mi->_mFadeTimer))
	{
		mi->_mState = STATE_WORKING;
		SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, musicVolume);
	}
}
void MusicInstance_HandleFadeOut(MusicInstance* mi, float musicVolume)
{
	float fadeOutVal = (1 - Timer_GetPercentage(&mi->_mFadeTimer)) * musicVolume;
	SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, fadeOutVal);
	if (Timer_Update(&mi->_mFadeTimer))
	{
		MusicInstance_Stop(mi);
		if (Utils_StringEqualTo(mi->_mNextTrack, EE_STR_NOTHING))
		{
			if (mi->_mWillFadeIn)
			{
				mi->_mFadeTimer.mLimit = mi->_mWillFadeInTime;
				mi->_mWillFadeIn = false;
				mi->_mWillFadeInTime = 0;
				SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, 0);
				
			}
			else
			{
				SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, musicVolume);
			}
			mi->_mCurrentTrack = mi->_mNextTrack;
			mi->_mNextTrack = EE_STR_NOTHING;
			MusicInstance_Play(mi, mi->_mCurrentTrack, true, mi->_mWillFadeIn, 0);
			if (mi->_mWillFadeIn)
			{
				mi->_mState = STATE_FADE_IN;
			}
			else
			{
				mi->_mState = STATE_WORKING;
			}
		}
		else
		{
			mi->_mState = STATE_COMPLETE;
		}
	}
}

void MusicInstance_Init(MusicInstance* mi)
{
	Utils_memset(mi, 0, sizeof(MusicInstance));
	Timer_Init(&mi->_mFadeTimer, 180);
	mi->_mPreviousTrack = EE_STR_NOTHING;
	mi->_mCurrentTrack = EE_STR_NOTHING;
	mi->_mNextTrack = EE_STR_NOTHING;
}

bool MusicInstance_IsLooped(MusicInstance* mi)
{
	return SoundEffectInstance_IsLooped(&mi->_mCurrentMusicInstance);
}
void MusicInstance_SetIsLooped(MusicInstance* mi, bool value)
{
	SoundEffectInstance_SetIsLooped(&mi->_mCurrentMusicInstance, value);
}
const char* MusicInstance_CurrentTrack(MusicInstance* mi)
{
	return mi->_mCurrentTrack;
}
const char* MusicInstance_PreviousTrack(MusicInstance* mi)
{
	return mi->_mPreviousTrack;
}
void MusicInstance_Play(MusicInstance* mi, const char* nextTrack, bool isLooping, bool isUsingForcedVolume, float forcedVolume)
{
	mi->_mPreviousTrack = mi->_mCurrentTrack;
	if (Utils_StringEqualTo(mi->_mPreviousTrack, EE_STR_NOTHING))
	{
		mi->_mPreviousTrack = nextTrack;
	}

	mi->_mCurrentTrack = nextTrack;
	if (Utils_StringEqualTo(mi->_mCurrentTrack, EE_STR_NOTHING))
	{
		return;
	}

	MusicInstance_Stop(mi);

	Music* data = MusicManager_GetResourceData(mi->_mCurrentTrack);
	bool success = SoundEffectInstance_Setup(&mi->_mCurrentMusicInstance, nextTrack, data->_mWaveFileData);
	if (!success)
	{
		return;
	}

	SoundEffectInstance_SetIsLooped(&mi->_mCurrentMusicInstance, isLooping);
	if (isUsingForcedVolume)
	{
		SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, forcedVolume);
	}
	else
	{
		SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, MusicInstance_GetMusicVolume(mi));
	}
	SoundEffectInstance_Play(&mi->_mCurrentMusicInstance);

	mi->_mState = STATE_WORKING;
}
float MusicInstance_GetMusicVolume(MusicInstance* mi)
{
	return Music_GetVolumeForMusic(mi->_mCurrentTrack);
}
void MusicInstance_Stop(MusicInstance* mi)
{
	SoundEffectInstance_Stop(&mi->_mCurrentMusicInstance);
}
void MusicInstance_Pause(MusicInstance* mi)
{
	if (SoundEffectInstance_State(&mi->_mCurrentMusicInstance) == SOUNDSTATE_PLAYING)
	{
		SoundEffectInstance_Pause(&mi->_mCurrentMusicInstance);
		mi->_mPaused = true;
	}
}
void MusicInstance_Resume(MusicInstance* mi)
{
	if (!mi->_mPaused)
	{
		return;
	}

	if (SoundEffectInstance_State(&mi->_mCurrentMusicInstance) == SOUNDSTATE_PAUSED)
	{
		SoundEffectInstance_Resume(&mi->_mCurrentMusicInstance);
		mi->_mPaused = false;
	}
}
void MusicInstance_Update(MusicInstance* mi)
{
	float musicVolume = MusicInstance_GetMusicVolume(mi);
	switch (mi->_mState)
	{
	case STATE_FADE_IN:
		MusicInstance_HandleFadeIn(mi, musicVolume);
		break;
	case STATE_WORKING:
		SoundEffectInstance_SetVolume(&mi->_mCurrentMusicInstance, musicVolume);
		break;
	case STATE_FADE_OUT:
		MusicInstance_HandleFadeOut(mi, musicVolume);
		break;
	}

	SoundEffectInstance_Update(&mi->_mCurrentMusicInstance);
}
void MusicInstance_SetupQueuedFadeIn(MusicInstance* mi, int fadeInTime)
{
	mi->_mWillFadeIn = true;
	mi->_mWillFadeInTime = fadeInTime;
}
void MusicInstance_SetupFadeIn(MusicInstance* mi, int fadeInTime)
{
	Timer_Reset(&mi->_mFadeTimer);
	mi->_mState = STATE_FADE_IN;
	mi->_mFadeTimer.mLimit = fadeInTime;
}
void MusicInstance_SetupFadeOut(MusicInstance* mi, const char* nextTrack, int fadeOutTime)
{
	Timer_Reset(&mi->_mFadeTimer);
	mi->_mNextTrack = nextTrack;
	mi->_mState = STATE_FADE_OUT;
	mi->_mFadeTimer.mLimit = fadeOutTime;
}
bool MusicInstance_IsFadingOut(MusicInstance* mi)
{
	return (mi->_mState == STATE_FADE_OUT);
}
void MusicInstance_ClearTrackNames(MusicInstance* mi)
{
	mi->_mPreviousTrack = EE_STR_NOTHING;
	mi->_mCurrentTrack = EE_STR_NOTHING;
	mi->_mNextTrack = EE_STR_NOTHING;
}
bool MusicInstance_IsPlaying(MusicInstance* mi)
{
	return (SoundEffectInstance_State(&mi->_mCurrentMusicInstance) == SOUNDSTATE_PLAYING);
}