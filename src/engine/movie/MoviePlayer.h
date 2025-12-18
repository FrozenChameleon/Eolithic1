#pragma once

#include "../math/Vector2.h"
#include "MovieImage.h"

void MoviePlayer_Init(bool useSwappedImages, int scale, const char* movieName);

void MoviePlayer_DisableSpeedUp();
void MoviePlayer_SetComplete();
bool MoviePlayer_IsComplete();
void MoviePlayer_Update();
void MoviePlayer_Update2(bool doNotAllowMovieSkip);
void MoviePlayer_DrawHud(SpriteBatch* spriteBatch);