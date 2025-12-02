/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "VolumeData.h"

#include "../utils/Utils.h"
#include "../io/File.h"
#include "../io/INIFile.h"

const char* VolumeData_GetFilePath(VolumeData* vd, bool isBinary)
{
	return NULL;/*
	std_string extension = OeUtils_GetExtension(isBinary);
	if (_mIsMusic)
	{
		return OeFile_Combine("data", "musicvolume" + extension);
	}
	else
	{
		return OeFile_Combine("data", "sfxvolume" + extension);
	}*/
}
void VolumeData_SaveHelper(VolumeData* vd, bool isBinary)
{
	//WILLNOTDO 05152023
	/*
	using (OeIniWriter writer = new OeIniWriter(GetFilePath(isBinary)))
	{
	writer.WriteDictionaryStringInt(_mVolumeMap);
	}
	*/
}

void VolumeData_Init(VolumeData* vd, bool isMusic)
{
	Utils_memset(vd, 0, sizeof(VolumeData));

	vd->_mIsMusic = isMusic;
}

int VolumeData_GetVolume(VolumeData* vd, const char* name)
{
	return 0;
	/*
	if (!_mVolumeMap.count(name))
	{
		return 100;
	}
	else
	{
		return _mVolumeMap[name];
	}
	*/
}
void VolumeData_SetVolume(VolumeData* vd, const char* name, int32_t volume)
{
	//_mVolumeMap[name] = volume;
}
void VolumeData_Save(VolumeData* vd)
{
	//WILLNOTDO 05152023
	//SaveHelper(true);
	//SaveHelper(false);
}
void VolumeData_Load(VolumeData* vd)
{
	/*
	std_string filePath = GetFilePath(OeUtils_IsBinaryForDebugFlag());
	if (OeFile_FileExists(filePath))
	{
		std_shared_ptr<OeIniReader> reader = OeIniReader_CreateNewOeIniReader(filePath);
		_mVolumeMap = reader->ReadAsStringIntDictionary();
	}
	else
	{
		Save();
	}
	*/
}

