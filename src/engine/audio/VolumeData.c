/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#ifndef AUDIO_DUMMY

#include "VolumeData.h"

#include "../io/File.h"
#include "../utils/Utils.h"
#include "../utils/IStringMap.h"
#include "../../third_party/stb_ds.h"
#include "../io/BufferReader.h"

void VolumeData_Init(VolumeData* vd, bool isMusic)
{
	Utils_memset(vd, 0, sizeof(VolumeData));

	vd->_mIsMusic = isMusic;
	sh_new_arena(vd->sh_volume_map);
}

int32_t VolumeData_GetVolume(VolumeData* vd, const char* name)
{
	int64_t loc = shgeti(vd->sh_volume_map, name);
	if (loc < 0)
	{
		return 100;
	}
	else
	{
		return vd->sh_volume_map[loc].value;
	}
}
/*void VolumeData_SetVolume(VolumeData* vd, const char* name, int32_t volume)
{
	shput(vd->sh_volume_map, name, volume);
}*/
void VolumeData_Load(VolumeData* vd)
{
	MString* path = NULL;
	if (vd->_mIsMusic)
	{
		File_PathCombine2(&path, "data", "musicvolume.bin");
	}
	else
	{
		File_PathCombine2(&path, "data", "sfxvolume.bin");
	}

	if (File_Exists(MString_GetText(path)))
	{
		BufferReader* br = BufferReader_CreateFromPath(MString_GetText(path));
		int32_t count = BufferReader_ReadI32(br);
		for (int32_t i = 0; i < count; i += 1)
		{
			MString* key = NULL;
			BufferReader_ReadMString(&key, br);
			int32_t volume = BufferReader_ReadI32(br);
			shput(vd->sh_volume_map, MString_GetText(key), volume);
		}
		BufferReader_Dispose(br);
	}

	MString_Dispose(&path);
}

#endif