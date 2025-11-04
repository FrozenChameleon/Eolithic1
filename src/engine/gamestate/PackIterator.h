#pragma once

#include "../utils/Macros.h"

typedef struct PackIterator
{
	Entity mEntity;
	void* mComponent;
	int32_t mIndex;
	int32_t mSeekPosition;
} PackIterator;

extern const PackIterator PackIterator_Begin;