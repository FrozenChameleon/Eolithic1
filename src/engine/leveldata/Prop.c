/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Prop.h"
#include "../utils/Utils.h"

Prop* Prop_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	return NULL;
}

void Prop_Dispose(Prop* prop)
{
	Utils_free(prop);
}
