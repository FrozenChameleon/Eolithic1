/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "SoundEffect.h"
#include "../utils/Macros.h"
#include "SoundEffectInstance.h"
#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "VolumeData.h"
#include "../globals/Globals.h"
#include "../core/GameUpdater.h"
#include "../utils/Logger.h"
#include "../resources/SoundEffectManager.h"

#define SFX_INSTANCE_LIMIT 128

typedef struct SoundEffectPlaybackTimeBuffer
{
	const char* mName;
	uint64_t mTime;
} SoundEffectPlaybackTimeBuffer;

static uint64_t DEFAULT_SOUND_PLAYBACK_TIME_BUFFER = 2;

static int32_t _mSoundPausePriority = -1;
static SoundEffectInstance _mInstances[SFX_INSTANCE_LIMIT];
static bool _mLoopStatus[SFX_INSTANCE_LIMIT];
static uint64_t _mCurrentFrame;
static VolumeData _mVolumeData;
static bool _mIsSfxMuted;
static SoundEffectPlaybackTimeBuffer* _mDynamicSoundEffectPlaybackTimeBuffer;

static float GetVolumeForSoundEffect(const char* sound)
{
	if (_mIsSfxMuted)
	{
		return 0;
	}

	return 1.0f;
	//return OeSoundEffect::GetVolumeHelper(OeCvars::USER_VOLUME_SFX, sound, &_mVolumeData);
}
static uint64_t GetPlaybackTimeBufferForSoundEffect(const char* name)
{
	int32_t len = arrlen(_mDynamicSoundEffectPlaybackTimeBuffer);
	for (int i = 0; i < len; i += 1)
	{
		SoundEffectPlaybackTimeBuffer* temp = &_mDynamicSoundEffectPlaybackTimeBuffer[i];
		if (temp->mName == name)
		{
			return temp->mTime;
		}
	}

	return DEFAULT_SOUND_PLAYBACK_TIME_BUFFER;
}
static bool IsRewinding()
{
	//if (OeGameStateManager::ActiveGameState()->IsRewinding())
	//{
	//	return true;
	//}
	return false;
}
static uint64_t GetLastFramePlayed(const char* sound)
{
	uint64_t highest = 0;
	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (Utils_StringEqualTo(sound, SoundEffectInstance_GetName(instance)))
		{
			if (SoundEffectInstance_GetFramePlayed(instance) > highest)
			{
				highest = SoundEffectInstance_GetFramePlayed(instance);
			}
		}
	}
	return highest;
}
static bool RefreshLoopStatus(const char* sound, int loopNumber)
{
	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (Utils_StringEqualTo(sound, SoundEffectInstance_GetName(instance)))
		{
			if (SoundEffectInstance_GetLoopNumber(instance) == loopNumber)
			{
				_mLoopStatus[i] = true;
				return true;
			}
		}
	}
	return false;
}
static bool IsDisabledPermanently()
{
	return Globals_IsAudioDisabledPermanently();
}

SoundEffect* SoundEffect_FromStream(BufferReader* br)
{
	SoundEffect* sfx = Utils_malloc(sizeof(SoundEffect));
	sfx->_mWaveFileData = WaveFileData_FromStream(br);;
	return sfx;
}
void SoundEffect_Dispose(SoundEffect* music)
{
	WaveFileData_Dispose(music->_mWaveFileData);
	music->_mWaveFileData = NULL;

	Utils_free(music);
}
uint64_t SoundEffect_GetDefaultSoundPlaybackTimeBuffer()
{
	return DEFAULT_SOUND_PLAYBACK_TIME_BUFFER;
}
void SoundEffect_SetDefaultSoundPlaybackTimeBuffer(uint64_t value)
{
	DEFAULT_SOUND_PLAYBACK_TIME_BUFFER = value;
}
void SoundEffect_SetPlaybackTimeBufferForSoundEffect(const char* name, uint64_t time)
{
	int32_t len = arrlen(_mDynamicSoundEffectPlaybackTimeBuffer);
	for (int i = 0; i < len; i += 1)
	{
		SoundEffectPlaybackTimeBuffer* temp = &_mDynamicSoundEffectPlaybackTimeBuffer[i];
		if (temp->mName == name)
		{
			temp->mTime = time;
			return;
		}
	}

	SoundEffectPlaybackTimeBuffer newBuffer = { 0 };
	newBuffer.mName = name;
	newBuffer.mTime = time;
	arrput(_mDynamicSoundEffectPlaybackTimeBuffer, newBuffer);
}
void SoundEffect_SetSfxMuted(bool value)
{
	_mIsSfxMuted = value;
}
uint64_t SoundEffect_GetCurrentFrame()
{
	return _mCurrentFrame;
}
VolumeData* SoundEffect_GetVolumeData()
{
	return &_mVolumeData;
}
void SoundEffect_Tick()
{
	if (IsDisabledPermanently())
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (!_mLoopStatus[i])
		{
			if (SoundEffectInstance_IsLooped(instance))
			{
				SoundEffectInstance_Stop(instance);
			}
		}
		_mLoopStatus[i] = false;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		SoundEffectInstance_Update(instance);
		SoundEffectInstance_SetVolume(instance, GetVolumeForSoundEffect(SoundEffectInstance_GetName(instance)));
	}

	_mCurrentFrame++;
}
void SoundEffect_PauseAllSounds(int priority)
{
	if (IsDisabledPermanently() || IsRewinding() || priority <= _mSoundPausePriority)
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance_Pause(&_mInstances[i]);
	}

	_mSoundPausePriority = priority;
}
void SoundEffect_ResumeAllSounds(int priority)
{
	if (IsDisabledPermanently() || IsRewinding() || priority < _mSoundPausePriority)
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance_Resume(&_mInstances[i]);
	}
	_mSoundPausePriority = -1;
}
void SoundEffect_StopAllPausedSounds()
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (SoundEffectInstance_State(instance) == SOUNDSTATE_PAUSED)
		{
			SoundEffectInstance_Stop(instance);
		}
	}
}
void SoundEffect_StopSound(const char* sound)
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (Utils_StringEqualTo(sound, SoundEffectInstance_GetName(instance)))
		{
			SoundEffectInstance_Stop(instance);
		}
	}
}
void SoundEffect_StopAllSounds()
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance_Stop(&_mInstances[i]);
	}
	_mSoundPausePriority = -1;
}
void SoundEffect_PlaySound(const char* sound)
{
	SoundEffect_PlaySoundWithForcedVolume(sound, -1);
}
static SoundEffectInstance* SetupNextInstance(const char* sound)
{
	SoundEffect* data = SoundEffectManager_GetResourceData(sound);
	if (data == NULL)
	{
		return NULL;
	}

	for (int i = 0; i < SFX_INSTANCE_LIMIT; i += 1)
	{
		SoundEffectInstance* instance = &_mInstances[i];
		if (!SoundEffectInstance_IsSetup(instance) || (SoundEffectInstance_State(instance) == SOUNDSTATE_STOPPED))
		{
			bool success = SoundEffectInstance_Setup(instance, sound, data->_mWaveFileData);
			if (!success)
			{
				Logger_printf("Unable to setup sound effect %s", sound);
				return NULL;
			}
			else
			{
				SoundEffectInstance_Update(instance);
				return instance;
			}
		}
	}

	Logger_LogWarning("Reached sound effect instance limit");
	return NULL;
}
void SoundEffect_PlaySoundWithForcedVolume(const char* sound, float forcedVolume)
{
	if (IsDisabledPermanently() || IsRewinding() || GameUpdater_IsDebugAutoSpeedOn())
	{
		return;
	}

	uint64_t lastFramePlayed = GetLastFramePlayed(sound);
	uint64_t buffer = GetPlaybackTimeBufferForSoundEffect(sound);
	if (_mCurrentFrame <= lastFramePlayed + buffer)
	{
		return;
	}

	SoundEffectInstance* instance = SetupNextInstance(sound);
	if (instance == NULL)
	{
		//reached limit
		return;
	}

	SoundEffectInstance_SetVolume(instance, forcedVolume != -1 ? forcedVolume : GetVolumeForSoundEffect(sound));
	SoundEffectInstance_Update(instance);
	SoundEffectInstance_Play(instance);
}
void SoundEffect_LoopSound(const char* sound, int loopNumber)
{
	if (IsDisabledPermanently() || IsRewinding())
	{
		return;
	}

	if (RefreshLoopStatus(sound, loopNumber))
	{
		return;
	}

	SoundEffectInstance* instance = SetupNextInstance(sound);
	if (instance == NULL)
	{
		//reached limit
		return;
	}

	SoundEffectInstance_SetLoopNumber(instance, loopNumber);
	SoundEffectInstance_SetVolume(instance, GetVolumeForSoundEffect(sound));
	SoundEffectInstance_SetIsLooped(instance, true);
	SoundEffectInstance_Play(instance);

	RefreshLoopStatus(sound, loopNumber);
}
float SoundEffect_GetVolumeHelper(const char* cvar, const char* name, VolumeData* volumeData)
{
	if (IsDisabledPermanently() || (Utils_StringEqualTo(name, EE_STR_NOTHING)))
	{
		return 0;
	}

	return 1.0f;
	//float userVolume = Cvars_GetAsInt(cvar) / 100.0f;
	//float userVolumeMaster = Cvars::GetAsInt(OeCvars::USER_VOLUME_MASTER) / 100.0f;
	//float clipVolume = volumeData->GetVolume(name) / 100.0f;
	//float rewindingVolume = 1.0f;
	//if (OeGameStateManager::ActiveGameState()->IsRewinding())
	//{
	//	rewindingVolume = 0.6f;
	//}
	//return clipVolume * userVolume * userVolumeMaster * rewindingVolume;
}
const char* SoundEffect_GetExtension()
{
	return ".wav";
}
const char* SoundEffect_GetDirectories()
{
	return NULL;
}