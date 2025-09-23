#pragma once

#include "../math/Rectangle.h"

typedef struct FreezeEntityTillOnScreen
{
	Rectangle mRectangle;
	bool mFacesPlayer;
	bool mIsFacingFlipped;
} FreezeEntityTillOnScreen;

