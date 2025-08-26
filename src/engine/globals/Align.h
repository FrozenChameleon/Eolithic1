/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

enum TextAlignment 
{ 
	ALIGN_LEFT = 0, 
	ALIGN_TOP = 0,
	ALIGN_CENTER = 1,
	ALIGN_RIGHT = 2,
	ALIGN_BOTTOM = 2
};

int32_t Align_ToAlign(bool value);