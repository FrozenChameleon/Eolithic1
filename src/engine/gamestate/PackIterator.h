#pragma once

#include "../utils/Macros.h"

typedef struct PackIterator
{
	Entity mEntity;
	int32_t mIndex;
	int32_t mSeekPosition;
} PackIterator;

extern const PackIterator PackIterator_Begin;