#pragma once

#include "System.h"

void GlobalSysDrawFPS_SetOffsetFromCorner(int32_t offset);
void GlobalSysDrawFPS_SetFont(const char* font);
void GlobalSysDrawFPS_DoNotDrawThisRightNow();
System* GlobalSysDrawFPS_CreateSystem();