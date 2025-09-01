/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "SoundEffect.h"
#include "../utils/Utils.h"

SoundEffect* SoundEffect_FromStream(BufferReader* br)
{
	SoundEffect* sfx = Utils_malloc(sizeof(SoundEffect));
	sfx->_mWaveFileData = WaveFileData_FromStream(br);;
	return sfx;
}

void SoundEffect_Dispose(SoundEffect* music)
{
	WaveFileData_Dispose(music->_mWaveFileData);
	music->_mWaveFileData = NULL;

	Utils_free(music);
}
