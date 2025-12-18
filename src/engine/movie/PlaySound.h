#pragma once

#include "../utils/Macros.h"

typedef struct PlaySound
{
	bool mIsLoaded;
	int32_t mPoint;
	char mSound[EE_FILENAME_MAX];
} PlaySound;

void PlaySound_PlayTheSoundIfAtPoint(const PlaySound* ps, int value);