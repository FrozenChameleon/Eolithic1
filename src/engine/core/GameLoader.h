/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

#pragma once

#include "stdbool.h"

typedef struct SpriteBatch SpriteBatch;

void GameLoader_Update(double delta);
void GameLoader_Draw(SpriteBatch* spriteBatch);
bool GameLoader_IsLoading(void);