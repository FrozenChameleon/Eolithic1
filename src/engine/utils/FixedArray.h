#pragma once

#include "stdint.h"

typedef struct FixedArray
{
	uint8_t* data;
	int32_t len;
} FixedArray;

