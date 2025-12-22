#include "GameUpdater.h"

#include "../core/ServiceHelper.h"
#include "../service/Service.h"
#include "../core/Game.h"
#include "../globals/Globals.h"
#include "../utils/Utils.h"
#include "../input/Input.h"
#include "../math/Math.h"
#include "../utils/FPSTool.h"
#include "../utils/Cvars.h"
#include "../gamestate/GameStateManager.h"
#include "../audio/Music.h"
#include "../audio/SoundEffect.h"
#include "../input/Keys.h"
#include "../utils/Logger.h"
#include "../input/RecordingTool.h"
#include "../input/ActionList.h"
#include "../input/InputAction.h"
#include "../core/Func.h"
#include "../leveldata/LevelData.h"
#include "../input/ControllerStates.h"
#include "../io/DynamicByteBuffer.h"
#include "../../DebugDefs.h"
#include "../render/Renderer.h"
#include "../gamestate/GameState.h"

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
#if EDITOR
static int32_t _mDebugTimeHeld = 0;
static void Cheats()
{
	//WILLNOTDO 05152023
	/*
	if (OeConsole.IsPresent())
	{
		return;
	}
	*/

	if (Input_IsCtrlPressed())
	{
		if (Input_IsKeyTapped(KEYS_NumPad0))
		{
			GameUpdater_CycleDebugShowInfo();
		}
		if (Input_IsKeyTapped(KEYS_NumPad1))
		{
			SetDebugAutoSpeed(false);
			GLOBALS_DEBUG_GAME_LOGIC_SPEED = GLOBALS_DEFAULT_DEBUG_GAME_LOGIC_SPEED;
			Logger_printf("Auto Speed: %i\n", _mIsDebugAutoSpeedOn);
		}
		if (Input_IsKeyTapped(KEYS_NumPad2))
		{
			GameUpdater_ToggleDebugAutoSpeed();
			Logger_printf("Auto Speed: %i\n", _mIsDebugAutoSpeedOn);
		}
		if (Input_IsKeyTapped(KEYS_NumPad3))
		{
			//WILLNOTDO 05152023 ResourceManagers.SoundEffectManager.Dispose();
			Logger_LogInformation("Reloaded Audio");
		}
		if (Input_IsKeyTapped(KEYS_NumPad4))
		{
			GameUpdater_DebugReloadGraphics();
			Logger_LogInformation("Reloaded All Assets And Animations");
		}
	}
	else if (Input_IsShiftPressed())
	{
	}
	else if (Input_IsAltPressed())
	{
		if (Input_IsKeyTapped(KEYS_NumPad0))
		{
			Globals_DebugSetRenderDisabled(!Globals_DebugIsRenderDisabled());
			Logger_printf("Render Disabled: %i\n", Globals_DebugIsRenderDisabled());
		}
	}
	else
	{
		if (Input_IsKeyTapped(KEYS_NumPad0))
		{
			Globals_ToggleGodMode();
		}
		int timeToStart = 60;
		int timeInterval = 5;
		bool timeGo = false;
		if ((_mDebugTimeHeld == 0) || ((_mDebugTimeHeld >= timeToStart) && (_mDebugTimeHeld % timeInterval == 0)))
		{
			timeGo = true;
		}
		if (Input_IsKeyPressed(KEYS_NumPad1) && Input_IsKeyPressed(KEYS_NumPad2))
		{
			if (GLOBALS_DEBUG_GAME_LOGIC_SPEED != 100)
			{
				SetDebugAutoSpeed(false);
				GLOBALS_DEBUG_GAME_LOGIC_SPEED = 100;
				Logger_printf("Game Speed: %f\n", Globals_GetDebugGameSpeedAsMul());
			}
		}
		else if (Input_IsKeyPressed(KEYS_NumPad1))
		{
			_mDebugTimeHeld += 1;
			if (timeGo)
			{
				SetDebugAutoSpeed(false);
				GLOBALS_DEBUG_GAME_LOGIC_SPEED -= 10;
				if (GLOBALS_DEBUG_GAME_LOGIC_SPEED < 10)
				{
					GLOBALS_DEBUG_GAME_LOGIC_SPEED = 10;
				}
				Logger_printf("Game Speed: %f\n", Globals_GetDebugGameSpeedAsMul());
			}
		}
		else if (Input_IsKeyPressed(KEYS_NumPad2))
		{
			_mDebugTimeHeld += 1;
			if (timeGo)
			{
				SetDebugAutoSpeed(false);
				GLOBALS_DEBUG_GAME_LOGIC_SPEED += 10;
				Logger_printf("Game Speed: %f\n", Globals_GetDebugGameSpeedAsMul());
			}
		}
		else
		{
			_mDebugTimeHeld = 0;
		}
		if (Input_IsKeyTapped(KEYS_NumPad3))
		{
			GLOBALS_DEBUG_IS_PAUSED = !GLOBALS_DEBUG_IS_PAUSED;
			Logger_printf("Is Paused: %i\n", GLOBALS_DEBUG_IS_PAUSED);
			return;
		}

		if (Input_IsKeyTapped(KEYS_NumPad5))
		{
			Cvars_FlipAsBool(CVARS_EDITOR_SHOW_PROPS);
			Logger_printf("Show Props: %i\n", Cvars_GetAsBool(CVARS_EDITOR_SHOW_PROPS));
		}
		if (Input_IsKeyTapped(KEYS_NumPad6))
		{
			Cvars_FlipAsBool(CVARS_EDITOR_SHOW_THINGS);
			Logger_printf("Show Things: %i\n", Cvars_GetAsBool(CVARS_EDITOR_SHOW_THINGS));
		}
		if (Input_IsKeyTapped(KEYS_NumPad7))
		{
			Cvars_FlipAsBool(CVARS_EDITOR_SHOW_TILES);
			Logger_printf("Show Tiles: %i\n", Cvars_GetAsBool(CVARS_EDITOR_SHOW_TILES));
		}
		if (Input_IsKeyTapped(KEYS_NumPad8))
		{
			if (GLOBALS_DEBUG_IS_EDITOR_MODE)
			{
				Cvars_FlipAsBool(CVARS_EDITOR_SHOW_COLLISION);
				Logger_printf("Show Editor Col: %i\n", Cvars_GetAsBool(CVARS_EDITOR_SHOW_COLLISION));
			}
			else
			{
				GLOBALS_DEBUG_SHOW_INGAME_COLLISION = !GLOBALS_DEBUG_SHOW_INGAME_COLLISION;
				Logger_printf("Show InGame Col: %i\n", GLOBALS_DEBUG_SHOW_INGAME_COLLISION);
			}
		}
		if (Input_IsKeyTapped(KEYS_NumPad9))
		{
			GLOBALS_DEBUG_DISABLE_HUD = !GLOBALS_DEBUG_DISABLE_HUD;
			Logger_printf("Disable Hud: %i\n", GLOBALS_DEBUG_DISABLE_HUD);
		}
		if (Input_IsKeyTapped(KEYS_F8))
		{
			SoundEffect_StopAllSounds();
			GameUpdater_DebugReloadMap();
		}
		if (Input_IsKeyTapped(KEYS_F9))
		{
			GameUpdater_DebugSaveMap();
		}
		if (Input_IsKeyTapped(KEYS_F10))
		{
			SoundEffect_StopAllSounds();
			GameUpdater_FastReset();
		}
		if (Input_IsKeyTapped(KEYS_F11))
		{
			SoundEffect_StopAllSounds();
			GameUpdater_FastResetPlusMove();
		}
		if (Input_IsKeyTapped(KEYS_F12))
		{
			//GameUpdater_ToggleEditor();
		}
		if (Input_IsKeyTapped(KEYS_OemComma))
		{
			//TODO C99 Utils_ToggleNextUserLanguage(true);
		}
	}
}
#endif
static void Tick()
{
	Utils_FreeArena(UTILS_ALLOCATION_ARENA_JUST_THIS_FRAME);

	GameStateManager_UpdateLastRenderPosition();

	if (ServiceHelper_HasPlayerHasLostControllerConnection())
	{
		if (!_mWasShowingControllerLostConnectionMessage)
		{
			Do_PauseAllSounds(0);
			Do_PauseMusic(0);
		}
		Input_Update(false);
		ServiceHelper_HandlePlayerLostControllerConnection();
		_mWasShowingControllerLostConnectionMessage = true;
	}
	else
	{
		if (_mWasShowingControllerLostConnectionMessage)
		{
			Do_ResumeAllSounds(0);
			Do_ResumeMusic(0);
		}
		GameStateManager_Tick();
		_mGlobalTicks++;
		_mWasShowingControllerLostConnectionMessage = false;
	}

	HandleAltEnterCheck();

#if EDITOR
	Cheats();
#endif
}
#if EDITOR
static bool HandleDebugPauseAndStep()
{
	/*
	int readFrame = OeControllerStates_GetMasterRecordingReadFrame(); //For specific frame stops
	if (readFrame == 137600)
	{
		OeGlobals_DEBUG_IS_PAUSED = true;
	}
	*/

	if (!GLOBALS_DEBUG_IS_PAUSED)
	{
		return false;
	}

	Input_Update(true);

	if (Input_IsKeyTapped(KEYS_NumPad4))
	{
		Tick();
		Renderer_SetupRenderState();
		Logger_LogInformation("Step");
		return true;
	}

	if (Input_IsKeyTapped(KEYS_OemComma))
	{
		//TODO C99 Utils_ToggleNextUserLanguage(true);
		return true;
	}

	if (Input_IsKeyTapped(KEYS_OemPeriod))
	{
		//TODO C99 Utils_ToggleNextUserLanguage(true);
		Tick();
		Renderer_SetupRenderState();
		Logger_LogInformation("Step");
		return true;
	}

	if (Input_GetPlayerOneAction(ACTIONLIST_GAME_LS)->mIsTapped)
	{
		//TODO C99 GameStateManager_ActiveGameState()->CreateDebugSaveState();
	}

	if (Input_GetPlayerOneAction(ACTIONLIST_GAME_RS)->mIsTapped)
	{
		//TODO C99 GameStateManager_ActiveGameState()->UseDebugSaveState();
	}

	if (Input_GetPlayerOneAction(ACTIONLIST_GAME_LB)->mIsTapped)
	{
		//TODO C99 GameStateManager_ActiveGameState()->Rewind();
	}

	Renderer_SetupRenderState();

	Cheats();

	return true;
}
#endif
static bool IsPaused()
{
#ifdef DEBUG_DEF_MAKE_GAME_ALWAYS_ACTIVE
	return false;
#endif

	if (Service_PlatformDoesNotDoNormalPausing())
	{
		return false;
	}

	bool isGameActive = Game_IsActive();
	bool pauseOnFocusLoss = Cvars_GetAsBool(CVARS_USER_IS_PAUSE_ON_FOCUS_LOSS);
	bool muteOnFocusLoss = Cvars_GetAsBool(CVARS_USER_IS_MUTE_ON_FOCUS_LOSS);
	if (pauseOnFocusLoss && Music_DoNotAllowUpdatesWhilePaused())
	{
		muteOnFocusLoss = true;
	}

	if (isGameActive)
	{
		if (_mWasNotInFocus)
		{
			Do_ResumeAllSounds(0);

			if (_mPausedMusic)
			{
				Do_ResumeMusic(0);
			}

			SoundEffect_SetSfxMuted(false);
			Music_SetMusicMuted(false);

#if EDITOR
			//WILLNOTDO 05152023
			/*
			if (OeGlobals_DEBUG_IS_EDITOR_MODE)
			{
				OeEditor.OnWindowFocus();
			}
			*/
#endif

			_mWasNotInFocus = false;
			_mPausedMusic = false;
		}
	}
	else
	{
		if (!_mWasNotInFocus)
		{
			if (pauseOnFocusLoss)
			{
				Do_PauseAllSounds(0);

				Input_StopAllRumble();

				if (muteOnFocusLoss)
				{
					_mPausedMusic = true;
					Do_PauseMusic(0);
				}
			}

			if (muteOnFocusLoss)
			{
				SoundEffect_SetSfxMuted(true);
				Music_SetMusicMuted(true);
			}

			_mWasNotInFocus = true;
		}
		if (!muteOnFocusLoss && pauseOnFocusLoss)
		{
			Music_Tick();
		}
	}

	if (!isGameActive && pauseOnFocusLoss)
	{
		return true;
	}

	return false;
}
/*
static void UpdateFixedTimeStep()
{
	bool isFixedTimeStep = false;
	if (Cvars_GetAsBool(Cvars_USER_IS_FIXED_TIMESTEP_ENABLED))
	{
		isFixedTimeStep = true;
	}
	if (Service_PlatformForcesRelyOnVsync() || Cvars_GetAsBool(Cvars_ENGINE_RELY_ON_VSYNC))
	{
		isFixedTimeStep = false;
	}
#if EDITOR
	if (OeGlobals_IsDebugGameSpeedSet())
	{
		isFixedTimeStep = false;
	}
	if (_mIsDebugAutoSpeedOn)
	{
		isFixedTimeStep = false;
	}
#endif
	//OeGame_SetTimeStepFixed(isFixedTimeStep);
}
*/
static void UpdateLoop(double delta)
{
#if EDITOR
	if (HandleDebugPauseAndStep())
	{
		return;
	}
#endif

#ifdef DEBUG_DEF_RUN_THE_GAME_FAST
	_mIsDebugAutoSpeedOn = true;
#endif

	double stepLength = Utils_GetNormalStepLength();
	bool interpolated = GameUpdater_IsInterpolated();

	int fixedTimeStepTicks = 1;
	if (!_mIsDebugAutoSpeedOn)
	{
		if ((RecordingTool_IsReading() && RecordingTool_IsGoFastFlagSet()) || (Input_IsPlayingMasterRecording() && INPUT_FLAG_IS_PLAYING_MASTER_RECORDING_FAST))
		{
			fixedTimeStepTicks = Cvars_GetAsInt(CVARS_ENGINE_RECORDING_PLAYBACK_FAST_SPEED);
			if (fixedTimeStepTicks < 1)
			{
				fixedTimeStepTicks = 1;
			}
			delta *= fixedTimeStepTicks;
		}
	}
	else
	{
		if (Service_PlatformForcesRelyOnVsync() || Cvars_GetAsBool(CVARS_ENGINE_RELY_ON_VSYNC)) //Make rely on vsync run at fast speed when debug auto speed is on
		{
			fixedTimeStepTicks = Cvars_GetAsInt(CVARS_ENGINE_RECORDING_PLAYBACK_FAST_SPEED);
		}
	}

#if EDITOR
	if (!GLOBALS_DEBUG_IS_EDITOR_MODE && Globals_IsDebugGameSpeedSet())
	{
		delta *= Globals_GetDebugGameSpeedAsMul();
	}
#endif

#ifdef DEBUG_DEF_FORCE_GAME_SPEED_MUL
	fixedTimeStepTicks = DEBUG_DEF_FORCE_GAME_SPEED_MUL;
	delta += (DEBUG_DEF_FORCE_GAME_SPEED_MUL * stepLength);
#endif

	bool ticked = false;
	if (!interpolated)
	{
		_mDeltaAccumulator = 0;
		for (int i = 0; i < fixedTimeStepTicks; i++)
		{
			Tick();
			ticked = true;
		}
	}
	else
	{
		_mDeltaAccumulator += delta;
		while (_mDeltaAccumulator >= stepLength)
		{
			if (ticked)
			{
				_mSkippedFrames++;
			}
			Tick();
			_mDeltaAccumulator -= stepLength;
			ticked = true;
		}
	}

	if (ticked)
	{
		Renderer_SetupRenderState();
	}
}

const char* GameUpdater_GetFpsString()
{
	//TODO C99
	return "";
	/*int number;
	if (_mIsDebugAutoSpeedOn)
	{
		float speed = GetAutoSpeedUpdateSpeed();
		number = (int)speed;
	}
	else
	{
		number = Renderer_GetFPS();
	}
	number = OeMath_Min(number, 9999);
	return Utils_GetStringFromNumber(number);*/
}
float GameUpdater_GetAutoSpeedUpdateSpeed()
{
	return GameUpdater_GetFPS() / 60.0f;
}
int GameUpdater_GetFPS()
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
	//TODO C99
	/*
	Get_LevelDataResource()->Reload();
	OeLogger_LogInformation("Map Reloaded (Full) [" + Get_LevelDataResource()->GetPath() + "][" +
		Get_LevelData()->mLevelName + "]");
	OeGlobals_DEBUG_QUICK_PLAYER_POSITION = Vector2_Zero;
	OeGameStateManager_SetupReloadMap();
	*/
}
void GameUpdater_DebugSaveMap()
{
	//WILLNOTDO 05152023
	/*
#if EDITOR
	Get_LevelDataResource().SaveAsIni();
	OeEditor.Save();
	Do_PlaySound("editorSave", 1f);
	Logger.LogInformation("Map Saved");
#endif
*/
}
void GameUpdater_FastReset()
{
	GLOBALS_DEBUG_QUICK_PLAYER_POSITION = Vector2_Zero;
	GameStateManager_DebugForceReloadMapNow();
	GameStateManager_SetGameState(GAMESTATEMANAGER_GAME_STATE_NORMAL);
	GLOBALS_DEBUG_IS_EDITOR_MODE = false;
	//TODO C99 Logger_LogInformation("Map Reloaded (Fast) [" + Get_LevelDataResource()->GetPath() + "][" +Get_LevelData()->mLevelName + "]");
}
void GameUpdater_FastResetPlusMove()
{
	//WILLNOTDO 05152023
	/*
#if EDITOR
	OeGlobals_DEBUG_QUICK_PLAYER_POSITION = Input_GetCameraAdjustedMouse(ref OeEditor.Camera);
	OeGameStateManager.DebugForceReloadMapNow();
	OeGameStateManager.SetGameState(OeGameStateManager.GAME_STATE_NORMAL);
	OeGlobals_DEBUG_IS_EDITOR_MODE = false;
	Logger.LogInformation("Map Reloaded (Fast+Move) [" + Get_LevelDataResource().GetPath() + "][" +
		Get_LevelData().mLevelName + "]");
	OeGame.GetHelper().OnDebugFastResetPlusMove();
#endif
*/
}
void GameUpdater_ToggleEditor()
{
	//WILLNOTDO 05152023
	//OeGlobals_DEBUG_IS_EDITOR_MODE = !OeGlobals_DEBUG_IS_EDITOR_MODE;
	//Logger.LogInformation("Editor Toggle");
}
void GameUpdater_ToggleDebugAutoSpeed()
{
	SetDebugAutoSpeed(!_mIsDebugAutoSpeedOn);
}
void GameUpdater_DebugReloadGraphics()
{
	//WILLNOTDO 05152023
	/*
	OeResourceManagers.TextureManager.Reload();
	OeSheet.BuildSheets();
	OeAnimation.BuildAnimations();
	bool isEditor = OeGlobals_DEBUG_IS_EDITOR_MODE;
	FastReset();
	if (isEditor)
	{
		OeGlobals_DEBUG_IS_EDITOR_MODE = true;
	}
	OeGlobals_DEBUG_EDITOR_JUST_RELOADED_GRAPHICS = true;
	Logger.LogInformation("Reloaded all graphics");
	*/
}
void GameUpdater_CycleDebugShowInfo()
{
	//TODO C99
	/*
	GLOBALS_DEBUG_SHOW_INFO++;
	if (GLOBALS_DEBUG_SHOW_INFO > GAMESTATEMANAGER_DEBUG_INFO_SHOW_THING_VIEWER)
	{
		GLOBALS_DEBUG_SHOW_INFO = GAMESTATEMANAGER_DEBUG_INFO_SHOW_NOTHING;
	}
	Logger_LogInformation("Debug Info: " + std_to_string(OeGlobals_DEBUG_SHOW_INFO), true);*/
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
