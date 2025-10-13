#include "SysResetFloatyMovementData.h"

#include "../utils/Utils.h"

void SysResetFloatyMovementData_UpdateRoutine(Entity owner, FloatyMovementData* data)
{
	if (!data->mWasUsed)
	{
		Utils_memset(data, 0, sizeof(FloatyMovementData));
	}
	data->mWasUsed = false;
}

System* SysResetFloatyMovementData_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_FloatyMovementData);
	ss->_mUpdateRoutine = SysResetFloatyMovementData_UpdateRoutine;
	return SystemSimple_CreateSystem(ss);
}