/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#define STB_DS_IMPLEMENTATION
#include "engine/third_party/stb_ds.h"

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
	char pathBuffer[EE_PATH_MAX];
	File_Combine2(pathBuffer, EE_PATH_MAX, "data", "engineconfig.bin");
	Cvars_Read(pathBuffer);
	File_Combine2(pathBuffer, EE_PATH_MAX, "data", "userconfig.bin");
	Cvars_Read(pathBuffer);
	File_Combine2(pathBuffer, EE_PATH_MAX, "data", "animtile.dat");
	DatReader* datReader = DatReader_Create(pathBuffer);
	FixedChar260 temp = DatReader_NextFilePath(datReader);
	int64_t cvarsLength = Cvars_Length();
	uint64_t mallocRefs = Utils_GetMallocRefs();
	Game_Run();
	return 0;
}