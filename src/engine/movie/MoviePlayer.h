#pragma once

#include "../math/Vector2.h"
#include "MovieImage.h"

void MoviePlayer_Init(bool useSwappedImages, int32_t scale, const char* movieName);

void MoviePlayer_DisableSpeedUp(void);
void MoviePlayer_SetComplete(void);
bool MoviePlayer_IsComplete(void);
void MoviePlayer_Update(void);
void MoviePlayer_Update2(bool doNotAllowMovieSkip);
void MoviePlayer_DrawHud(SpriteBatch* spriteBatch);