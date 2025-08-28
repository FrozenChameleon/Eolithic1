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

const const char* Music_GetExtension();
const const char* Music_GetDirectories();
void Music_SetMusicMuted(bool value);
bool Music_DoNotAllowUpdatesWhilePaused();
void Music_SetDoNotAllowUpdatesWhilePaused(bool value);
VolumeData* Music_GetVolumeData();
void Music_PauseMusic(int priority);
void Music_ResumeMusic(int priority);
void Music_RestartMusic();
void Music_PlayPreviousTrack();
void Music_PlayMusic(const char* nextTrack, bool isLooping, bool isForced);
void Music_PlayMusic(const char* nextTrack, bool isLooping, bool isForced, bool isFadeIn, int fadeInTime, bool isFadeOut, int fadeOutTime);
void Music_StopMusic();
void Music_FadeOutMusic(int fadeOutTime);
void Music_Tick();
float Music_GetVolumeForMusic(const char* name);
bool Music_IsPlaying();
Music* Music_FromStream(BufferReader* br);