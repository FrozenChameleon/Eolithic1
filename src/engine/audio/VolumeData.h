/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

typedef struct VolumeData
{
	struct { char* key; int32_t value; } _mVolumeMap;
	bool _mIsMusic;
} VolumeData;

void VolumeData_Init(VolumeData* vd, bool isMusic);
const char* VolumeData_GetFilePath(VolumeData* vd, bool isBinary);
void VolumeData_SaveHelper(VolumeData* vd, bool isBinary);
int VolumeData_GetVolume(VolumeData* vd, const char* name);
void VolumeData_SetVolume(VolumeData* vd, const char* name, int volume);
void VolumeData_Save(VolumeData* vd);
void VolumeData_Load(VolumeData* vd);