#pragma once

#include "../utils/Timer.h"

typedef struct Pause
{
	int _mPoint;
	bool _mIsComplete;
	Timer _mTimer;
} Pause;

void Pause_Init(Pause* p, int time, int point);

void Pause_Update(Pause* p);
bool Pause_IsComplete(const Pause* p);
bool Pause_IsAtPoint(const Pause* p, int value);