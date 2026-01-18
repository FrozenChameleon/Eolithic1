#include "FontMap.h"

#include "../utils/Utils.h"
#include "../utils/Cvars.h"
#include "../../GlobalDefs.h"
#include "../../third_party/stb_ds.h"

//static int64_t _mLastWriteTime = 0;
//static int32_t _mReadCounter = 0;

static FontMapData* arr_data;
static char _mPath[EE_FILENAME_MAX];
static bool _mHasInit;

static void FillWithEfigs(IStringArray* fillThis)
{
	IStringArray_Add(fillThis, "en");
	IStringArray_Add(fillThis, "fr");
	IStringArray_Add(fillThis, "it");
	IStringArray_Add(fillThis, "de");
	IStringArray_Add(fillThis, "es");
}
static void FillWithFigs(IStringArray* fillThis)
{
	IStringArray_Add(fillThis, "fr");
	IStringArray_Add(fillThis, "it");
	IStringArray_Add(fillThis, "de");
	IStringArray_Add(fillThis, "es");
}

#ifdef GLOBAL_DEF_GAME_IS_MUTE_CRIMSON_DX
static void BuildMuteCrimsonFontReplacements()
{
	arrsetlen(arr_data, 0);

	//Originals in comments
	{
		FontMapData fontEditor;
		FontMapData_Init(&fontEditor);
		Utils_strlcpy(fontEditor.mNote, "Editor", EE_FILENAME_MAX);
		Utils_strlcpy(fontEditor.mFontName, "AnekLatin-Regular", EE_FILENAME_MAX);
		Utils_strlcpy(fontEditor.mReplace, "editor", EE_FILENAME_MAX);
		fontEditor.mFontSize = 24;
		arrput(arr_data, fontEditor);
	}

	{
		FontMapData fontCardGame1;
		FontMapData_Init(&fontCardGame1);
		Utils_strlcpy(fontCardGame1.mNote, "Card Game 1", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame1.mFontName, "Kanit-Italic", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame1.mReplace, "cardgame", EE_FILENAME_MAX);
		FillWithEfigs(fontCardGame1.mLanguages);
		fontCardGame1.mFontSize = 52;
		fontCardGame1.mLineSpacing = -20;
		fontCardGame1.mCharacterSpacing = 0;
		fontCardGame1.mOffset.X = 0;
		fontCardGame1.mOffset.Y = 0;
		fontCardGame1.mOverrideBoundsHeight = 32;
		arrput(arr_data, fontCardGame1);
	}

	{
		FontMapData fontCardGame2;
		FontMapData_Init(&fontCardGame2);
		Utils_strlcpy(fontCardGame2.mNote, "Card Game 2", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame2.mFontName, "Kanit-BoldItalic", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame2.mReplace, "cardgame2", EE_FILENAME_MAX);
		FillWithEfigs(fontCardGame2.mLanguages);
		fontCardGame2.mFontSize = 106;
		fontCardGame2.mLineSpacing = -56;
		fontCardGame2.mCharacterSpacing = 0;
		fontCardGame2.mOffset.X = 0;
		fontCardGame2.mOffset.Y = 0;
		fontCardGame2.mOverrideBoundsHeight = 54;
		arrput(arr_data, fontCardGame2);
	}

	{
		FontMapData fontCardGame3;
		FontMapData_Init(&fontCardGame3);
		Utils_strlcpy(fontCardGame3.mNote, "Card Game 3", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame3.mFontName, "Kanit-BoldItalic", EE_FILENAME_MAX);
		Utils_strlcpy(fontCardGame3.mReplace, "cardgame3", EE_FILENAME_MAX);
		FillWithEfigs(fontCardGame3.mLanguages);
		fontCardGame3.mFontSize = 86;
		fontCardGame3.mLineSpacing = -24;
		fontCardGame3.mCharacterSpacing = 0;
		fontCardGame3.mOffset.X = 0;
		fontCardGame3.mOffset.Y = 0;
		arrput(arr_data, fontCardGame3);
	}
}
#endif

/*#ifdef GLOBAL_DEF_GAME_IS_COMETSTRIKER_DX
static void BuildCometStrikerFontReplacements()
{
	_mData.clear();

	//Originals in comments
	OeFontMapData fontEditor = OeFontMapData();
	fontEditor.mNote = "Editor";
	fontEditor.mFontName = "AnekLatin-Regular";
	fontEditor.mReplace = "editor";
	fontEditor.mFontSize = 24;
	_mData.push_back(fontEditor);

	OeFontMapData fontNormalText = OeFontMapData();
	fontNormalText.mNote = "Normal Text";
	fontNormalText.mFontName = "Silkscreen-Regular";
	fontNormalText.mScaleFactor = 4;
	fontNormalText.mReplace = "6x6";
	FillWithFigs(fontNormalText.mLanguages);
	fontNormalText.mFontSize = 10;
	fontNormalText.mLineSpacing = -8;
	fontNormalText.mCharacterSpacing = -5; //-4
	fontNormalText.mOffset.Y = -2;
	fontNormalText.mOverrideBoundsHeight = 8;
	_mData.push_back(fontNormalText);

	OeFontMapData fontHUD = OeFontMapData();
	fontHUD.mNote = "HUD";
	fontHUD.mFontName = "Silkscreen-Regular";
	fontHUD.mScaleFactor = 4;
	fontHUD.mReplace = "6x6hud";
	FillWithFigs(fontHUD.mLanguages);
	fontHUD.mFontSize = 12;
	fontHUD.mCharacterSpacing = -6; //-5
	fontHUD.mOffset.X = -1;
	fontHUD.mOffset.Y = -1;
	fontHUD.mOverrideBoundsHeight = 9;
	_mData.push_back(fontHUD);

	OeFontMapData fontComboText = OeFontMapData();
	fontComboText.mNote = "Combo Text";
	fontComboText.mFontName = "Silkscreen-Bold";
	fontComboText.mScaleFactor = 4;
	fontComboText.mReplace = "6x6Outline";
	FillWithFigs(fontComboText.mLanguages);
	fontComboText.mFontSize = 10;
	fontComboText.mEffect = 2;
	fontComboText.mEffectAmount = 2;
	fontComboText.mCharacterSpacing = -6;
	fontComboText.mOffset.Y = -4;
	_mData.push_back(fontComboText);

	OeFontMapData fontCutscene = OeFontMapData();
	fontCutscene.mNote = "Cutscene";
	fontCutscene.mFontName = "Silkscreen-Regular";
	fontCutscene.mScaleFactor = 4;
	fontCutscene.mReplace = "12x12";
	FillWithFigs(fontCutscene.mLanguages);
	fontCutscene.mFontSize = 23;
	fontCutscene.mLineSpacing = -8;
	fontCutscene.mOffset.Y = -6;
	fontCutscene.mOverrideBoundsHeight = 21;
	_mData.push_back(fontCutscene);

	OeFontMapData fontGrading = OeFontMapData();
	fontGrading.mNote = "Grading";
	fontGrading.mFontName = "Silkscreen-Regular";
	fontGrading.mScaleFactor = 4;
	fontGrading.mReplace = "game";
	FillWithFigs(fontGrading.mLanguages);
	fontGrading.mFontSize = 14;
	fontGrading.mCharacterSpacing = -5; //-4
	fontGrading.mOffset.Y = -4;
	_mData.push_back(fontGrading);

	OeFontMapData fontFinalGrading = OeFontMapData();
	fontGrading.mNote = "Final Grading";
	fontFinalGrading.mFontName = "Silkscreen-Regular";
	fontFinalGrading.mScaleFactor = 4;
	fontFinalGrading.mReplace = "finalGrading";
	FillWithFigs(fontFinalGrading.mLanguages);
	fontFinalGrading.mFontSize = 24;
	fontFinalGrading.mCharacterSpacing = -7; //-6
	fontFinalGrading.mOffset.Y = -4;
	fontFinalGrading.mOverrideBoundsHeight = 20;
	_mData.push_back(fontFinalGrading);
}
#endif*/

void FontMap_Init()
{
	if (_mHasInit)
	{
		return;
	}

#ifdef GLOBAL_DEF_GAME_IS_MUTE_CRIMSON_DX
	BuildMuteCrimsonFontReplacements();
#endif

/*#ifdef GLOBAL_DEF_GAME_IS_COMETSTRIKER_DX
	BuildCometStrikerFontReplacements();
#endif*/

	_mHasInit = true;
}
const FontMapData* FontMap_GetReplacement(const char* fontName)
{
	const char* language = Utils_GetCurrentUserLanguageCode();
	if (Cvars_GetAsBool(CVARS_USER_IS_USING_ALT_FONT))
	{
		if (Utils_StringEqualTo(language, UTILS_ENGLISH_LANGUAGE_CODE))
		{
			language = UTILS_FRENCH_LANGUAGE_CODE;
		}
	}

	for (int32_t i = 0; i < arrlen(arr_data); i += 1)
	{
		FontMapData* data = &arr_data[i];
		if (IStringArray_Length(data->mLanguages) > 0)
		{
			bool contains = IStringArray_Contains(data->mLanguages, language);
			if (contains)
			{
				if ((Utils_StringEqualTo(data->mReplace, EE_STR_EMPTY)) || Utils_StringEqualTo(data->mReplace, fontName))
				{
					return data;
				}
			}
		}
	}

	return NULL;
}
/*#if EDITOR
void FontMap_Update()
{
#ifdef GLOBAL_DEF_GAME_IS_MUTE_CRIMSON_DX
	BuildMuteCrimsonFontReplacements();
#endif

#ifdef GLOBAL_DEF_GAME_IS_COMETSTRIKER_DX
	BuildCometStrikerFontReplacements();
#endif

	//WILLNOTDO 2023
	//if (!OeGlobals.IsDebugFileMode())
	//{
	//return;
	//}
	//if (OeCvars.GetAsBool(OeCvars.ENGINE_DISABLE_ASSET_REFRESH))
	//{
	//return;
	//}
	//if (OeGameUpdater.IsDebugAutoSpeedOn())
	//{
	//return;
	//}

	//if (_mReadCounter == 60 * 2)
	//{
	//int64_t currentWriteTime = OeFile.GetLastWriteTimeUtc(_mPath);
	//if (currentWriteTime != _mLastWriteTime)
	//{
	//Read();
	//}
	//_mReadCounter = 0;
	//}
	//else
	//{
	//_mReadCounter++;
	//}
}
#endif*/