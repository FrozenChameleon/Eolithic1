/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "WaveFileData.h"
#include "SoundState.h"

typedef struct SoundEffectInstance
{
	uint64_t _mFramePlayed;
	int _mLoopNumber;
	bool _mIsSetup;
	bool _mIsDynamic;
	//OeSoundEffectInstanceDynamic _mDynamicInstance;
	const char* _mName;
} SoundEffectInstance;

bool SoundEffectInstance_Setup(const char* name, WaveFileData* waveFileData);
bool SoundEffectInstance_IsSetup();
int SoundEffectInstance_GetLoopNumber();
void SoundEffectInstance_SetLoopNumber(int value);
const char* SoundEffectInstance_GetName();
uint64_t SoundEffectInstance_GetFramePlayed();
void SoundEffectInstance_Resume();
float SoundEffectInstance_GetVolume();
void SoundEffectInstance_SetVolume(float value);
SoundState SoundEffectInstance_State();
bool SoundEffectInstance_IsLooped();
void SoundEffectInstance_SetIsLooped(bool value);
void SoundEffectInstance_Play();
void SoundEffectInstance_Pause();
void SoundEffectInstance_Stop();
void SoundEffectInstance_Update(bool isMusic);