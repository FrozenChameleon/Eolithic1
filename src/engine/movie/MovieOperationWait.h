#pragma once

#include "MovieGlobals.h"
#include "../utils/Timer.h"

typedef struct MovieOperationWait
{
	MOVIE_OPERATION_HEADER
	Timer mTimerWait;
} MovieOperationWait;

void MovieOperationWait_Init(MovieOperationWait* wait, int timeLimit);

void MovieOperationWait_SpeedUp(MovieOperationWait* wait);
void MovieOperationWait_Update(MovieOperationWait* wait);
bool MovieOperationWait_ForcesWait(MovieOperationWait* wait);