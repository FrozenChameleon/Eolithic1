#pragma once

#include "SpecialMcFinalBossEffect.h"
#include "../systems/SystemSimple.h"

void SpecialMcFinalBossEffectSys_Create(Vector2 position, const char* animationName, Vector2 bloodOffset, bool disableShaking, 
	int32_t bloodCutoff, int32_t forcedDirection);

System* SpecialMcFinalBossEffectSys_CreateSystem(void);