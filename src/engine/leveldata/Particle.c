/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Particle.h"
#include "../utils/Utils.h"

Particle* Particle_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	return NULL;
}

void Particle_Dispose(Particle* particle)
{
	Utils_free(particle);
}
