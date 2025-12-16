#include "Pause.h"

void Pause_Init(Pause* p, int time, int point)
{
	p->_mPoint = point;
	p->_mIsComplete = false;
	p->_mTimer = Timer_Create(time);
}

void Pause_Update(Pause* p)
{
	if (Timer_Update(&p->_mTimer))
	{
		p->_mIsComplete = true;
	}
}
bool Pause_IsComplete(const Pause* p)
{
	return p->_mIsComplete;
}
bool Pause_IsAtPoint(const Pause* p, int value)
{
	if (value == p->_mPoint)
	{
		return true;
	}
	return false;
}
