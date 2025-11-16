/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "ImageDataInstance.h"

#include "../utils/Utils.h"
#include "../utils/MString.h"

void ImageDataInstance_Init(ImageDataInstance* idi, ImageData* data)
{
	Utils_memset(idi, 0, sizeof(ImageDataInstance));

	idi->mData = data;

	if (data->mCanAnimate)
	{
		idi->mSheet = Sheet_GetDefaultSheet();
		Animation_Init(&idi->mAnimation, MString_GetText(data->mImage), data->mFlipSpeed);
		idi->mAnimation.mIsLoopingDisabled = data->mAnimationStops;
		if (data->mAnimationBlanks)
		{
			idi->mAnimation.mIsLoopingDisabled = true;
		}
		idi->mAnimation.mAnimationLoopPoint = data->mAnimationLoopPoint;
	}
	else
	{
		idi->mSheet = Sheet_GetSheet(MString_GetText(data->mImage));
		Utils_memset(&idi->mAnimation, 0, sizeof(Animation));
	}

	idi->mIsOriginSet = ImageData_IsOriginSet(data);
}
