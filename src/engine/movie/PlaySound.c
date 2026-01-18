#include "PlaySound.h"

#include "../utils/Utils.h"
#include "../core/Func.h"

void PlaySound_PlayTheSoundIfAtPoint(const PlaySound* ps, int32_t value)
{
	if (value == ps->mPoint)
	{
		Do_PlaySound(ps->mSound);
	}
}
