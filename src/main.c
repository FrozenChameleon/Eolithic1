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
#include "engine/resources/MusicManager.h"
#include "engine/resources/SoundEffectManager.h"
#include "engine/audio/Music.h"
#include "engine/audio/SoundEffectInstance.h"
#include "engine/io/DatReader.h"

int main(int argc, char* args[])
{
	SharedFixedChar260* path = Utils_GetSharedFixedChar260();
	File_Combine2(path, "data", "engineconfig.bin");
	Cvars_Read(path);
	File_Combine2(path, "data", "userconfig.bin");
	Cvars_Read(path);
	path->mIsInUse = false;

	MusicManager_LoadAllFromDat();
	SoundEffectManager_LoadAllFromDat();

	//MusicManager_DisposeAll();
	//SoundEffectManager_LoadAllFromDat();
	//SoundEffectManager_DisposeAll();
	//Utils_FreeAllSharedFixedChar260();

	int32_t sharedFixedCharInUse = Utils_GetAmountOfSharedFixedChar260InUse();
	int64_t cvarsLength = Cvars_Length();
	uint64_t mallocRefs = Utils_GetMallocRefs();

	Game_Run();

	return 0;
}