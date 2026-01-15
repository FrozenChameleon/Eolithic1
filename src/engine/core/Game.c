/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

/* Derived from code by Ethan Lee (Copyright 2009-2024).
 * Released under the Microsoft Public License.
 * See fna.LICENSE for details.

 * Derived from code by the Mono.Xna Team (Copyright 2006).
 * Released under the MIT License. 
 * See monoxna.LICENSE for details.
 */

#include "Game.h"

#include "stdio.h"
#include "SDL3/SDL.h"
#include "stdbool.h"
#include "Window.h"
#include "../utils/Stopwatch.h"
#include "../render/Renderer.h"
#include "../input/Input.h"
#include "../audio/SoundEffectInstance.h"
#include "../utils/Exception.h"
#include "../audio/Music.h"
#include "../audio/SoundEffect.h"
#include "../render/Sheet.h"
#include "../core/GameLoader.h"
#include "../service/Service.h"
#include "ServiceHelper.h"
#include "../utils/Cvars.h"
#include "GameUpdater.h"
#include "../globals/Globals.h"
#include "../utils/Utils.h"
#include "../gamestate/GameStateManager.h"
#include "../gamesave/GameSaveManager.h"
#include "../font/FontMap.h"
#include "../input/ControllerState.h"
#include "../utils/Logger.h"
#include "GameHelper.h"
#include "MenuFunc.h"

static const double FIXED_TIME_STEP_TICK = (1.0 / 60.0);
#define MAX_TIME_STEP_FRAMES 4
#define MAX_TIME_STEP ((1.0 / 60.0) * MAX_TIME_STEP_FRAMES)

static bool _mIsFirstPollEvents = true;
//static bool _mWasGuiDrawMissed = false;
//static bool _mHasRunFatalExceptionRoutine = false;
//static bool _mHasRunExitGameRoutine = false;
static bool _mIsExitingGame;
static bool _mHasInit;

static bool IsFixedTimeStep()
{
	if (GameLoader_IsLoading())
	{
		return false;
	}

	if (Service_PlatformForcesRelyOnVsync() || Cvars_GetAsBool(CVARS_ENGINE_RELY_ON_VSYNC))
	{
		return false;
	}

#if EDITOR
	if (Globals_IsDebugGameSpeedSet())
	{
		return false;
	}
	if (GameUpdater_IsDebugAutoSpeedOn())
	{
		return false;
	}
#endif

	return Cvars_GetAsBool(CVARS_USER_IS_FIXED_TIMESTEP_ENABLED);
}

int32_t Game_Init()
{
	if (_mHasInit)
	{
		return 0;
	}

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD))
	{
		return Exception_Run("Unable to init SDL!", false);
	}

	int initStatus = 0;
	initStatus = Window_Init();
	if (initStatus < 0)
	{
		return Exception_Run("Unable to init window!", false);
	}

	initStatus = Renderer_Init(Window_GetWindowContext());
	if (initStatus < 0)
	{
		return Exception_Run("Unable to init platform renderer!", false);
	}
	Renderer_InitSpriteBatch();
	Renderer_ApplyChanges();

	initStatus = SoundEffectInstance_InitAudio();
	if (initStatus < 0)
	{
		return Exception_Run("Unable to init platform renderer!", false);
	}


	//Old "Initialize"
	//WILLNOTDO 06262023
	/*
	OeServiceHelper::Init();
	OeAutoPool.Init();
	OePool.Init();
	OeFunc.Init();
	OeRecordingTool.Init();
	OeTilesetOffset.Init();
	OeMusic.Init();
	*/
	FontMap_Init();
	Input_Init();
	GameStateManager_Ctor();
	GameSaveManager_Init();
	GameHelper_Initialize();
	MenuFunc_Init();
	Music_Init();
	SoundEffect_Init();

	_mHasInit = true;

	return initStatus;
}
int32_t Game_Run()
{
	if (Game_Init() < 0)
	{
		return Exception_Run("Unable to init!", true);
	}

	uint64_t oldTicks = Stopwatch_GetTicks();
	bool isDone = false;
	double deltaLeftover = 0;
	while (!isDone)
	{
		bool isFixedTimeStep = IsFixedTimeStep();
		double delta = deltaLeftover;
		deltaLeftover = 0;
		do
		{
			uint64_t newTicks = Stopwatch_GetTicks();
			delta += Stopwatch_GetElapsedSeconds(oldTicks, newTicks);
			oldTicks = newTicks;
		} while ((delta < FIXED_TIME_STEP_TICK) && isFixedTimeStep);
		if (isFixedTimeStep)
		{
			deltaLeftover = (delta - FIXED_TIME_STEP_TICK);
			delta = FIXED_TIME_STEP_TICK;
		}
		if (delta > MAX_TIME_STEP)
		{
			delta = MAX_TIME_STEP;
		}
		if (deltaLeftover > MAX_TIME_STEP)
		{
			deltaLeftover = MAX_TIME_STEP;
		}
		Game_PollEvents();
		Game_Update(delta);
		if (!Service_SuppressDrawing())
		{
			Game_Draw(delta);
		}
		if (!isDone)
		{
			isDone = Game_IsExitingGame();
		}
	}
	Game_Dispose();
	return 0;
}
void Game_PollEvents() //Derived from FNA
{
	SDL_Event e;
	while (SDL_PollEvent(&e) == 1)
	{
		if (e.type == SDL_EVENT_MOUSE_WHEEL)
		{
			// 120 units per notch. Because reasons.
			//OeMouseState_INTERNAL_SetScrollWheelValue(e.wheel.y * 120);
		}
		if (e.type == SDL_EVENT_GAMEPAD_ADDED)
		{
			ControllerState_AddControllerInstance(e.cdevice.which);
		}
		else if (e.type == SDL_EVENT_GAMEPAD_REMOVED)
		{
			ControllerState_RemoveControllerInstance(e.cdevice.which);
		}
		else if (e.type == SDL_EVENT_WINDOW_FOCUS_GAINED) // Various Window Events...
		{
			//GameWindow_SetWindowActive(true);

			const char* videoDriver = SDL_GetCurrentVideoDriver();
			if (Utils_StringEqualTo(videoDriver, "x11"))
			{
				// If we alt-tab away, we lose the 'fullscreen desktop' flag on some WMs
				//SDL_SetWindowFullscreen((SDL_Window*)(OeWindow_GetWindowContext()),
			//		OeWindow_IsFullscreen() ? SDL_WindowFlags_SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
			}

			// Disable the screensaver when we're back.
			SDL_DisableScreenSaver();
		}
		else if (e.type == SDL_EVENT_WINDOW_FOCUS_LOST)
		{
			//OeWindow_SetWindowActive(false);

			const char* videoDriver = SDL_GetCurrentVideoDriver();
			if (Utils_StringEqualTo(videoDriver, "x11"))
			{
				//SDL_SetWindowFullscreen((SDL_Window*)(OeWindow_GetWindowContext()), 0);
			}

			// Give the screensaver back, we're not that important now.
			SDL_EnableScreenSaver();
		}
		else if (e.type == SDL_EVENT_WINDOW_RESIZED)
		{
			//GameRenderer_ApplyChanges();
		}
		else if (e.type == SDL_EVENT_WINDOW_MOUSE_ENTER)
		{
			SDL_DisableScreenSaver();
		}
		else if (e.type == SDL_EVENT_WINDOW_MOUSE_LEAVE)
		{
			SDL_EnableScreenSaver();
		}
		else if (e.type == SDL_EVENT_QUIT)
		{
			_mIsExitingGame = true;
		}
	}

	_mIsFirstPollEvents = false;
}
bool Game_IsExitingGame()
{
	return _mIsExitingGame;
}
void Game_Exit()
{
	_mIsExitingGame = true;
}
bool Game_IsActive()
{
	//TODO C99
	return true;
}

void Game_Update(double gameTime)
{
	//WILLNOTDO 06262023 (EDITOR)
	/*
#if EDITOR
	if (_mWasGuiDrawMissed)
	{
		OeGui.AfterLayout();
	}
	OeGui.BeforeLayout(gameTime);
	_mWasGuiDrawMissed = true;
#endif
*/

	double delta = gameTime;

	if (!Globals_IsExceptionUnsafe())
	{
		//try
		//{
		Game_UpdateHelper(delta);
		//}
		//catch (...)
		//{
		//HandleFatalException("Fatal exception in update!");
		//}
	}
	else
	{
		Game_UpdateHelper(delta);
	}

	//WILLNOTDO 06262023 2023
	/*
#if EDITOR
	if (OeGui.IsAnythingHovered())
	{
		OeInput.BlockMKBInputForFrames(10);
	}
#endif
*/
}

void Game_Draw(double gameTime)
{
#if EDITOR
	if (Globals_DebugIsRenderDisabled())
	{
		return;
	}
#endif

	double delta = gameTime;

	if (!Globals_IsExceptionUnsafe())
	{
		//try
		//{
		Renderer_Render(delta);
		//}
		//catch (...)
		//{
		//	HandleFatalException("Fatal exception in draw!");
		//}
	}
	else
	{
		Renderer_Render(delta);
	}


#if EDITOR
	//WILLNOTDO 05152023 OeGui.AfterLayout();
	//WILLNOTDO 05152023 _mWasGuiDrawMissed = false;
#endif
}

void Game_UpdateHelper(double delta)
{
	ServiceHelper_Update(delta);

	if (GameLoader_IsLoading())
	{
		GameLoader_Update(delta);
		Renderer_SetupRenderState();
	}

	if (!GameLoader_IsLoading())
	{
		GameUpdater_Update(delta);
	}
}

void Game_Dispose()
{
	Window_Dispose();
	SDL_Quit();
}
