#include "PlaySound.h"

#include "../utils/Utils.h"
#include "../core/Func.h"

void PlaySound_PlayTheSoundIfAtPoint(const PlaySound* ps, int value)
{
	if (value == ps->mPoint)
	{
		Do_PlaySound(ps->mSound);
	}
}
