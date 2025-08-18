/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "Macros.h"

typedef struct Timer
{
	int32_t mCurrent;
	int32_t mLimit;
} Timer;

void Timer_Init(Timer* timer, int limit);
float Timer_GetPercentage(const Timer* timer);
float Timer_GetInversePercentage(const Timer* timer);
int Timer_GetRemainingTime(const Timer* timer);
bool Timer_UpdateWithTuningLimit(Timer* timer, Entity entity, const char* tuning);
bool Timer_UpdateWithLimit(Timer* timer, int limit);
bool Timer_Update(Timer* timer);
void Timer_Reset(Timer* timer);
bool Timer_IsAtPercentage(const Timer* timer, float percent);
void Timer_SetToTwoFourthsOfLimit(Timer* timer);
void Timer_SetToThreeFourthsOfLimit(Timer* timer);
void Timer_SetToOneFourthsOfLimit(Timer* timer);
void Timer_SetToLimit(Timer* timer);
void Timer_SetAsPercentOfLimit(Timer* timer, float percent);
void Timer_InverseCurrent(Timer* timer);
Timer Timer_Zero();
