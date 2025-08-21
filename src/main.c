/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#define STB_DS_IMPLEMENTATION
#include "third_party/stb_ds.h"

#include "engine/core/Game.h"
#include "engine/io/File.h"
#include "engine/io/BufferReader.h"
#include "engine/utils/Utils.h"
#include "engine/io/INIFile.h"
#include "engine/utils/Cvars.h"
#include "engine/utils/Logger.h"

#include "engine/io/DatReader.h"

int main(int argc, char* args[])
{
	FixedChar260* sharedStringBuffer = Utils_GetSharedStringBuffer();
	File_Combine2(sharedStringBuffer->mValue, UTILS_SHARED_STRING_BUFFER_LENGTH, "data", "engineconfig.bin");
	Cvars_Read(sharedStringBuffer->mValue);
	File_Combine2(sharedStringBuffer->mValue, EE_PATH_MAX, "data", "userconfig.bin");
	Cvars_Read(sharedStringBuffer->mValue);
	File_Combine2(sharedStringBuffer->mValue, EE_PATH_MAX, "data", "animtile.dat");
	DatReader* dr = DatReader_Create(sharedStringBuffer->mValue);
	FixedChar260 temp = { 0 };
	while (DatReader_HasNext(dr))
	{
		DatReader_NextFilePath(dr, &temp);
		BufferReader* br = DatReader_NextStream(dr, false);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	int64_t cvarsLength = Cvars_Length();
	uint64_t mallocRefs = Utils_GetMallocRefs();
	Game_Run();
	return 0;
}