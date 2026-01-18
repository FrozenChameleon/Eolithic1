/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

int32_t ButtonList_GetButton(int32_t index);
const int32_t* ButtonList_GetArray();
int32_t ButtonList_GetArrayLength();