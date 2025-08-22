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
#include "engine/resources/AnimTileManager.h"
#include "engine/io/DatReader.h"

int main(int argc, char* args[])
{
	SharedFixedChar260* sharedStringBufferForPath = Utils_GetSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileName = Utils_GetSharedFixedChar260();
	SharedFixedChar260* sharedStringBufferForFileNameWithoutExtension = Utils_GetSharedFixedChar260();
	File_Combine2(sharedStringBufferForPath, "data", "engineconfig.bin");
	Cvars_Read(sharedStringBufferForPath);
	File_Combine2(sharedStringBufferForPath, "data", "userconfig.bin");
	Cvars_Read(sharedStringBufferForPath);
	File_Combine2(sharedStringBufferForPath, "data", "animtile.dat");
	DatReader* dr = DatReader_Create(sharedStringBufferForPath);
	while (DatReader_HasNext(dr))
	{
		DatReader_NextFilePath(dr, sharedStringBufferForPath);
		File_GetFileName(sharedStringBufferForFileName, sharedStringBufferForPath);
		File_GetFileNameWithoutExtension(sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader* br = DatReader_NextStream(dr, false);
		AnimTileManager_LoadAssetFromStreamAndCreateResource(br, sharedStringBufferForFileNameWithoutExtension, sharedStringBufferForPath);
		BufferReader_Dispose(br, false);
	}
	DatReader_Dispose(dr);
	sharedStringBufferForPath->mIsInUse = false;
	sharedStringBufferForFileName->mIsInUse = false;
	sharedStringBufferForFileNameWithoutExtension->mIsInUse = false;
	int32_t sharedFixedCharInUse = Utils_GetAmountOfSharedFixedChar260InUse();
	int64_t cvarsLength = Cvars_Length();
	uint64_t mallocRefs = Utils_GetMallocRefs();
	Game_Run();
	return 0;
}