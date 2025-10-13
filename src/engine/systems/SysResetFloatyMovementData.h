#pragma once

#include "SystemSimple.h"
#include "../components/FloatyMovementData.h"

System* SysResetFloatyMovementData_CreateSystem();
void SysResetFloatyMovementData_UpdateRoutine(Entity owner, FloatyMovementData* data);