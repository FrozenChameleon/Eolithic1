/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Music.h"

#include "../utils/Utils.h"
#include "VolumeData.h"
#include "MusicInstance.h"
#include "../globals/Globals.h"
#include "../utils/Macros.h"

 //static const std::string MUSIC_EXTENSION = ".wav";
 //static const std::vector<std::string> MUSIC_DIR = { OeFile::Combine("data", "music") };

static VolumeData _mVolumeData;
static MusicInstance _mCurrentMusic;
static int _mMusicPausePriority;
static bool _mDoNotAllowUpdatesWhilePaused;
static bool _mIsMusicMuted;
static bool _mHackToIgnoreNextFadeOutMusic;
static bool _mHasInit;

static bool IsRewinding()
{
	//if (OeGameStateManager::ActiveGameState()->IsRewinding())
	//{
	//	return true;
	//}
	return false;
}
static bool IsDisabledPermanently()
{
	if (!_mHasInit)
	{
		return true;
	}

	return Globals_IsAudioDisabledPermanently();
}

void Music_Init()
{
	if (_mHasInit)
	{
		return;
	}

	MusicInstance_Init(&_mCurrentMusic);

	_mHasInit = true;
}
float Music_GetVolumeForMusic(const char* name)
{
	return 1.0f;
}
bool Music_IsPlaying()
{
	if (IsDisabledPermanently())
	{
		return false;
	}

	MusicInstance_IsPlaying(&_mCurrentMusic);
}
Music* Music_FromStream(BufferReader* br)
{
	Music* music = Utils_malloc(sizeof(Music));
	music->_mWaveFileData = WaveFileData_FromStream(br);
	return music;
}
void Music_Dispose(Music* music)
{
	WaveFileData_Dispose(music->_mWaveFileData);
	music->_mWaveFileData = NULL;

	Utils_free(music);
}
bool Music_HackToIgnoreNextFadeOutMusic()
{
	return _mHackToIgnoreNextFadeOutMusic;
}
void Music_SetHackToIgnoreNextFadeOutMusic(bool value)
{
	_mHackToIgnoreNextFadeOutMusic = value;
}
const char* Music_GetExtension()
{
	return ".wav";
}
const char* Music_GetDirectories()
{
	return NULL;
}
void Music_SetMusicMuted(bool value)
{
	_mIsMusicMuted = value;
}
bool Music_DoNotAllowUpdatesWhilePaused()
{
	return _mDoNotAllowUpdatesWhilePaused;
}
void Music_SetDoNotAllowUpdatesWhilePaused(bool value)
{
	_mDoNotAllowUpdatesWhilePaused = value;
}
VolumeData* Music_GetVolumeData()
{
	return &_mVolumeData;
}
void Music_PauseMusic(int priority)
{
	if (IsDisabledPermanently() || IsRewinding() || (priority <= _mMusicPausePriority))
	{
		return;
	}

	MusicInstance_Pause(&_mCurrentMusic);
	_mMusicPausePriority = priority;
}
void Music_ResumeMusic(int priority)
{
	if (IsDisabledPermanently() || IsRewinding() || (priority < _mMusicPausePriority))
	{
		return;
	}

	MusicInstance_Resume(&_mCurrentMusic);
	_mMusicPausePriority = -1;
}
void Music_RestartMusic()
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	Music_PlayMusic(MusicInstance_CurrentTrack(&_mCurrentMusic), true, true, false, 0, false, 0);
}
void Music_PlayPreviousTrack()
{
	Music_PlayMusic(MusicInstance_PreviousTrack(&_mCurrentMusic), true, true, false, 0, false, 0);
}
void Music_PlayMusic(const char* nextTrack, bool isLooping, bool isForced, bool isFadeIn, int fadeInTime, bool isFadeOut, int fadeOutTime)
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	_mMusicPausePriority = -1;

	if (!isForced)
	{
		if (Utils_StringEqualTo(nextTrack, MusicInstance_CurrentTrack(&_mCurrentMusic)))
		{
			if (!MusicInstance_IsFadingOut(&_mCurrentMusic) && MusicInstance_IsPlaying(&_mCurrentMusic))
			{
				return;
			}
		}
	}

	if (isFadeOut)
	{
		MusicInstance_SetupFadeOut(&_mCurrentMusic, nextTrack, fadeOutTime);
		if (isFadeIn)
		{
			MusicInstance_SetupQueuedFadeIn(&_mCurrentMusic, fadeInTime);
		}
	}
	else
	{
		MusicInstance_Stop(&_mCurrentMusic);
		MusicInstance_Play(&_mCurrentMusic, nextTrack, isLooping, isFadeIn, 0);
		if (IsDisabledPermanently()) //Stop now if this flag is set because of playback
		{
			return;
		}
		if (isFadeIn)
		{
			MusicInstance_SetupFadeIn(&_mCurrentMusic, fadeInTime);
		}
	}
}
void Music_StopMusic()
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	MusicInstance_ClearTrackNames(&_mCurrentMusic);
	MusicInstance_Stop(&_mCurrentMusic);
	_mMusicPausePriority = -1;
}
void Music_FadeOutMusic(int fadeOutTime)
{
	if (_mHackToIgnoreNextFadeOutMusic)
	{
		_mHackToIgnoreNextFadeOutMusic = false;
		return;
	}

	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	MusicInstance_SetupFadeOut(&_mCurrentMusic, EE_STR_NOTHING, fadeOutTime);
}
void Music_Tick()
{
	if (IsDisabledPermanently())
	{
		return;
	}

	MusicInstance_Update(&_mCurrentMusic);
}
