#pragma once

#include "../systems/System.h"
#include "DrawLineOfSight.h"

typedef struct SpriteBatch SpriteBatch;

System* DrawLineOfSightSys_CreateSystem();
//#if EDITOR
void DrawLineOfSightSys_DrawRoutine(Entity owner, DrawLineOfSight* data, SpriteBatch* spriteBatch);
//#endif