/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Window.h"

#include <SDL3/SDL.h>
#include "../math/Rectangle.h"
#include "../service/Service.h"
#include "../utils/Cvars.h"
#include "../utils/Logger.h"
#if RENDER_FNA3D
#include <FNA3D.h>
#endif

static bool _mHasWindowInit;
static bool _mHasLoadedIcon;
static bool _mIsWindowActive;
static SDL_Window* _mWindowContext = NULL;

static uint32_t GetWindowFlagForFullscreen()
{
	bool useFullscreen = Window_IsFullscreen();

	if (!_mHasWindowInit && Service_PlatformForcesWindowedModeOnBoot())
	{
		useFullscreen = false;
	}

	if (Service_PlatformForcesFullscreen())
	{
		useFullscreen = true;
	}

#ifdef DEBUG_DEF_FORCE_FULLSCREEN_OFF
	useFullscreen = false;
#endif

#ifdef DEBUG_DEF_FORCE_FULLSCREEN_ON
	useFullscreen = true;
#endif

	if (useFullscreen)
	{
		return SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		return SDL_WINDOW_RESIZABLE;
	}
}

static Rectangle GetProposedWindowBounds()
{
	Rectangle forcedWindowSize = Service_PlatformGetForcedWindowSize();
	if (!Rectangle_IsEmpty(&forcedWindowSize))
	{
		Rectangle temp = { 0, 0, forcedWindowSize.Width, forcedWindowSize.Height };
		return temp;
	}

	int windowSizeWidthFromCvar = Cvars_GetAsInt(CVARS_USER_WINDOW_SIZE_WIDTH);
	int windowSizeHeightFromCvar = Cvars_GetAsInt(CVARS_USER_WINDOW_SIZE_HEIGHT);
	if ((windowSizeWidthFromCvar > 0) && (windowSizeHeightFromCvar > 0)) //Fixed resolutions from CVAR
	{
		Rectangle temp = { 0, 0, windowSizeWidthFromCvar, windowSizeHeightFromCvar };
		return temp;
	}
	else //Scaler resolutions from CVAR
	{
		int windowMul = Cvars_GetAsInt("usr_window_size_multiple");
#ifdef DEBUG_DEF_FORCED_WINDOW_MUL
		if (DEBUG_DEF_FORCED_WINDOW_MUL > 0)
		{
			windowMul = DEBUG_DEF_FORCED_WINDOW_MUL;
		}
#endif
		Rectangle temp = { 0, 0, Cvars_GetAsInt("internal_render_width") * windowMul, Cvars_GetAsInt("internal_render_height") * windowMul };
	}
}

int32_t Window_Init()
{
	if (_mHasWindowInit)
	{
		Logger_LogWarning("Window has already init");
		return 0;
	}

	_mIsWindowActive = true;

	const char* gameName = "Hello World!";
	//std::string gameName = Cvars_Get("name");

	SDL_WindowFlags flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
	//uint32_t flags = GetWindowFlagForFullscreen();
	//flags = flags | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
#if RENDER_FNA3D
	//SDL_SetHint("FNA3D_FORCE_DRIVER", "OpenGL");
	//SDL_SetHint("FNA3D_OPENGL_FORCE_CORE_PROFILE", "1");
	flags = flags | FNA3D_PrepareWindowAttributes();
#endif

	//Rectangle proposedWindowBounds = GetProposedWindowBounds();
	Rectangle proposedWindowBounds = { 0, 0, 1440, 810 };
	_mWindowContext = SDL_CreateWindow(gameName, proposedWindowBounds.Width, proposedWindowBounds.Height, flags);

	_mHasWindowInit = true;

	if (_mWindowContext == NULL)
	{
		Logger_LogError("Unable to init window!");
		return -1;
	}

	return 0;
}
void* Window_GetWindowContext()
{
	return _mWindowContext;
}
bool Window_IsWindowActive()
{
	return _mIsWindowActive;
}
void Window_SetWindowActive(bool value)
{
	_mIsWindowActive = value;
}
bool Window_IsFullscreen()
{
	return false;
}
