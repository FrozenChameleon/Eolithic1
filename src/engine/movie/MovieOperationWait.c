#include "MovieOperationWait.h"

#include "../utils/Utils.h"
#include "MovieGlobals.h"

void MovieOperationWait_Init(MovieOperationWait* wait, int32_t timeLimit)
{
	Utils_memset(wait, 0, sizeof(MovieOperationWait));

	wait->mType = MOVIE_OPERATION_TYPE_WAIT;
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
