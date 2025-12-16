#include "MovieOperationWait.h"

#include "../utils/Utils.h"

void MovieOperationWait_Init(MovieOperationWait* wait, int timeLimit)
{
	Utils_memset(wait, 0, sizeof(MovieOperationWait));

	wait->mIsComplete = false;
	wait->mTimerWait = Timer_Create(timeLimit);
}

void MovieOperationWait_SpeedUp(MovieOperationWait* wait)
{
	wait->mTimerWait.mCurrent = wait->mTimerWait.mLimit;
}
void MovieOperationWait_Update(MovieOperationWait* wait)
{
	if (Timer_Update(&wait->mTimerWait))
	{
		wait->mIsComplete = true;
	}
}
bool MovieOperationWait_ForcesWait(MovieOperationWait* wait)
{
	return true;
}
