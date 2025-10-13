#pragma once

#include "SystemSimple.h"
#include "../components/BounceData.h"

System* SysResetBounceData_CreateSystem();
void SysResetBounceData_UpdateRoutine(Entity owner, BounceData* data);