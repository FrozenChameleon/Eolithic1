#include "SpecialShakeCameraSys.h"

#include "../core/Func.h"
#include "SpecialShakeCameraSys.h"

void SpecialShakeCameraSys_UpdateRoutine(Entity owner, ShakeCamera* data)
{
	Do_ShakeCamera(data->mMinX, data->mMaxX, data->mMinY, data->mMaxY);
	if (Timer_Update(&data->mTimer))
	{
		Do_SetComplete(owner);
	}
}
void SpecialShakeCameraSys_Setup(ShakeCamera* data, int timerLimit, int minX, int maxX, int minY, int maxY)
{
	data->mTimer.mLimit = timerLimit;
	data->mMinX = minX;
	data->mMaxX = maxX;
	data->mMinY = minY;
	data->mMaxY = maxY;
}
void SpecialShakeCameraSys_Create(int timerLimit, int minX, int maxX, int minY, int maxY)
{
	Entity entity = Do_BuildNewEntity("Shake Camera");
	Do_InitComponent(C_ShakeCamera, entity);
	SpecialShakeCameraSys_Setup(Get_Component(C_ShakeCamera, entity), timerLimit, minX, maxX, minY, maxY);
}

System* SpecialShakeCameraSys_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_ShakeCamera);
	ss->_mUpdateRoutine = SpecialShakeCameraSys_UpdateRoutine;
	return SystemSimple_CreateSystem(ss);
}
