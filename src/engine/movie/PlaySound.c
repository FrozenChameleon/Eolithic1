/* Eolithic1
 * Copyright 2025-2026 Patrick Derosby
 * Released under the zlib License.
 * See eolithic1.LICENSE for details.
 */

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
