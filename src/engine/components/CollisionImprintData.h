#pragma once

#include "../math/Point.h"

typedef struct CollisionImprintData
{
	Point mPosition;
	int32_t mWidth;
	int32_t mHeight;
	int32_t mType;
} CollisionImprintData;
