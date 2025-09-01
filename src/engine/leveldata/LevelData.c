/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "LevelData.h"
#include "../utils/Utils.h"

LevelData* LevelData_FromStream(BufferReader* br)
{
	return NULL;
}
void LevelData_Dispose(LevelData* ld)
{
	Utils_free(ld);
}
