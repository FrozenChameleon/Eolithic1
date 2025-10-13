#pragma once

#include "../systems/SystemSimple.h"
#include "../components/ShakeCamera.h"

System* SpecialShakeCameraSys_CreateSystem();
void SpecialShakeCameraSys_UpdateRoutine(Entity owner, ShakeCamera* data);
void SpecialShakeCameraSys_Setup(ShakeCamera* data, int timerLimit, int minX, int maxX, int minY, int maxY);
void SpecialShakeCameraSys_Create(int timerLimit, int minX, int maxX, int minY, int maxY);