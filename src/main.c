/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#define STB_DS_IMPLEMENTATION
#include "third_party/stb_ds.h"

#include "engine/core/Game.h"
#include "engine/utils/Cvars.h"
#include "engine/utils/MString.h"
#include "engine/io/File.h"
#include "engine/globals/Globals.h"
#include "engine/input/RecordingTool.h"

int main(int argc, char* args[])
{
	MString* enginePath = File_Combine2("data", "engineconfig.bin");
	Cvars_Read(MString_GetText(enginePath));
	MString_Dispose(&enginePath);

	MString* userPath = File_Combine2("data", "userconfig.bin");
	Cvars_Read(MString_GetText(userPath));
	MString_Dispose(&userPath);

	//RecordingTool_EnableFromArgumentsPlayback(RECORDINGTOOL_FROM_ARGUMENTS_PLAYBACK_SESSION_NORMAL);
	Globals_TurnOnAutoMode(true);

	Game_Run();

	return 0;
}