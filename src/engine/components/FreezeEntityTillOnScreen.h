#pragma once

#include "../math/Rectangle.h"

struct FreezeEntityTillOnScreen
{
	Rectangle mRectangle;
	bool mFacesPlayer;
	bool mIsFacingFlipped;
};

