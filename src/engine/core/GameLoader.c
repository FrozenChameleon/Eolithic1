#include "GameLoader.h"

#include "../../third_party/stb_ds.h"
#include "../achievement/AchievementHandler.h"
#include "../core/GameHelper.h"
#include "../core/Game.h"
#include "../utils/Cvars.h"
#include "../utils/Strings.h"
#include "../gamestate/GameStateManager.h"
#include "../audio/SoundEffect.h"
#include "../globals/Globals.h"
#include "../render/Sheet.h"
#include "../render/Animation.h"
#include "../audio/SoundEffect.h"
#include "../audio/Music.h"
#include "../utils/Utils.h"
#include "../utils/Logger.h"
#include "../audio/VolumeData.h"
#include "../utils/Timer.h"
#include "../render/SpriteBatch.h"
#include "../render/Renderer.h"
#include "../render/DrawTool.h"
#include "../utils/Cvars.h"
#include "../service/Service.h"
#include "../resources/AnimTileManager.h"
#include "../resources/BmFontManager.h"
#include "../resources/LevelDataManager.h"
#include "../resources/MusicManager.h"
#include "../resources/ParticleManager.h"
#include "../resources/PropManager.h"
#include "../resources/ShaderProgramManager.h"
#include "../resources/SoundEffectManager.h"
#include "../resources/TextureManager.h"
#include "../resources/TextureFontManager.h"
#include "../resources/TextureMovieManager.h"
#include "../resources/TextureOffsetManager.h"
#include "../resources/ThingSettingsManager.h"
#include "../resources/TilesetOffsetManager.h"
#include "../resources/MovieManager.h"
#include "../resources/MovieTimingManager.h"
#include "../resources/TTFontManager.h"

enum
{
	FPS_TARGET_FOR_HIGH_FPS = 75
};

enum Step
{
	STEP_LOADING = 0,
	STEP_TEST_FPS = 1,
	STEP_BLINK = 2,
	STEP_FADE_OUT = 3,
	STEP_WAIT_ON_SERVICE = 4
};

typedef bool (*JobFunc)();

static int32_t _mFps;
static int32_t _mStep;
static int32_t _mPreloaderGraphicFrame;
static double _mDeltaAccumulator;
static double _mFlipDeltaAccumulator;
static bool _mIsFirstFrame = true;
static bool _mIsLoading = true;
static Timer _mBlinkTimer = { 0, 60 };
static Timer _mFadeOutTimer = { 0, 60 };
static Texture* _mPreloaderTextureFinalToDisplay;
static Texture* _mPreloaderTextureFinal;
static Texture* _mPreloaderTextureFinalB;
static Texture** arr_preloader_textures;
static JobFunc* arr_loading_jobs;

static void DisposeTextures()
{
	_mPreloaderTextureFinalToDisplay = NULL;
	_mPreloaderTextureFinal = NULL;
	_mPreloaderTextureFinalB = NULL;
	arrsetlen(arr_preloader_textures, 0);
}
static void UpdateLoadingJob()
{
	if (arr_loading_jobs[0]())
	{
		arrdel(arr_loading_jobs, 0);
	}
}
static void FinishLoading()
{
#if EDITOR
	//WILLNOTDO 06142023
	/*
	GuiThingViewer.Init();
	Editor.Init();
	EditorPart.Init();
	Logger.LogInformation("Editor loaded");
	*/
#endif

	GameStateManager_SetGameState2(GAMESTATEMANAGER_GAME_STATE_NORMAL, true);

	Globals_SetAsGameLoaded();

	_mIsLoading = false;
}
static void QuickStart()
{
	while (arrlen(arr_loading_jobs) > 0)
	{
		UpdateLoadingJob();
	}
	FinishLoading();
}
static void LoadTextures()
{
	/*
	for (int i = 0; i < 99; i += 1)
	{
		const char* preloader = "preloader_" + std_to_string(i) + ".png";
		const char* path = File_Combine("data", preloader);
		if (File_Exists(path))
		{
			Texture* tex = Renderer_GetTextureData(path, File_ReadAll(path));
			arrput(arr_preloader_textures, tex);
		}
		else
		{
			break;
		}
	}
	*/

	/*
	SharedFixedChar260* fixedChar = Utils_CreateSharedFixedChar260();
	const char* fileFinalPath = File_Combine2(fixedChar, "data", "preloaderFinal.png");
	if (File_Exists(fileFinalPath))
	{
		_mPreloaderTextureFinal = Renderer_GetTextureData(fileFinalPath, File_ReadAll(fileFinalPath));
	}
	_mPreloaderTextureFinalToDisplay = _mPreloaderTextureFinal;

	const char* fileFinalBPath = File_Combine("data", "preloaderFinalB.png");
	if (File_Exists(fileFinalBPath))
	{
		_mPreloaderTextureFinalB = Renderer_GetTextureData(fileFinalBPath, File_ReadAll(fileFinalBPath));
	}
	*/
}
static bool LoadStart()
{
	GameHelper_CreateGlobalSystems();
	GameHelper_CreateStateSystems();
	/*for (int i = 0; i < GameStateManager_StateSystems.size(); i += 1)
	{
		GameStateManager_StateSystems[i]->InitStringSettingsHere();
	}*/
	GameHelper_OnLoadingStart();
	GameHelper_SetupPlatformTypes();
	Strings_Init();
	//ResourceManagers_CreateManagers();
	//Tuning_SetCurrentDifficulty(Cvars_GetAsInt(CVARS_ENGINE_DEFAULT_DIFFICULTY));
	Logger_LogInformation("Loading started");
	return true;
}
static bool LoadResources()
{
	AnimTileManager_LoadAllFromDat();
	BmFontManager_LoadAllFromDat();
	MusicManager_LoadAllFromDat();
	ParticleManager_LoadAllFromDat();
	PropManager_LoadAllFromDat();
	ShaderProgramManager_LoadAllFromDat();
	SoundEffectManager_LoadAllFromDat();
	TextureManager_LoadAllFromDat();
	TextureFontManager_LoadAllFromDat();
	TextureMovieManager_LoadAllFromDat();
	TextureOffsetManager_LoadAllFromDat();
	TTFontManager_LoadAllFromDat();
	TilesetOffsetManager_LoadAllFromDat();
	ThingSettingsManager_LoadAllFromDat();
	MovieManager_LoadAllFromDat();
	MovieTimingManager_LoadAllFromDat();
	LevelDataManager_LoadAllFromDat();
	return true;
}
static bool LoadAfterResources()
{
	Sheet_BuildSheets();
	Animation_BuildAnimations();
	GameHelper_BuildAchievementList();
	//SoundEffect_GetVolumeData()->Load();
	//Music_GetVolumeData()->Load();
	GameHelper_InitPoolsForEngine();
	GameHelper_InitPoolsForGame();
	GameHelper_OnLoadingAfterResources();
	return true;
}
static bool LoadGameStates()
{
	GameHelper_CreateGameStates();
	Logger_LogInformation("Game states loaded");
	return true;
}
static bool LoadEnd()
{
	//TODO C99 Game_RunServiceCheckRoutine();
	Logger_LogInformation("Loading complete");
	return true;
}
static void SetupLoadingJobs()
{
	arrput(arr_loading_jobs, LoadStart);
	arrput(arr_loading_jobs, LoadResources);
	arrput(arr_loading_jobs, LoadAfterResources);
	arrput(arr_loading_jobs, LoadGameStates);
	arrput(arr_loading_jobs, LoadEnd);
}
static void HandleFps()
{
	Logger_printf("Frame rate was %i", _mFps);

	if (!Cvars_GetAsBool(CVARS_USER_IS_FIXED_TIMESTEP_ENABLED) || !Cvars_GetAsBool(CVARS_USER_IS_VSYNC))
	{
		return;
	}

	if (_mFps >= FPS_TARGET_FOR_HIGH_FPS) //broad test
	{
		Logger_LogInformation("High hz detected, turning fixed time step off");
		Cvars_SetAsBool(CVARS_USER_IS_FIXED_TIMESTEP_ENABLED, false);
		Cvars_SaveUserConfig(false);
	}
}
static void UpdatePreloaderGraphic(double delta)
{
	if (arrlen(arr_preloader_textures) <= 0)
	{
		return;
	}

	_mFlipDeltaAccumulator += delta;
	double flipTime = 1.0 / 4.0;
	if (_mFlipDeltaAccumulator >= flipTime)
	{
		_mPreloaderGraphicFrame += 1;
		if (_mPreloaderGraphicFrame > (arrlen(arr_preloader_textures) - 1))
		{
			_mPreloaderGraphicFrame = 0;
		}
		_mFlipDeltaAccumulator -= flipTime;
	}
}
static void StepLoading(double delta)
{
	UpdatePreloaderGraphic(delta);

	if (arrlen(arr_loading_jobs) > 0)
	{
		UpdateLoadingJob();
	}
	else
	{
		if (Service_IsWaitingOnServiceToFinishLoading(delta))
		{
			_mStep = STEP_WAIT_ON_SERVICE;
		}
		else if (!Globals_NeedToTestFrameRate())
		{
			_mStep = STEP_BLINK;
		}
		else
		{
			Logger_LogInformation("It is the first load, testing frame rate");
			_mStep = STEP_TEST_FPS;
		}
	}
}
static void StepTestFPS(double delta)
{
	UpdatePreloaderGraphic(delta);

	_mDeltaAccumulator += delta;
	if (_mDeltaAccumulator >= 1)
	{
		HandleFps();
		_mDeltaAccumulator = 0;
		_mStep = STEP_BLINK;
	}
	else
	{
		_mFps += 1;
	}
}
static void StepBlink(double delta, double tickTime)
{
	_mDeltaAccumulator += delta;
	if (_mDeltaAccumulator >= tickTime)
	{
		if (_mBlinkTimer.mCurrent == 0)
		{
			SoundEffect_PlaySound("preloaderBlink");
		}
		if (_mBlinkTimer.mCurrent == 10)
		{
			if (_mPreloaderTextureFinalB != NULL)
			{
				_mPreloaderTextureFinalToDisplay = _mPreloaderTextureFinalB;
			}
		}
		if (Timer_Update(&_mBlinkTimer))
		{
			_mStep = STEP_FADE_OUT;
		}
		else
		{
			_mDeltaAccumulator -= tickTime;
		}
	}
}
static void StepFadeOut(double delta, double tickTime)
{
	_mDeltaAccumulator += delta;
	if (_mDeltaAccumulator >= tickTime)
	{
		if (Timer_Update(&_mFadeOutTimer))
		{
			DisposeTextures();
			FinishLoading();
		}
		else
		{
			_mDeltaAccumulator -= tickTime;
		}
	}
}

void GameLoader_Update(double delta)
{
	if (!_mIsLoading)
	{
		return;
	}

	if (_mIsFirstFrame)
	{
		if (!Cvars_GetAsBool(CVARS_ENGINE_QUICKSTART))
		{
			LoadTextures();
		}
		SetupLoadingJobs();
		_mIsFirstFrame = false;
	}

	if (Cvars_GetAsBool(CVARS_ENGINE_QUICKSTART))
	{
		QuickStart();
		return;
	}
	else
	{
		double tickTime = 1.0 / 60.0;
		switch (_mStep)
		{
		case STEP_LOADING:
			StepLoading(delta);
			break;
		case STEP_TEST_FPS:
			StepTestFPS(delta);
			break;
		case STEP_BLINK:
			StepBlink(delta, tickTime);
			break;
		case STEP_FADE_OUT:
			StepFadeOut(delta, tickTime);
			break;
		case STEP_WAIT_ON_SERVICE:
			if (!Service_IsWaitingOnServiceToFinishLoading(delta))
			{
				_mStep = STEP_BLINK;
			}
			break;
		}
	}

	SoundEffect_Tick();
	Music_Tick();
}
static void RunShaderStutterFix(SpriteBatch* spriteBatch, Texture* tex, Vector2 offset)
{
	//Running this to preempt various pipeline states 
	Rectangle rect = { 0, 0, 32, 32 };
	for (int i = 0; i < 2; i += 1)
	{
		RenderCommandSheet* instance = SpriteBatch_Draw(spriteBatch, tex, Color_White, 0, NULL, offset, rect, Vector2_One, 0, false, false, Vector2_Zero);
		switch (i)
		{
		case 0:
			instance->mBlendState = BLENDSTATE_ADDITIVE;
			break;
		case 1:
			instance->mBlendState = BLENDSTATE_ALPHABLEND;
			break;
		}
	}
}
void GameLoader_Draw(SpriteBatch* spriteBatch)
{
	if (!_mIsLoading)
	{
		return;
	}

	if (arrlen(arr_preloader_textures) <= 0)
	{
		return;
	}

	Texture* tex = arr_preloader_textures[_mPreloaderGraphicFrame];
	if (_mStep == STEP_BLINK || _mStep == STEP_FADE_OUT)
	{
		if (_mPreloaderTextureFinalToDisplay != NULL)
		{
			tex = _mPreloaderTextureFinalToDisplay;
		}
	}
	else if (_mStep == STEP_WAIT_ON_SERVICE)
	{
		tex = _mPreloaderTextureFinalB;
	}

	int internalWidth = Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_WIDTH);
	int internalHeight = Cvars_GetAsInt(CVARS_ENGINE_INTERNAL_HEIGHT);
	Vector2 offset = { (float)(-internalWidth / 2), (float)(-internalHeight / 2) };

	if (_mStep == STEP_LOADING)
	{
		if (Service_PlatformNeedsShaderStutterFix())
		{
			RunShaderStutterFix(spriteBatch, tex, offset);
		}
	}

	Rectangle destRect = { (int)(offset.X), (int)(offset.Y), internalWidth, internalHeight };

	//TODO C99 spriteBatch->DrawRectangle(tex, Color_White, 100, NULL, destRect, tex->GetRectangle(), 0, false, false, Vector2_Zero);

	if (_mStep == STEP_FADE_OUT)
	{
		float percent = Timer_GetPercentage(&_mFadeOutTimer);
		uint8_t alpha = (uint8_t)(0xFF * percent);
		Color tempColor = { 0, 0, 0, alpha };
		DrawTool_DrawRectangle2(spriteBatch, tempColor, 100, destRect, 0, false);
	}
}
bool GameLoader_IsLoading()
{
	return _mIsLoading;
}
