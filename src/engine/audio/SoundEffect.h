/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "WaveFileData.h"
#include "VolumeData.h"
#include "../io/BufferReader.h"

typedef struct SoundEffect
{
	WaveFileData* _mWaveFileData;
} SoundEffect;

//extern uint64_t DEFAULT_SOUND_PLAYBACK_TIME_BUFFER;

void SoundEffect_SetPlaybackTimeBufferForSoundEffect(const char* name, uint64_t time);
void SoundEffect_SetSfxMuted(bool value);
uint64_t SoundEffect_GetCurrentFrame();
VolumeData* SoundEffect_GetVolumeData();
void SoundEffect_Tick();
void SoundEffect_PauseAllSounds(int priority);
void SoundEffect_ResumeAllSounds(int priority);
void SoundEffect_StopAllPausedSounds();
void SoundEffect_StopSound(const char* sound);
void SoundEffect_StopAllSounds();
void SoundEffect_PlaySound(const char* sound);
void SoundEffect_PlaySound(const char* sound, float forcedVolume);
void SoundEffect_LoopSound(const char* sound, int loopNumber);
float SoundEffect_GetVolumeHelper(const char* cvar, const char* name, VolumeData* volumeData);
const char* SoundEffect_GetExtension();
const char* SoundEffect_GetDirectories();
SoundEffect* SoundEffect_FromStream(BufferReader* br);
void SoundEffect_Dispose(SoundEffect* music);