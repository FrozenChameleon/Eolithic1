#pragma once

#include "../utils/Macros.h"

typedef struct PlaySound
{
	int _mPoint;
	char _mSound[EE_FILENAME_MAX];
} PlaySound;

void PlaySound_Init(PlaySound* ps, int point, const char* sound);
void PlaySound_PlayTheSoundIfAtPoint(const PlaySound* ps, int value);