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
	struct { char* key; int32_t value; }* sh_volume_map;
	bool _mIsMusic;
} VolumeData;

void VolumeData_Init(VolumeData* vd, bool isMusic);
int VolumeData_GetVolume(VolumeData* vd, const char* name);
//void VolumeData_SetVolume(VolumeData* vd, const char* name, int32_t volume); //Unused
void VolumeData_Load(VolumeData* vd);