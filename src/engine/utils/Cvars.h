/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "CvarNames.h"
#include "stdint.h"
#include "stdbool.h"

void Cvars_FlipAsBool(const char* key);
void Cvars_SetAsBool(const char* key, bool value);
void Cvars_SetAsInt(const char* key, int value);
void Cvars_SetAsFloat(const char* key, float value);
void Cvars_Set(const char* key, const char* value);
const char* Cvars_Get(const char* key);
float Cvars_GetAsFloat(const char* key);
int Cvars_GetAsInt(const char* key);
bool Cvars_GetAsBool(const char* key);
void Cvars_Read(const char* path);
int64_t Cvars_Length();
void Cvars_SaveUserConfig();