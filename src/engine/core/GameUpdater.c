/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "GameUpdater.h"

#include "../utils/Utils.h"
#include "../utils/FPSTool.h"
#include "../utils/Cvars.h"
#include "Game.h"
#include "../input/Input.h"
#include "../render/Renderer.h"
#include "../service/Service.h"

static uint64_t _mSkippedFrames;
static uint64_t _mGlobalTicks;
static double _mDeltaAccumulator;
static double _mLastDelta;
static bool _mIsDebugAutoSpeedOn;
static bool _mSuppressFullscreenToggle;
static bool _mPausedMusic;
static bool _mWasNotInFocus;
static bool _mWasShowingControllerLostConnectionMessage;
static FPSTool _mFpsToolUpdate;

static void SetDebugAutoSpeed(bool value)
{
	if (_mIsDebugAutoSpeedOn == value)
	{
		return;
	}

	Cvars_SetAsBool(CVARS_USER_IS_VSYNC, !_mIsDebugAutoSpeedOn);
	Renderer_UpdateVsync();
	Renderer_ApplyChanges();
	_mIsDebugAutoSpeedOn = value;
}
static void HandleAltEnterCheck()
{
	if (Input_IsAltPressed())
	{
		if (!_mSuppressFullscreenToggle)
		{
			if (Input_IsEnterTapped())
			{
				Utils_ToggleFullscreenButton();
				Cvars_SaveUserConfig();
				_mSuppressFullscreenToggle = true;
			}
		}
	}
	else
	{
		_mSuppressFullscreenToggle = false;
	}
}
static void Tick()
{
	//TODO
}
static bool IsPaused()
{
	return false;
}
static void UpdateLoop(double delta)
{
}

const char* GameUpdater_GetFpsString()
{
	return NULL;
	//TODO C99
   //int number;
   //if (_mIsDebugAutoSpeedOn)
   //{
   //	float speed = GetAutoSpeedUpdateSpeed();
   //	number = (int)speed;
   //}
   //else
   //{
   //	number = OeRenderer::GetFPS();
//	}
	//number = OeMath::Min(number, 9999);
//	return OeUtils::GetStringFromNumber(number);
}
float GameUpdater_GetAutoSpeedUpdateSpeed()
{
	return (GameUpdater_GetFPS() / 60.0f);
}
int32_t GameUpdater_GetFPS()
{
	return _mFpsToolUpdate.mCurrentFps;
}
bool GameUpdater_IsInterpolated()
{
	if (_mIsDebugAutoSpeedOn)
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
		return true;
	}
#endif

	if (Cvars_GetAsBool(CVARS_USER_IS_FIXED_TIMESTEP_ENABLED))
	{
		return false;
	}

	return true;
}
void GameUpdater_Update(double delta)
{
	_mLastDelta = delta;

	FPSTool_Update(&_mFpsToolUpdate, delta);

	//UpdateFixedTimeStep();

	if (!Game_IsActive())
	{
		if (Input_HasInit() && Service_PlatformMutesInputWhenGameIsNotActive())
		{
			Input_MuteAllInput();
		}
	}

	if (!IsPaused())
	{
		UpdateLoop(delta);
	}
}
void GameUpdater_DebugReloadMap()
{
	//TODO
}
void GameUpdater_DebugSaveMap()
{
	//TODO
}
void GameUpdater_FastReset()
{
	//TODO
}
void GameUpdater_FastResetPlusMove()
{
	//TODO
}
void GameUpdater_ToggleEditor()
{
	//TODO
}
void GameUpdater_ToggleDebugAutoSpeed()
{
	//TODO
}
void GameUpdater_DebugReloadGraphics()
{
	//TODO
}
void GameUpdater_CycleDebugShowInfo()
{
	//TODO
}
uint64_t GameUpdater_GetGlobalTicks()
{
	return _mGlobalTicks;
}
bool GameUpdater_IsDebugAutoSpeedOn()
{
	return _mIsDebugAutoSpeedOn;
}
double GameUpdater_GetLastDelta()
{
	return _mLastDelta;
}
double GameUpdater_GetDeltaAccumulator()
{
	return _mDeltaAccumulator;
}
uint64_t GameUpdater_GetSkippedFrames()
{
	return _mSkippedFrames;
}