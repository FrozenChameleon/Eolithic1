#pragma once

#include "../systems/SystemSimple.h"
#include "HitFlashKit.h"

void HitFlashKitSys_InitRoutine(Entity owner, HitFlashKit* data);
void HitFlashKitSys_UpdateRoutine(Entity owner, HitFlashKit* data);

System* HitFlashKitSys_CreateSystem();