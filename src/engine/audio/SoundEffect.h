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

void SetPlaybackTimeBufferForSoundEffect(const char* name, uint64_t time);
void SetSfxMuted(bool value);
uint64_t GetCurrentFrame();
VolumeData* GetVolumeData();
void Tick();
void PauseAllSounds(int priority);
void ResumeAllSounds(int priority);
void StopAllPausedSounds();
void StopSound(const char* sound);
void StopAllSounds();
void PlaySound(const char* sound);
void PlaySound(const char* sound, float forcedVolume);
void LoopSound(const char* sound, int loopNumber);
float GetVolumeHelper(const char* cvar, const char* name, VolumeData* volumeData);
SoundEffect* FromStream(BufferReader* br);
const char* GetExtension();
const char* GetDirectories();