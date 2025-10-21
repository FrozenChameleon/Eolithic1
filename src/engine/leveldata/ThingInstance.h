/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "../utils/Macros.h"
#include "../math/Point.h"
#include "../utils/StringPair.h"
#include "../utils/MString.h"

typedef struct ThingInstance
{
	MString* mName;
	Point* mDynamicNodes;
	StringPair* mDynamicSettings;
} ThingInstance;

