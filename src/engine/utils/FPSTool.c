/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "FPSTool.h"

bool FPSTool_Update(FPSTool* data, double delta)
{
	data->mTime += delta;
	data->mFrames += 1;
	if (data->mTime >= 1)
	{
		data->mCurrentFps = data->mFrames;
		data->mFrames = 0;
		data->mTime -= 1;
		return true;
	}
	return false;
}
