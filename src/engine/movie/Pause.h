#pragma once

#include "../utils/Timer.h"

typedef struct Pause
{
	bool mIsComplete;
	bool mIsLoaded;
	int mPoint;
	Timer mTimer;
} Pause;

void Pause_Update(Pause* p);
bool Pause_IsAtPoint(const Pause* p, int value);