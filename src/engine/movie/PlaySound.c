#include "PlaySound.h"

#include "../utils/Utils.h"
#include "../core/Func.h"

void PlaySound_Init(PlaySound* ps, int point, const char* sound)
{
	Utils_memset(ps, 0, sizeof(PlaySound));

	ps->_mPoint = point;
	Utils_strlcpy(ps->_mSound, sound, EE_FILENAME_MAX);
}
void PlaySound_PlayTheSoundIfAtPoint(const PlaySound* ps, int value)
{
	if (value == ps->_mPoint)
	{
		Do_PlaySound(ps->_mSound);
	}
}
