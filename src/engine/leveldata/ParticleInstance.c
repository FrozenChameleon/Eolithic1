/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ParticleInstance.h"

static ParticleInstance _mDummy;
const static ParticleInstance _mEmpty = { 0 };

ParticleInstance* ParticleInstance_Dummy(void)
{
	return &_mDummy;
}
const ParticleInstance* ParticleInstance_Empty(void)
{
	return &_mEmpty;
}
