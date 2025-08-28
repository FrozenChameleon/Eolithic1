/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

 /* Derived from code by Ethan Lee (Copyright 2009-2024).
  * Released under the Microsoft Public License.
  * See fna.LICENSE for details.

  * Derived from code by the Mono.Xna Team (Copyright 2006).
  * Released under the MIT License.
  * See monoxna.LICENSE for details.
  */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "WaveFileData.h"
#include "AudioChannels.h"
#include "SoundState.h"

typedef struct SoundEffectInstance
{
	uint64_t _mFramePlayed;
	int _mLoopNumber;
	bool _mHasInit;
	int _mCurrentSample;
	bool _mIsMusic;
	bool _mIsLooped;
	uint8_t* _mBuffer;
	int _mBufferLength;
	WaveFileData* _mData;
	const char* _mName;
	bool _mIsDisposed;
	int _mSampleRate;
	AudioChannels _mChannels;
	SoundState _mInternalState;
	float _mInternalVolume;
	bool _mHasStarted;
	uint8_t** _mDynamicQueuedBuffers;
	uint32_t* _mDynamicQueuedSizes;
	void* _mHandleStorage;
	void* _mFormatStorage;
} SoundEffectInstance;

bool SoundEffectInstance_Init(SoundEffectInstance* sei, const char* name, WaveFileData* waveFileData);
bool SoundEffectInstance_HasInit(const SoundEffectInstance* sei);
int32_t SoundEffectInstance_GetLoopNumber(const SoundEffectInstance* sei);
void SoundEffectInstance_SetLoopNumber(SoundEffectInstance* sei, int value);
const char* SoundEffectInstance_GetName(const SoundEffectInstance* sei);
uint64_t SoundEffectInstance_GetFramePlayed(const SoundEffectInstance* sei);
void SoundEffectInstance_Resume(SoundEffectInstance* sei);
float SoundEffectInstance_GetVolume(const SoundEffectInstance* sei);
void SoundEffectInstance_SetVolume(SoundEffectInstance* sei, float value);
SoundState SoundEffectInstance_State(const SoundEffectInstance* sei);
bool SoundEffectInstance_IsLooped(const SoundEffectInstance* sei);
void SoundEffectInstance_SetIsLooped(SoundEffectInstance* sei, bool value);
void SoundEffectInstance_Play(SoundEffectInstance* sei);
void SoundEffectInstance_Pause(SoundEffectInstance* sei);
void SoundEffectInstance_Stop(SoundEffectInstance* sei, bool immediate);
void SoundEffectInstance_Update(SoundEffectInstance* sei);
void SoundEffectInstance_Dispose(SoundEffectInstance* sei);
void SoundEffectInstance_QueueInitialBuffers(SoundEffectInstance* sei);
void SoundEffectInstance_ClearBuffers(SoundEffectInstance* sei);
void SoundEffectInstance_FillBuffer(SoundEffectInstance* sei, bool isReverse, int amountOfSamples);
void SoundEffectInstance_SubmitBuffer(SoundEffectInstance* sei, uint8_t* buffer, int32_t bufferLength);
int32_t SoundEffectInstance_GetSampleSize(const SoundEffectInstance* sei);
int32_t SoundEffectInstance_GetTotalSamples(const SoundEffectInstance* sei);
int32_t SoundEffectInstance_PendingBufferCount(const SoundEffectInstance* sei);
int32_t SoundEffectInstance_InitAudio();