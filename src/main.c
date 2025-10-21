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
#include "engine/utils/MString.h"

int main(int argc, char* args[])
{
	MString* enginePath = File_Combine2("data", "engineconfig.bin");
	Cvars_Read(enginePath->text);
	MString_Dispose(enginePath);

	MString* userPath = File_Combine2("data", "userconfig.bin");
	Cvars_Read(userPath->text);
	MString_Dispose(userPath);

	Game_Run();

	return 0;
}