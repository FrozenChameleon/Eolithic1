#include "MenuFunc.h"

#include "Game.h"
#include "GameHelper.h"
#include "../utils/Cvars.h"
#include "../globals/Globals.h"
#include "../service/Service.h"
#include "../utils/Utils.h"
#include "../achievement/AchievementHandler.h"
#include "../core/GameUpdater.h"
#include "../utils/Strings.h"
#include "../input/Input.h"
#include "../input/InputPlayer.h"
#include "../gamesave/GameSaveManager.h"
#include "../gamestate/GameStateManager.h"
#include "../input/InputBindings.h"
#include "../render/Renderer.h"
#include "../core/Window.h"
#include "Func.h"
#include "../../third_party/stb_ds.h"
#include "../utils/Macros.h"

int MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = 0;
Rectangle MENUFUNC_TEMP_WINDOW_SIZE = { 0 };

static bool SUPPRESS_MENU_SOUNDS;
static int32_t SOUND_TEST_CURRENT_SOUND;
static int32_t SOUND_TEST_CURRENT_MUSIC;
static StringPair* MUSIC_LIST;
static StringPair* SOUND_LIST;
static bool LOADED_OPTIONS_MENU;
static uint64_t WENT_BACK_FRAME;

static bool _mHasInit;
void MenuFunc_Init()
{
	if (_mHasInit)
	{
		return;
	}

	GameHelper_SetupMusicAndSfxList(MUSIC_LIST, SOUND_LIST);

	_mHasInit = true;
}

void MenuFunc_GameResetAllOptionsToDefaults()
{
	//TODO C99 Cvars_CopyFromUserDefaults();
	Window_UpdateFullscreen();
	Renderer_UpdateVsync();
	Renderer_ApplyChanges();
}
void MenuFunc_DebugGodModeToggle()
{
	Globals_ToggleGodMode();
}
void MenuFunc_DebugResetAchievements()
{
	//TODO C99 Service_ResetAchievements();
}
void MenuFunc_DebugUnlockNextAchievement()
{
	AchievementHandler_DebugUnlockNextAchievement();
}
void MenuFunc_ToggleNextUserLanguage()
{
	//TODO C99 Utils_ToggleNextUserLanguage(false);
}
const char* MenuFunc_GetUserLanguageName()
{
	return NULL;
	//TODO C99 return Utils_GetUserLanguageName();
}
bool MenuFunc_WentBackThisFrame()
{
	return WENT_BACK_FRAME == GameUpdater_GetGlobalTicks();
}
void MenuFunc_SoundStopSoundTestMusic()
{
	Do_StopMusic();
}
static void HandleSoundTestDirectionLogic(int* value, const int32_t direction, const int32_t len)
{
	if (direction == 1)
	{
		*value += 1;
	}
	else
	{
		*value -= 1;
	}

	int lim = len - 1;
	if (*value < 0)
	{
		*value = 0;
	}
	else if (*value > lim)
	{
		*value = lim;
	}
}
void MenuFunc_SoundChangeSoundTextMusic(int direction)
{
	UNUSED(direction);
	//TODO C99 HandleSoundTestDirectionLogic(&SOUND_TEST_CURRENT_MUSIC, direction, MUSIC_LIST.size());
}
void MenuFunc_SoundChangeSoundTextSfx(int direction)
{
	UNUSED(direction);
	//TODO C99 HandleSoundTestDirectionLogic(&SOUND_TEST_CURRENT_SOUND, direction, SOUND_LIST.size());
}
void MenuFunc_SoundPlaySoundTestSfx()
{
	Do_StopAllSounds();
	//TODO C99 Do_PlaySound(SOUND_LIST[SOUND_TEST_CURRENT_SOUND].mValue);
}
void MenuFunc_SoundPlaySoundTestMusic()
{
	//TODO C99 Do_PlayMusic(MUSIC_LIST[SOUND_TEST_CURRENT_MUSIC].mValue, true, true);
}
const char* MenuFunc_GetCurrentSoundTestMusic()
{
	return NULL;
	//TODO C99 return MUSIC_LIST[SOUND_TEST_CURRENT_MUSIC].mKey;
}
const char* MenuFunc_GetCurrentSoundTestMusicAsNumber()
{
	return NULL;
/*#if EDITOR
	if (GLOBALS_DEBUG_IS_GOD_MODE)
	{
		return GetCurrentSoundTestMusic();
	}
#endif*/
	//TODO C99 return Utils_GetStringFromNumberWithZerosTens(SOUND_TEST_CURRENT_MUSIC);
}
const char* MenuFunc_GetCurrentSoundTestSfx()
{
	return NULL;
	//TODO C99 return SOUND_LIST[SOUND_TEST_CURRENT_SOUND].mKey;
}
const char* MenuFunc_GetCurrentSoundTestSfxAsNumber()
{
	return NULL;
/*#if EDITOR
	if (GLOBALS_DEBUG_IS_GOD_MODE)
	{
		return GetCurrentSoundTestSfx();
	}
#endif*/
	//TODO C99 return OeUtils_GetStringFromNumberWithZerosHundreds(SOUND_TEST_CURRENT_SOUND);
}
const char* MenuFunc_GetGenericText(int action, const char* data1, const char* data2)
{
	return NULL;
	/*std_string strToDraw = "";
	switch (action)
	{
	case MENUFUNC_SOUND_STOP_SOUND_TEST_MUSIC:
		break;
	case MENUFUNC_SOUND_STOP_SOUND_TEST_SFX:
		break;
	case MENUFUNC_SOUND_CHANGE_SOUND_TEST_MUSIC:
		strToDraw = GetCurrentSoundTestMusic();
		break;
	case MENUFUNC_SOUND_CHANGE_SOUND_TEST_SFX:
		strToDraw = GetCurrentSoundTestSfx();
		break;
	case MENUFUNC_SOUND_PLAY_SOUND_TEST_MUSIC:
		break;
	case MENUFUNC_SOUND_PLAY_SOUND_TEST_SFX:
		break;
	case MENUFUNC_ACTION_GO_TO_ANCHOR:
		break;
	case MENUFUNC_VIDEO_FULLSCREEN_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_FULLSCREEN));
		break;
	case MENUFUNC_VIDEO_VSYNC_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_VSYNC));
		break;
	case MENUFUNC_VIDEO_FIXED_TIME_STEP_TOGGLE:
		strToDraw = Cvars_GetAsBool(Cvars_USER_IS_FIXED_TIMESTEP_ENABLED) ? "<60>" : "<Variable>";
		break;
	case MENUFUNC_SOUND_SFX_VOLUME_TOGGLE:
		strToDraw = StringHelperInt(Cvars_GetAsInt(Cvars_USER_VOLUME_SFX));
		break;
	case MENUFUNC_SOUND_MUSIC_VOLUME_TOGGLE:
		strToDraw = StringHelperInt(Cvars_GetAsInt(Cvars_USER_VOLUME_MUSIC));
		break;
	case MENUFUNC_SOUND_MASTER_VOLUME_TOGGLE:
		strToDraw = StringHelperInt(Cvars_GetAsInt(Cvars_USER_VOLUME_MASTER));
		break;
	case MENUFUNC_INPUT_RUMBLE_TOGGLE:
		strToDraw = StringHelperBool(!Cvars_GetAsBool(Cvars_USER_IS_RUMBLE_DISABLED));
		break;
	case MENUFUNC_INPUT_DEADZONE_TOGGLE:
		//strToDraw = StringHelperInt(Cvars_GetAsFloat(Cvars_USER_CONTROLLER_RADIAL_DEADZONE));
		break;
	case MENUFUNC_VIDEO_SHOW_FPS_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_SHOWING_FPS));
		break;
	case MENUFUNC_VIDEO_SHOW_IN_GAME_TIMER_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_SHOWING_IN_GAME_TIMER));
		break;
	case MENUFUNC_SOUND_MUTE_ON_FOCUS_LOSS_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_MUTE_ON_FOCUS_LOSS));
		break;
	case MENUFUNC_GAME_PAUSE_ON_FOCUS_LOSS_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_PAUSE_ON_FOCUS_LOSS));
		break;
	case MENUFUNC_GAME_IS_SCREENSHAKE_DISABLED:
		strToDraw = StringHelperBool(!Cvars_GetAsBool(Cvars_USER_IS_SCREENSHAKE_DISABLED));
		break;
	case MENUFUNC_INPUT_RESET_ALL_BINDINGS:
		break;
	case MENUFUNC_ACTION_RESUME_GAME:
		break;
	case MENUFUNC_ACTION_EXIT_GAME:
		break;
	case MENUFUNC_ACTION_LOAD_LEVEL:
		break;
	case MENUFUNC_GAME_BORDER_TOGGLE:
		strToDraw = StringHelperBorder(Cvars_GetAsInt(CVARS_USER_BORDER_TYPE));
		break;
	case MENUFUNC_INPUT_CONTROLLER_TYPE_TOGGLE:
		strToDraw = "?";
		break;
	case MENUFUNC_GAME_BORDER_FRAME:
		strToDraw = StringHelperBool(Cvars_GetAsBool(CVARS_USER_IS_BORDER_FRAME_ON));
		break;
	case MENUFUNC_ACTION_GO_BACK_ONE_ANCHOR:
		break;
	case MENUFUNC_VIDEO_DRAW_MODE_TOGGLE:
		switch (Cvars_GetAsInt(CVARS_USER_DRAW_MODE))
		{
		case RENDERER_DRAWMODE_ASPECT:
			strToDraw = OeStrings_Get("<Aspect Ratio>");
			break;
		case RENDERER_DRAWMODE_PIXELPERFECT:
			strToDraw = OeStrings_Get("<Pixel>");
			break;
		case RENDERER_DRAWMODE_SUPERSAMPLE:
			strToDraw = OeStrings_Get("<Super Sample>");
			break;
		}
		break;
	case MENUFUNC_VIDEO_REFRESH_SYNC_TOGGLE:
		break;
	case MENUFUNC_VIDEO_APPLY_WINDOW_SIZE_MULTIPLE:
		break;
	case MENUFUNC_VIDEO_CHANGE_WINDOW_SIZE_MULTIPLE:
		strToDraw = GetChangeWindowSizeMultipleString();
		break;
	case MENUFUNC_VIDEO_CHANGE_WINDOW_SIZE:
		strToDraw = GetChangeWindowSizeString();
		break;
	case MENUFUNC_INPUT_BIND_ACTION:
		break;
	case MENUFUNC_VIDEO_INTERNAL_RESOLUTION_MULTIPLE_TOGGLE:
		strToDraw = GetInternalResolutionMultipleString();
		break;
	case MENUFUNC_VIDEO_LINEAR_FILTER_TOGGLE:
		strToDraw = StringHelperBool(Cvars_GetAsBool(Cvars_USER_IS_LINEAR_FILTER_ALLOWED));
		break;
	}
	return strToDraw;*/
}
const char* MenuFunc_GetChangeWindowSizeMultipleString()
{
	return NULL;

	//TODO C99
	/*
	return "<" + std_to_string(TEMP_WINDOW_SIZE_MULTIPLE) + "X: " + std_to_string((OeUtils_GetWindowSizeMulWidth() * TEMP_WINDOW_SIZE_MULTIPLE)) +
		"x" + std_to_string((OeUtils_GetWindowSizeMulHeight() * TEMP_WINDOW_SIZE_MULTIPLE)) + ">";*/
}
const char* MenuFunc_GetChangeWindowSizeString()
{
	return NULL;

	//TODO C99
/*
	return "<" + std_to_string(TEMP_WINDOW_SIZE.Width) + "X" + std_to_string(TEMP_WINDOW_SIZE.Height) + ">";*/
}
const char* MenuFunc_GetInternalResolutionMultipleString()
{
	return NULL;

	/*int mul = Cvars_GetAsInt(Cvars_USER_INTERNAL_RESOLUTION_MULTIPLE);
	std_string mulString = "";
	if (mul > 0)
	{
		mulString = "<" + std_to_string(mul) + "x: " + std_to_string((Cvars_GetAsInt(Cvars_ENGINE_INTERNAL_RENDER_WIDTH) * mul)) +
			"x" + std_to_string((Cvars_GetAsInt(Cvars_ENGINE_INTERNAL_RENDER_HEIGHT) * mul)) + ">";
	}
	else
	{
		mul = OeRenderer_GetRenderTargetScale();
		mulString = "<Auto " + std_to_string(mul) + "x: " + std_to_string(Cvars_GetAsInt(Cvars_ENGINE_INTERNAL_RENDER_WIDTH) * mul) +
			"x" + std_to_string(Cvars_GetAsInt(Cvars_ENGINE_INTERNAL_RENDER_HEIGHT) * mul) + ">";
	}
	return mulString;*/
}
void MenuFunc_SoundStopSoundTestSfx()
{
	Do_StopAllSounds();
}
void MenuFunc_VideoFixedTimeStepToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_FIXED_TIMESTEP_ENABLED);
}
void MenuFunc_VideoApplyWindowSizeMultiple()
{
	Cvars_SetAsBool(CVARS_USER_IS_FULLSCREEN, false);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_MULTIPLE, MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_WIDTH, -1);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_HEIGHT, -1);
	//TODO C99 Utils_InvokeWindowedMode();
}
void MenuFunc_VideoApplyWindowSize()
{
	Cvars_SetAsBool(CVARS_USER_IS_FULLSCREEN, false);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_MULTIPLE, 1);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_WIDTH, MENUFUNC_TEMP_WINDOW_SIZE.Width);
	Cvars_SetAsInt(CVARS_USER_WINDOW_SIZE_HEIGHT, MENUFUNC_TEMP_WINDOW_SIZE.Height);
	//TODO C99 OeUtils_InvokeWindowedMode();
}
void MenuFunc_VideoChangeWindowSize(int direction, int32_t forcedSliderValue)
{
	/*std_vector<Rectangle> resolutions = OeUtils_GetWindowResolutions(true);
	if (resolutions.size() == 0)
	{
		return;
	}

	int me = -1;
	if (TEMP_WINDOW_SIZE.Width == -1)
	{
		TEMP_WINDOW_SIZE = OeUtils_GetProposedWindowSize();
	}

	for (int i = 0; i < resolutions.size(); i += 1)
	{
		if (resolutions[i] == TEMP_WINDOW_SIZE)
		{
			me = i;
			break;
		}
	}

	if (me == -1)
	{
		TEMP_WINDOW_SIZE = resolutions[resolutions.size() - 1];
		return;
	}

	int next = me + direction;
	if (next < 0)
	{
		next = resolutions.size() - 1;
	}
	if (next > resolutions.size() - 1)
	{
		next = 0;
	}
	TEMP_WINDOW_SIZE = resolutions[next];*/
}
void MenuFunc_VideoChangeWindowSizeMultiple(int direction, int32_t forcedSliderValue)
{
	int maxValue = MenuFunc_GetVideoChangeWindowSizeMultipleMaxValue();
	int min = 1;
	if (forcedSliderValue != -1)
	{
		MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = (int)(maxValue * (forcedSliderValue / 100.0f));
		if (MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE < min)
		{
			MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = min;
		}
	}
	else if (direction != 0)
	{
		MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE += direction;
		if (MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE > maxValue)
		{
			MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = maxValue;
		}
		if (MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE < min)
		{
			MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = min;
		}
	}
	else
	{
		MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE++;
		if (MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE > maxValue)
		{
			MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = min;
		}
		if (MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE < min)
		{
			MENUFUNC_TEMP_WINDOW_SIZE_MULTIPLE = maxValue;
		}
	}
}
const char* MenuFunc_StringHelperBorder(int value)
{
	return NULL;
	/*
	std_string str = "";

	switch (value)
	{
	case -1:
		str = OeStrings_Get("<NONE>");
		break;
	case 0:
		str = OeStrings_Get("<0>");
		break;
	case 1:
		str = OeStrings_Get("<1>");
		break;
	case 2:
		str = OeStrings_Get("<2>");
		break;
	case 3:
		str = OeStrings_Get("<3>");
		break;
	case 4:
		str = OeStrings_Get("<4>");
		break;
	case 5:
		str = OeStrings_Get("<5>");
		break;
	case 6:
		str = OeStrings_Get("<6>");
		break;
	case 7:
		str = OeStrings_Get("<7>");
		break;
	case 8:
		str = OeStrings_Get("<8>");
		break;
	case 9:
		str = OeStrings_Get("<9>");
		break;
	}

	return str;*/
}
const char* MenuFunc_StringHelperBool(bool value)
{
	if (value)
	{
		return "<ON>";
	}
	else
	{
		return "<OFF>";
	}
}
const char* MenuFunc_StringHelperFloat(float value)
{
	return NULL;
	//TODO C99 return "<" + std_to_string(value) + ">";
}
const char* MenuFunc_StringHelperInt(int value)
{
	return NULL;
	//TODO C99 return "<" + std_to_string(value) + ">";
}
void MenuFunc_InputDeadzoneToggle()
{
	/*
	float temp = Cvars_GetAsFloat(Cvars_USER_CONTROLLER_RADIAL_DEADZONE);
	temp += .1f;
	temp = OeMath.RoundToTenths(temp);
	float min = .1f;
	float max = .9f;
	if (temp > max)
	{
	temp = min;
	}
	Cvars_Set(Cvars_USER_CONTROLLER_RADIAL_DEADZONE, temp);
	OeUniverse.SaveUserConfig();
	*/
}
int MenuFunc_VolumeToggle(const char* cvar, int32_t direction, int32_t forcedSliderValue)
{
	int returnValue = 0;
	int volume = Cvars_GetAsInt(cvar);
	int oldVolume = volume;
	if (forcedSliderValue != -1)
	{
		int newVolume = forcedSliderValue;
		newVolume /= 10;
		newVolume *= 10;
		if (newVolume != volume)
		{
			if (newVolume > volume)
			{
				returnValue = 1;
			}
			else
			{
				returnValue = -1;
			}
			volume = newVolume;
		}
	}
	else
	{
		bool oneDirection = direction == 0;
		if (oneDirection)
		{
			volume += 10;
			if (volume > 100)
			{
				volume = 0;
			}
		}
		else
		{
			volume += 10 * direction;
			if (volume > 100)
			{
				volume = 100;
			}
			if (volume < 0)
			{
				volume = 0;
			}
		}
	}
	if (volume != oldVolume)
	{
		Cvars_SetAsInt(cvar, volume);
	}
	return returnValue;
}
void MenuFunc_VideoVsyncToggle()
{
	//TODO C99 Utils_ToggleVsyncButton();
}
void MenuFunc_InputRumbleToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_RUMBLE_DISABLED);
	if (!Cvars_GetAsBool(CVARS_USER_IS_RUMBLE_DISABLED))
	{
		InputPlayer_Vibrate(Input_GetPlayerOne(), 0, 10, 0.5f, 0.5f);
	}
}
void MenuFunc_VideoShowFpsToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_SHOWING_FPS);
}
void MenuFunc_VideoShowInGameTimerToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_SHOWING_IN_GAME_TIMER);
}
void MenuFunc_VideoInternalResolutionMultipleToggle(int direction, int32_t forcedSliderValue)
{
	int maxValue = MenuFunc_GetVideoInternalResolutionMultipleToggleMaxValue();
	int current = Cvars_GetAsInt(CVARS_USER_INTERNAL_RESOLUTION_MULTIPLE);
	int old = current;
	if (forcedSliderValue != -1)
	{
		current = (int)(maxValue * (forcedSliderValue / 100.0f));
	}
	else if (direction != 0)
	{
		current += direction;
		if (current > maxValue)
		{
			current = maxValue;
		}
		if (current < 0)
		{
			current = 0;
		}
	}
	else
	{
		current++;
		if (current > maxValue)
		{
			current = 0;
		}
		if (current < 0)
		{
			current = maxValue;
		}
	}
	if (current != old)
	{
		Cvars_SetAsInt(CVARS_USER_INTERNAL_RESOLUTION_MULTIPLE, current);
		Renderer_ApplyChanges();
	}
}
int MenuFunc_GetVideoInternalResolutionMultipleToggleMaxValue()
{
	int value = MenuFunc_GetVideoChangeWindowSizeMultipleMaxValue();
	value++;
	int min = Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_RESOLUTION_MUL_MAX_MIN);
	if (value < min)
	{
		value = min;
	}
	return value;
}
int MenuFunc_GetVideoChangeWindowSizeMultipleMaxValue()
{
	Rectangle displayBounds = Window_GetDisplayBounds();
	int width = 1280; //TODO C99 Utils_GetWindowSizeMulWidth();
	int height = 720; //TODO C99  Utils_GetWindowSizeMulHeight();
	int maxWidth = displayBounds.Width / width;
	int maxHeight = displayBounds.Height / height;
	int maxValue = maxWidth > maxHeight ? maxHeight : maxWidth;
	if (maxValue * width == displayBounds.Width && maxValue * height == displayBounds.Height) //don't show a perfect match resolution
	{
		maxValue--;
	}
	if (maxValue < 1)
	{
		maxValue = 1;
	}
	return maxValue;
}
void MenuFunc_VideoLinearFilterToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_LINEAR_FILTER_ALLOWED);
}
void MenuFunc_SoundMuteOnFocusToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_MUTE_ON_FOCUS_LOSS);
}
void MenuFunc_GamePauseOnFocusToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_PAUSE_ON_FOCUS_LOSS);
}
void MenuFunc_GameTurboModeToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_TURBO_MODE);
}
void MenuFunc_GameToggleAltFont()
{
	Cvars_FlipAsBool(CVARS_USER_IS_USING_ALT_FONT);
}
void MenuFunc_InputResetBindings()
{
	InputBindings_ResetAllPlayerBindingsToDefaultAndSave();
}
void MenuFunc_ActionResumeGame()
{
	GameStateManager_SetGameState(GAMESTATEMANAGER_GAME_STATE_NORMAL);
	Do_ResumeMusic(1);
	Do_ResumeAllSounds(1);
}
void MenuFunc_ActionExitGame()
{
	Game_Exit();
}
void MenuFunc_ActionLoadLevel(const char* level)
{
	GameStateManager_SetupLoadMap(level);
}
void MenuFunc_GameBorderFrameToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_BORDER_FRAME_ON);
}
void MenuFunc_GameScreenshakeToggle()
{
	Cvars_FlipAsBool(CVARS_USER_IS_SCREENSHAKE_DISABLED);
}
void MenuFunc_ActionLoadSaveSlot(const char* save, const char* level)
{
	int saveSlot = Utils_ParseInt(save);
	//OeGameSaveManager_SetSaveSlot(saveSlot);
	GameStateManager_SetupLoadMap(level);
}
void MenuFunc_VideoRefreshSyncToggle()
{
}
void MenuFunc_VideoDrawModeToggle(int direction)
{
	int current = Cvars_GetAsInt(CVARS_USER_DRAW_MODE);
	current += direction;
	if (current > RENDERER_DRAWMODE_END_OF_NORMAL_OPTIONS)
	{
		current = 0;
	}
	if (current < 0)
	{
		current = RENDERER_DRAWMODE_END_OF_NORMAL_OPTIONS;
	}
	Cvars_SetAsInt(CVARS_USER_DRAW_MODE, current);
}
void MenuFunc_InputControllerTypeToggle()
{
	int current = Cvars_GetAsInt(CVARS_USER_CONTROLLER_TYPE);
	current += 1;
	if (current > INPUT_CONTROLLER_GLYPH_P4)
	{
		current = INPUT_CONTROLLER_GLYPH_X;
	}
	Cvars_SetAsInt(CVARS_USER_CONTROLLER_TYPE, current);
}
void MenuFunc_GameBorderToggle()
{
	int current = Cvars_GetAsInt(CVARS_USER_BORDER_TYPE);
	current += 1;
	if (current > Cvars_GetAsInt(CVARS_ENGINE_MAX_BORDERS))
	{
		current = -1;
	}
	Cvars_SetAsInt(CVARS_USER_BORDER_TYPE, current);
}
void MenuFunc_VideoFullscreenToggle()
{
	//TODO C99 Utils_ToggleFullscreenButton();
}
void MenuFunc_PlayMenuSoundSelect()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_SELECT_SOUND));
}
void MenuFunc_PlayMenuSoundDeny()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_DENY_SOUND));
}
void MenuFunc_PlayMenuSoundUp()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_UP_SOUND));
}
void MenuFunc_PlayMenuSoundRight()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_RIGHT_SOUND));
}
void MenuFunc_PlayMenuSoundDown()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_DOWN_SOUND));
}
void MenuFunc_PlayMenuSoundLeft()
{
	MenuFunc_PlayMenuSoundHelper(Cvars_Get(CVARS_ENGINE_DEFAULT_MENU_LEFT_SOUND));
}
void MenuFunc_PlayMenuSoundHelper(const char* soundToPlay)
{
	if (SUPPRESS_MENU_SOUNDS)
	{
		return;
	}

	if (!Utils_StringEqualTo(EE_STR_NOT_SET, soundToPlay))
	{
		Do_PlaySound(soundToPlay);
	}
}
void MenuFunc_SaveIfLoadedOptionsMenu()
{
	if (LOADED_OPTIONS_MENU)
	{
		Do_SaveGame();
		Do_SaveUserConfig();
		LOADED_OPTIONS_MENU = false;
	}
}
