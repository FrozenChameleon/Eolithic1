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
#include "engine/core/Window.h"
#include "engine/resources/TextureManager.h"
#include "engine/resources/TextureOffsetManager.h"
#include "engine/utils/IStrings.h"
#include "engine/gamestate/ComponentPack.h"
#include "engine/gamestate/GameStateData.h"

int main(int argc, char* args[])
{
	SharedFixedChar260* path = Utils_CreateSharedFixedChar260();
	File_Combine2(path, "data", "engineconfig.bin");
	Cvars_Read(path);
	File_Combine2(path, "data", "userconfig.bin");
	Cvars_Read(path);
	Utils_DisposeSharedFixedChar260(path);

	Game_Init();

	AnimTileManager_LoadAllFromDat();
	MusicManager_LoadAllFromDat();
	SoundEffectManager_LoadAllFromDat();
	TextureManager_LoadAllFromDat();
	TextureOffsetManager_LoadAllFromDat();
	Sheet_BuildSheets();
	//MusicManager_DisposeAll();
	//SoundEffectManager_LoadAllFromDat();
	//SoundEffectManager_DisposeAll();
	//Utils_FreeAllSharedFixedChar260();

	int32_t sharedFixedCharInUse = Utils_GetAmountOfSharedFixedChar260InUse();
	int64_t cvarsLength = Cvars_Length();
	uint64_t mallocRefs = Utils_GetMallocRefs();

	IStringArray* strings = Utils_SplitString("hello,,hello,", 260, ',');
	int strlen = IStringArray_Length(strings);
	for (int i = 0; i < strlen; i += 1)
	{
		const char* strrr = IStringArray_Get(strings, i);
		int hello = 0;
	}
	IStringArray_Dispose(strings);

	size_t globalLen = IStrings_GlobalLength();

	GameStateData* gsd = Utils_malloc(sizeof(GameStateData));
	GameStateData_Ctor(gsd);

	ComponentPack* genericPack = GameStateData_GetComponentPack(gsd, C_Camera);
	for (int i = 0; i < 100; i += 1)
	{
		Entity entityNumber = (i + 1);
		ComponentPack_Set(genericPack, entityNumber);
		Camera* cam = ComponentPack_GetComponent(genericPack, entityNumber);
		cam->mHingeGateLeft = i;
		cam->mHingeGateRight = i * 2;
		int loc = ComponentPack_GetEntityLocation(genericPack, entityNumber);
		int tester = 0;
	}

	for (int i = 0; i < 100; i += 1)
	{
		Entity entityNumber = (i + 1);
		Camera* cam = ComponentPack_GetComponent(genericPack, entityNumber);
		cam->mHingeGateLeft = i;
		cam->mHingeGateRight = i * 2;
		int loc = ComponentPack_GetEntityLocation(genericPack, entityNumber);
	}

	Game_Run();

	return 0;
}