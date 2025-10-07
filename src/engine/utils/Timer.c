/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Timer.h"

#include "Utils.h"

Timer Timer_Create(int limit)
{
	Timer timer;
	timer.mCurrent = 0;
	timer.mLimit = limit;
	return timer;
}
void Timer_Init(Timer* timer, int limit)
{
	Utils_memset(timer, 0, sizeof(Timer));
	timer->mLimit = limit;
}
float Timer_GetPercentage(const Timer* timer)
{
	float temp1 = timer->mCurrent;
	float temp2 = timer->mLimit;
	return temp1 / temp2;
}
float Timer_GetInversePercentage(const Timer* timer)
{
	return 1.0f - Timer_GetPercentage(timer);
}
int Timer_GetRemainingTime(const Timer* timer)
{
	return timer->mLimit - timer->mCurrent;
}
bool Timer_UpdateWithTuningLimit(Timer* timer, Entity entity, const char* tuning)
{
	return false;
	//WILLNOTDO MCDX 2023return Update(timer, OeFunc.Get_TuningAsInt(entity, tuning));
}
bool Timer_UpdateWithLimit(Timer* timer, int limit)
{
	timer->mLimit = limit;
	return Timer_Update(timer);
}
bool Timer_Update(Timer* timer)
{
	timer->mCurrent++;
	if (timer->mCurrent >= timer->mLimit)
	{
		Timer_Reset(timer);
		return true;
	}
	return false;
}
void Timer_Reset(Timer* timer)
{
	timer->mCurrent = 0;
}
bool Timer_IsAtPercentage(const Timer* timer, float percent)
{
	return false;
	//int goal = OeMath::Round(timer->mLimit * percent);
	//if (timer->mCurrent == goal)
	//{
	//	return true;
	//}
	//return false;
}
void Timer_SetToTwoFourthsOfLimit(Timer* timer)
{
	Timer_SetAsPercentOfLimit(timer, 0.5f);
}
void Timer_SetToThreeFourthsOfLimit(Timer* timer)
{
	Timer_SetAsPercentOfLimit(timer, 0.75f);
}
void Timer_SetToOneFourthsOfLimit(Timer* timer)
{
	Timer_SetAsPercentOfLimit(timer, 0.25f);
}
void Timer_SetToLimit(Timer* timer)
{
	timer->mCurrent = timer->mLimit;
}
void Timer_SetAsPercentOfLimit(Timer* timer, float percent)
{
	timer->mCurrent = (int)(timer->mLimit * percent);
}
void Timer_InverseCurrent(Timer* timer)
{
	timer->mCurrent = timer->mLimit - timer->mCurrent;
}
Timer Timer_Zero()
{
	Timer timer = { 0 };
	return timer;
}
