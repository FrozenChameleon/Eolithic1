/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Window.h"

#include "../utils/Cvars.h"
#include "SDL3/SDL.h"
#include "../utils/Logger.h"
#include "../globals/Globals.h"
#include "../audio/SoundEffectInstance.h"
#include "../render/Texture.h"
#include "../render/Renderer.h"
#include "../input/ControllerState.h"
#include "Game.h"
#include "../service/Service.h"
#if RENDER_FNA3D
#include <FNA3D.h>
#endif
#include "../../DebugDefs.h"
#include "../io/File.h"
#include "../utils/Utils.h"

static bool _mHasWindowInit;
static bool _mHasLoadedIcon;
static bool _mIsWindowActive;
static SDL_Window* _mWindowContext;

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

	//TODO REMOVE THIS C99
	return SDL_WINDOW_RESIZABLE;

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
	Rectangle returnRect = { 0 };

	Rectangle forcedWindowSize = Service_PlatformGetForcedWindowSize();
	if (!Rectangle_IsEmpty(&forcedWindowSize))
	{
		returnRect.Width = forcedWindowSize.Width;
		returnRect.Height = forcedWindowSize.Height;
		return returnRect;
	}

	int windowSizeWidthFromCvar = Cvars_GetAsInt(CVARS_USER_WINDOW_SIZE_WIDTH);
	int windowSizeHeightFromCvar = Cvars_GetAsInt(CVARS_USER_WINDOW_SIZE_HEIGHT);
	if ((windowSizeWidthFromCvar > 0) && (windowSizeHeightFromCvar > 0)) //Fixed resolutions from CVAR
	{
		returnRect.Width = windowSizeWidthFromCvar;
		returnRect.Height = windowSizeHeightFromCvar;
		return returnRect;
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
		returnRect.Width = Cvars_GetAsInt("internal_render_width") * windowMul;
		returnRect.Height = Cvars_GetAsInt("internal_render_height") * windowMul;
		return returnRect;
	}
}

int Window_Init()
{
	if (_mHasWindowInit)
	{
		Logger_LogWarning("Window has already init");
		return 0;
	}

	_mIsWindowActive = true;

	const char* gameName = Cvars_Get("name");

	uint32_t flags = GetWindowFlagForFullscreen();
	flags = flags | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
#if RENDER_FNA3D
	//SDL_SetHint("FNA3D_FORCE_DRIVER", "OpenGL");
	//SDL_SetHint("FNA3D_OPENGL_FORCE_CORE_PROFILE", "1");
	flags = flags | FNA3D_PrepareWindowAttributes();
#endif

	Rectangle proposedWindowBounds = GetProposedWindowBounds();
	_mWindowContext = SDL_CreateWindow(gameName, proposedWindowBounds.Width, proposedWindowBounds.Height, flags);

	_mHasWindowInit = true;

	if (_mWindowContext == NULL)
	{
		Logger_LogError("Unable to init window!");
		return -1;
	}

	return 0;
}
bool Window_IsFullscreen()
{
	return Cvars_GetAsBool(CVARS_USER_IS_FULLSCREEN);
}
void Window_UpdateFullscreen()
{
	Rectangle proposedWindowBounds = GetProposedWindowBounds();
	SDL_SetWindowSize(_mWindowContext, proposedWindowBounds.Width, proposedWindowBounds.Height);
	SDL_SetWindowFullscreen(_mWindowContext, GetWindowFlagForFullscreen());
}
void Window_SetWindowPositionToCentered()
{
	SDL_SetWindowPosition(_mWindowContext, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
void* Window_GetWindowContext()
{
	return _mWindowContext;
}
void Window_Dispose()
{
	SDL_DestroyWindow(_mWindowContext);
	_mWindowContext = NULL;
}
bool Window_IsTheMouseVisible()
{
	return SDL_CursorVisible();
}
void Window_SetTheMouseVisible(bool isVisible)
{
	if (isVisible)
	{
		SDL_ShowCursor();
	}
	else
	{
		SDL_HideCursor();
	}
}
Rectangle Window_GetWindowSize()
{
	Rectangle rect = Rectangle_Empty;
	SDL_GetWindowSize(_mWindowContext, &rect.Width, &rect.Height);
	return rect;
}
Rectangle Window_GetDisplayBounds()
{
	Rectangle returnRect = { 0 };
	SDL_Rect displayBounds = { 0 };
	int success = SDL_GetDisplayBounds(0, &displayBounds);
	if (success < 0)
	{
		Logger_LogInformation("Unable to get display bounds");
		returnRect.Width = 1280;
		returnRect.Height = 720;
		return returnRect;
	}
	returnRect.X = displayBounds.x;
	returnRect.Y = displayBounds.y;
	returnRect.Width = displayBounds.w;
	returnRect.Height = displayBounds.h;
	return returnRect;
}
void Window_GetAllDisplayModeBounds(Rectangle* displayModeBounds)
{
	//TODO C99
	/*
	displayModeBounds.clear();
	int numDisplayModes = SDL_GetNumDisplayModes(0);
	if (numDisplayModes < 0)
	{
		Logger_LogInformation("Unable to get num display modes");
		return;
	}

	for (int i = 0; i < numDisplayModes; i += 1)
	{
		SDL_DisplayMode displayMode = SDL_DisplayMode();
		SDL_GetDisplayMode(0, i, &displayMode);
		displayModeBounds.push_back(Rectangle(0, 0, displayMode.w, displayMode.h));
	}
	*/
}
bool Window_IsWindowActive()
{
	return _mIsWindowActive;
}
void Window_SetWindowActive(bool value)
{
	_mIsWindowActive = value;
}
void Window_LoadIcon()
{
	if (_mHasLoadedIcon)
	{
		Logger_LogWarning("Window icon has already been loaded");
		return;
	}

	_mHasLoadedIcon = true;

	if (!Service_PlatformShouldLoadWindowIcon())
	{
		Logger_LogWarning("Platform does not load window icon");
		return;
	}

	const char* gameName = Cvars_Get(CVARS_ENGINE_NAME);
	MString* sharedPath = File_Combine2(File_GetBasePath(), gameName);
	MString_AddAssignString(&sharedPath, ".bmp");
	SDL_Surface* icon = SDL_LoadBMP(sharedPath->text);
	MString_Dispose(sharedPath);

	if (icon == NULL)
	{
		Logger_LogWarning("Failed to load window icon");
		return;
	}

	SDL_SetWindowIcon(_mWindowContext, icon);
	SDL_DestroySurface(icon);

	Logger_LogWarning("Successfully loaded window icon");
}