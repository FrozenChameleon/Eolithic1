/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "../math/Point.h"
#include "../utils/StringPair.h"
#include "../utils/FixedChar260.h"

typedef struct ThingInstance
{
	FixedChar260 mName;
	Point* mDynamicNodes;
	StringPair* mDynamicSettings;
} ThingInstance;

