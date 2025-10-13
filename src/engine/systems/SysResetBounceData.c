#include "SysResetBounceData.h"

#include "../utils/Utils.h"

void SysResetBounceData_UpdateRoutine(Entity owner, BounceData* data)
{
	if (!data->mWasUsed)
	{
		Utils_memset(data, 0, sizeof(BounceData));
	}
	data->mWasUsed = false;
}

System* SysResetBounceData_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_BounceData);
	ss->_mUpdateRoutine = SysResetBounceData_UpdateRoutine;
	return SystemSimple_CreateSystem(ss);
}
