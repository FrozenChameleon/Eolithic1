/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "WaveFileData.h"
#include "VolumeData.h"

typedef struct Music
{
	WaveFileData* _mWaveFileData;
} Music;

//extern bool HACK_TO_IGNORE_NEXT_FADE_OUT_MUSIC;

void Music_Init(void);
bool Music_HackToIgnoreNextFadeOutMusic(void);
void Music_SetHackToIgnoreNextFadeOutMusic(bool value);
const char* Music_GetExtension(void);
const char* Music_GetDirectories(void);
void Music_SetMusicMuted(bool value);
bool Music_DoNotAllowUpdatesWhilePaused(void);
void Music_SetDoNotAllowUpdatesWhilePaused(bool value);
VolumeData* Music_GetVolumeData(void);
void Music_PauseMusic(int priority);
void Music_ResumeMusic(int priority);
void Music_RestartMusic(void);
void Music_PlayPreviousTrack(void);
void Music_PlayMusic(const char* nextTrack, bool isLooping, bool isForced, bool isFadeIn, int32_t fadeInTime, bool isFadeOut, int32_t fadeOutTime);
void Music_StopMusic(void);
void Music_FadeOutMusic(int fadeOutTime);
void Music_Tick(void);
float Music_GetVolumeForMusic(const char* name);
bool Music_IsPlaying(void);
Music* Music_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void Music_Dispose(Music* music);