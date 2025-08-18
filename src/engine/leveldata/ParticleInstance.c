/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ParticleInstance.h"

static ParticleInstance _mDummy;
const static ParticleInstance _mEmpty;

ParticleInstance* ParticleInstance_Dummy()
{
	return &_mDummy;
}
const ParticleInstance* ParticleInstance_Empty()
{
	return &_mEmpty;
}
