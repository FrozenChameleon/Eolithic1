#pragma once

#include "../utils/Macros.h"

typedef struct Body Body;

bool Is_UpdateDisabled(Entity entity);
bool Is_DrawDisabled(Entity entity);
Body* Get_Body(Entity entity);