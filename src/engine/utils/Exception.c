/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Exception.h"

#include "assert.h"
#include "Logger.h"
#include "SDL3/SDL.h"
#include "../core/Window.h"

int32_t Exception_Run(const char* message, bool exitTheGameNow)
{
	Logger_LogError(message);
	assert(0);
	if (exitTheGameNow)
	{
		SDL_ShowSimpleMessageBox(0, "Fatal Exception!", message, Window_GetWindowContext());
		exit(1);
	}
	return 1;
}
