/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ShaderProgram.h"
#include "../utils/Utils.h"

ShaderProgram* ShaderProgram_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	return NULL;
}

void ShaderProgram_Dispose(ShaderProgram* sp)
{
	Utils_free(sp);
}
