#pragma once

#include "stdbool.h"

void Strings_Init();
const char* Strings_Get(const char* key);
void Strings_Add(const char* key, const char* val);
void Strings_AddDoNotReplace(const char* key, const char* val, bool doNotReplace);
bool Strings_Contains(const char* key);