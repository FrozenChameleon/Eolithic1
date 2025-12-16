#pragma once

#include "MovieOperation.h"
#include "../math/Vector2.h"
#include "../utils/Timer.h"
#include "MovieImage.h"

typedef struct MovieOperationPan
{
	int32_t mType;
	bool mIsComplete;
	Vector2 mSpeed;
	Timer mTimerWait;
	MovieImage* mImage;
} MovieOperationPan;

void MovieOperationPan_Init(MovieOperationPan* pan, MovieImage* image, Vector2 speed, int time);
void MovieOperationPan_SpeedUp(MovieOperationPan* pan);
void MovieOperationPan_Update(MovieOperationPan* pan);