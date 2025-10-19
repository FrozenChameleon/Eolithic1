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

static const double FIXED_TIME_STEP_TICK = (1.0 / 60.0);
#define MAX_TIME_STEP_FRAMES 4
#define MAX_TIME_STEP ((1.0 / 60.0) * MAX_TIME_STEP_FRAMES)

static bool _mIsFirstPollEvents = true;
//static bool _mWasGuiDrawMissed = false;
//static bool _mHasRunFatalExceptionRoutine = false;
//static bool _mHasRunExitGameRoutine = false;
static bool _mIsExitingGame;
static bool _mHasInit;

int32_t Game_Init()
{
	if (_mHasInit)
	{
		return 0;
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

	_mHasInit = true;

	return initStatus;
}
int32_t Game_Run()
{
	if (Game_Init() < 0)
	{
		return Exception_Run("Unable to init!", false);
	}

	Window_LoadIcon();
	Music_Init();
	Input_Init();

	Music_PlayMusic("new00", true, true, false, 0, false, 0);

	bool ranAnimationTest = false;
	uint64_t counter = 0;
	uint64_t oldTicks = Stopwatch_GetTicks();
	bool isDone = false;
	double deltaLeftover = 0;
	while (!isDone)
	{
		//bool isFixedTimeStep = IsFixedTimeStep();
		bool isFixedTimeStep = true;
		double delta = deltaLeftover;
		deltaLeftover = 0;
		do
		{
			uint64_t newTicks = Stopwatch_GetTicks();
			double elapsedTime = Stopwatch_GetElapsedSeconds(oldTicks, newTicks);
			delta += elapsedTime;
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
		Input_Update(false);
		Music_Tick();
		SoundEffect_Tick();

		Renderer_SetupRenderState();
		Renderer_Render(1 / 60.0);

		bool tester1 = Input_IsLeftMouseReleased();
		bool tester2 = Input_IsDeleteReleased();
		counter += 1;
		if (counter % 180 == 0)
		{
			SoundEffect_PlaySound("newWarp");
		}
		if (tester1)
		{
			int hello = 0;
		}
		if (tester2)
		{
			int hello2 = 0;
		}

		if (!ranAnimationTest)
		{
			Animation_DebugTest();
			ranAnimationTest = true;
		}
		//Update(delta);
		//if (!OeService::SuppressDrawing())
		//{
		//	Draw(delta);
	//	}
		if (!isDone)
		{
			isDone = Game_IsExitingGame();
		}
	}
	//Dispose();
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
			//OeMouseState::INTERNAL_SetScrollWheelValue(e.wheel.y * 120);
		}
		if (e.type ==  SDL_EVENT_GAMEPAD_ADDED)
		{
			//OeControllerState::AddControllerInstance(e.cdevice.which);
		}
		else if (e.type == SDL_EVENT_GAMEPAD_REMOVED)
		{
			//OeControllerState::RemoveControllerInstance(e.cdevice.which);
		}
		else if (e.type == SDL_EVENT_WINDOW_FOCUS_GAINED) // Various Window Events...
		{
			//GameWindow_SetWindowActive(true);

			const char* videoDriver = SDL_GetCurrentVideoDriver();
			if (videoDriver == "x11")
			{
				// If we alt-tab away, we lose the 'fullscreen desktop' flag on some WMs
				//SDL_SetWindowFullscreen((SDL_Window*)(OeWindow::GetWindowContext()),
			//		OeWindow::IsFullscreen() ? SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
			}

			// Disable the screensaver when we're back.
			SDL_DisableScreenSaver();
		}
		else if (e.type == SDL_EVENT_WINDOW_FOCUS_LOST)
		{
			//OeWindow::SetWindowActive(false);

			const char* videoDriver = SDL_GetCurrentVideoDriver();
			if (videoDriver == "x11")
			{
				//SDL_SetWindowFullscreen((SDL_Window*)(OeWindow::GetWindowContext()), 0);
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
