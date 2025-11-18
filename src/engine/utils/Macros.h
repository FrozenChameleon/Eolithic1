/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"

#define EE_SAFE_BUFFER_LENGTH_FOR_INT 20
#define EE_SAFE_BUFFER_LENGTH_FOR_FLOAT 50
#define EE_SAFE_BUFFER_LENGTH_FOR_DOUBLE 100
#define EE_PATH_MAX 260
#define EE_FILENAME_MAX 255
#define EE_STR_NOT_SET "NOT_SET"
#define EE_STR_EMPTY ""
#define ENTITY_NOTHING 0

typedef int32_t Entity;
typedef int32_t ResourceID;
typedef const char* IString;