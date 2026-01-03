#pragma once

#include "Body.h"
#include "../systems/SystemSimple.h"

void BodySys_InitRoutine(Entity owner, Body* data);
System* BodySys_CreateSystem(void);