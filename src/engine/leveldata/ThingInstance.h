/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "../math/Point.h"
#include "../utils/StringPair.h"

typedef struct ThingInstance
{
	char mName[EE_FILENAME_MAX];
	Point* mDynamicNodes;
	StringPair* mDynamicSettings;
} ThingInstance;

