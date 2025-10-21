#pragma once

#include "stdbool.h"

typedef struct SpriteBatch SpriteBatch;

void GameLoader_Update(double delta);
void GameLoader_Draw(SpriteBatch* spriteBatch);
bool GameLoader_IsLoading();