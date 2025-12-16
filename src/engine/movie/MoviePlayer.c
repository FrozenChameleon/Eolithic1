#include "MoviePlayer.h"

#include "../audio/Music.h"
#include "../core/Func.h"
#include "../utils/Utils.h"
#include "../gamestate/GameStateManager.h"
#include "MovieOperationPan.h"
#include "MovieOperationShake.h"
#include "../utils/Logger.h"
#include "../render/SpriteBatch.h"
#include "../input/Input.h"
#include "../input/ActionList.h"
#include "../input/InputPlayer.h"
#include "MovieOperationText.h"
#include "../utils/Strings.h"
#include "MovieOperationWait.h"
#include "MovieOperationFadeText.h"
#include "../render/Color.h"
//#include "MovieSheetsTool.h"

static const char* KEY_SCREEN = "KEY_SCREEN";

void MoviePlayer_WriteTimings(MoviePlayer* mp)
{
	//WILLNOTDO 05152023
	/*
	if (!OeGlobals.IsDebugFileMode())
	{
	return;
	}

	if (_mUseStrictTiming)
	{
	return;
	}

	OeFile.WriteString(OeFile.Combine("data", "timings", _mMovieName + ".txt"), OeUtils_GetListToCsvString(_mTimingsToWrite));
	*/
}
void MoviePlayer_AddOperation(MoviePlayer* mp, const char* operation, IStringArray* arguments)
{
	if (Utils_StringEqualTo(operation, ("useStrictTimings")))
	{
		mp->_mUseStrictTiming = true;
	}
	else if (Utils_StringEqualTo(operation, ("showFrameTimer")))
	{
		mp->_mShowFrameTimer = true;
	}
	else if (Utils_StringEqualTo(operation, ("swapNextImage")))
	{
		MoviePlayer_OperationSwapNextImage(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("giveTime")))
	{
		MoviePlayer_OperationGiveTime(mp);
	}
	else if (Utils_StringEqualTo(operation, ("disableSpeedUp")))
	{
		mp->_mDisableSpeedUp = true;
	}
	else if (Utils_StringEqualTo(operation, ("enableSpeedUp")))
	{
		mp->_mDisableSpeedUp = false;
	}
	else if (Utils_StringEqualTo(operation, ("dispose")))
	{
		MoviePlayer_OperationRemove(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("remove")))
	{
		MoviePlayer_OperationRemove(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("text")) || Utils_StringEqualTo(operation, "mappedText"))
	{
		MoviePlayer_OperationText(mp, operation, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("fadeText")) || Utils_StringEqualTo(operation, "mappedFadeText"))
	{
		MoviePlayer_OperationFadeText(mp, operation, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("goto")))
	{
		MoviePlayer_OperationGoTo(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("loop")))
	{
		mp->_mIsEnded = true;
		GameStateManager_SetupLoadMap(Get_LevelFileName());
	}
	else if (Utils_StringEqualTo(operation, ("end")))
	{
		mp->_mIsEnded = true;
		mp->_mIsComplete = true;
		MoviePlayer_WriteTimings(mp);
	}
	else if (Utils_StringEqualTo(operation, ("pan")))
	{
		MoviePlayer_OperationPan(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("clear")))
	{
		MoviePlayer_OperationClear(mp);
	}
	else if (Utils_StringEqualTo(operation, ("playSound")))
	{
		MoviePlayer_OperationPlaySound(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("playMusic")))
	{
		MoviePlayer_OperationPlayMusic(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("fadeOutMusic")))
	{
		MoviePlayer_OperationFadeOutMusic(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("stopMusic")))
	{
		Do_StopMusic();
	}
	else if (Utils_StringEqualTo(operation, ("addImage")))
	{
		MoviePlayer_OperationAddImage(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("addScreen")))
	{
		MoviePlayer_OperationAddScreen(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("removeScreen")))
	{
		MoviePlayer_OperationRemoveScreen(mp);
	}
	else if (Utils_StringEqualTo(operation, ("addAnimation")))
	{
		MoviePlayer_OperationAddAnimation(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("wait")))
	{
		MoviePlayer_OperationWait(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("block")))
	{
		mp->_mIsBlocking = true;
	}
	else if (Utils_StringEqualTo(operation, ("stopShake")))
	{
		MoviePlayer_OperationStopShake(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("shake")))
	{
		MoviePlayer_OperationShake(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextFont")))
	{
		MoviePlayer_OperationSetTextFont(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextPosition")))
	{
		MoviePlayer_OperationSetTextPosition(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextSpeed")))
	{
		MoviePlayer_OperationSetTextSpeed(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextRate")))
	{
		MoviePlayer_OperationSetTextRate(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextWait")))
	{
		MoviePlayer_OperationSetTextWait(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextFadeRampSpeed")))
	{
		MoviePlayer_OperationSetTextFadeRampSpeed(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextFadeHoldTime")))
	{
		MoviePlayer_OperationSetTextFadeHoldTime(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setTextColor")))
	{
		MoviePlayer_OperationSetTextColor(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("newText")) || Utils_StringEqualTo(operation, ("newMappedText")))
	{
		MoviePlayer_OperationNewText(mp, operation, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("newFadeText")) || Utils_StringEqualTo(operation, ("newMappedFadeText")))
	{
		MoviePlayer_OperationNewFadeText(mp, operation, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("setNextTextColor")))
	{
		MoviePlayer_OperationSetNextTextColor(mp, arguments);
	}
	else if (Utils_StringEqualTo(operation, ("hackIgnoreNextMusicFadeOut")))
	{
		Music_SetHackToIgnoreNextFadeOutMusic(true);
	}
	else if (Utils_StringEqualTo(operation, ("setTextCentered")))
	{
		mp->_mTextData.mIsCentered = true;
	}
	else if (Utils_StringEqualTo(operation, ("setTextUncentered")))
	{
		mp->_mTextData.mIsCentered = false;
	}
}
void MoviePlayer_OperationSwapNextImage(MoviePlayer* mp, IStringArray* arguments)
{
	if (!mp->_mUseSwappedImages)
	{
		return;
	}

	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	Utils_strlcpy(mp->_mNextSwappedImage, IStringArray_Get(arguments, 0), EE_FILENAME_MAX);
}
void MoviePlayer_OperationSetNextTextColor(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	Utils_strlcpy(mp->_mNextTextData.mColor, IStringArray_Get(arguments, 0), EE_FILENAME_MAX);
}
void MoviePlayer_OperationRemove(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mImages.erase(arguments[0]);
}
void MoviePlayer_OperationGoTo(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	mp->_mIsSkipping = true;
	mp->_mSkipPoint = Utils_ParseInt(IStringArray_Get(arguments, 0));
}
void MoviePlayer_OperationPan(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 4)
	{
		return;
	}

	/*
	std_shared_ptr<MovieImage> image = _mImages[arguments[0]];
	if (image != nullptr)
	{
		_mOperations.push_back(std_shared_ptr<MovieOperation>(
			new MovieOperationPan(image,
				Vector2(OeUtils_TryParseFloat(arguments[1]), OeUtils_TryParseFloat(arguments[2])), OeUtils_TryParseInt(arguments[3]))));
	}*/
}
void MoviePlayer_OperationClear(MoviePlayer* mp)
{
	/*
	std_vector<std_string> removeThese = {};
	for (auto it = _mImages.begin(); it != _mImages.end(); it++)
	{
		if (!it->second->mIsPermanent)
		{
			removeThese.push_back(it->first);
		}
	}

	for (int i = 0; i < removeThese.size(); i++)
	{
		_mImages.erase(removeThese[i]);
	}

	_mOperations.clear();*/
}
void MoviePlayer_OperationPlaySound(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	Do_PlaySound(IStringArray_Get(arguments, 0));
}
void MoviePlayer_OperationPlayMusic(MoviePlayer* mp, IStringArray* arguments)
{
	/*
	if (IStringArray_Length(arguments) == 1)
	{
		Do_PlayMusic(arguments[0], true, false);
	}
	else if (IStringArray_Length(arguments) == 5)
	{
		Do_PlayMusic(arguments[0], true, false, OeUtils_TryParseBoolean(arguments[1]), OeUtils_TryParseInt(arguments[2]), OeUtils_TryParseBoolean(arguments[3]),
			OeUtils_TryParseInt(arguments[4]));
	}
	*/
}
void MoviePlayer_OperationFadeOutMusic(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 Do_FadeOutMusic(OeUtils_TryParseInt(arguments[0]));
}
void MoviePlayer_OperationAddImage(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 5)
	{
		return;
	}
	/*
	std_string key = arguments[0];
	std_string strImage = arguments[1];
	if (_mUseSwappedImages && (_mNextSwappedImage != STR_NOTHING))
	{
		strImage = _mNextSwappedImage;
		_mNextSwappedImage = STR_NOTHING;
	}
	std_shared_ptr<MovieImage> image = std_shared_ptr<MovieImage>(new MovieImage(_mScale, strImage));
	float depth = OeUtils_TryParseFloat(arguments[2]);
	image->mDepth = (int)(depth * 100);
	image->mPosition = Vector2(OeUtils_TryParseInt(arguments[3]), OeUtils_TryParseInt(arguments[4]));
	if (IStringArray_Length(arguments) == 6)
	{
		image->mIsPermanent = OeUtils_TryParseBoolean(arguments[5]);
	}
	_mImages[key] = image;*/
}
void MoviePlayer_OperationAddScreen(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	/*int waitTime = 0;
	if (IStringArray_Length(arguments) >= 2)
	{
		waitTime = Utils_ParseInt(IStringArray_Get(arguments, 1));
	}

	const char* image = IStringArray_Get(arguments, 0);
	std_shared_ptr<MovieImage> movieImage = std_shared_ptr<MovieImage>(new MovieImage(_mScale, image));
	movieImage->mDepth = 50;
	_mImages[KEY_SCREEN] = movieImage;
	if (waitTime > 0)
	{
		_mIsWaiting = true;
		_mOperations.push_back(std_shared_ptr<MovieOperation>(
			new MovieOperationWait(waitTime)));
	}*/
}
void MoviePlayer_OperationNewText(MoviePlayer* mp, const char* operation, IStringArray* arguments)
{
	if ((IStringArray_Length(arguments) < 1) || (Utils_StringEqualTo(mp->_mTextData.mFont, EE_STR_EMPTY)))
	{
		return;
	}

	/*
	std_string str = arguments[0];
	bool isMappedText = false;
	if (Utils_StringEqualTo(operation, ("newMappedText"))
	{
		isMappedText = true;
	}
	_mOperations.push_back(std_shared_ptr<MovieOperation>(new MovieOperationText(isMappedText, str, _mTextData.mFont, _mTextData.mPosition,
		_mTextData.mSpeed, _mTextData.mRate, _mTextData.mWait, GetCurrentTextColor(), _mTextData.mIsCentered)));
		_mNextTextData = NewMovieTextData();*/
}
void MoviePlayer_OperationNewFadeText(MoviePlayer* mp, const char* operation, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	/*std_string str = arguments[0];
	if (Utils_StringEqualTo(operation, ("newMappedFadeText"))
	{
		str = OeStrings_Get(str);
	}
	_mOperations.push_back(std_shared_ptr<MovieOperation>(new MovieOperationFadeText(str, _mTextData.mFont, _mTextData.mPosition,
		_mTextData.mFadeRampSpeed, _mTextData.mFadeHoldTime, _mTextData.mIsCentered)));
		_mNextTextData = NewMovieTextData();*/
}
const char* MoviePlayer_GetCurrentTextColor(MoviePlayer* mp)
{
	return NULL;
	/*std_string color = _mTextData.mColor;
	if (_mNextTextData.mColor != STR_NOTHING)
	{
		color = _mNextTextData.mColor;
	}
	return color;*/
}
void MoviePlayer_OperationSetTextFont(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	Utils_strlcpy(mp->_mTextData.mFont, IStringArray_Get(arguments, 0), EE_FILENAME_MAX);
}
void MoviePlayer_OperationSetTextPosition(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 2)
	{
		return;
	}

	//TODO C99 mp->_mTextData.mPosition = Vector2_Create(Utils_ParseInt(IStringArray_Get(arguments, 0)), Utils_ParseInt(IStringArray_Get(arguments, 1));
}
void MoviePlayer_OperationSetTextSpeed(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mSpeed = OeUtils_TryParseInt(arguments[0]);
}
void MoviePlayer_OperationSetTextRate(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mRate = OeUtils_TryParseInt(arguments[0]);
}
void MoviePlayer_OperationSetTextWait(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mWait = OeUtils_TryParseInt(arguments[0]);
}
void MoviePlayer_OperationSetTextFadeRampSpeed(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mFadeRampSpeed = OeUtils_TryParseInt(arguments[0]);
}
void MoviePlayer_OperationSetTextFadeHoldTime(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mFadeHoldTime = OeUtils_TryParseInt(arguments[0]);
}
void MoviePlayer_OperationSetTextColor(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mTextData.mColor = arguments[0];
}
void MoviePlayer_OperationRemoveScreen(MoviePlayer* mp)
{
	/*
	if (_mImages.count(KEY_SCREEN))
	{
		_mImages.erase(KEY_SCREEN);
	}*/
}
void MoviePlayer_OperationAddAnimation(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 7)
	{
		return;
	}

	/*std_string key = arguments[0];
	std_string baseImage = arguments[1];
	if (_mUseSwappedImages && (_mNextSwappedImage != STR_NOTHING))
	{
		baseImage = _mNextSwappedImage;
		_mNextSwappedImage = STR_NOTHING;
	}
	int frames = OeUtils_TryParseInt(arguments[2]);
	int flip = OeUtils_TryParseInt(arguments[3]);

	std_shared_ptr<MovieImage> image = std_shared_ptr<MovieImage>(new MovieImage(_mScale, baseImage, frames, flip));

	float depth = OeUtils_TryParseFloat(arguments[4]);
	image->mDepth = (int)(depth * 100);
	image->mPosition = Vector2(OeUtils_TryParseInt(arguments[5]), OeUtils_TryParseInt(arguments[6]));

	if (IStringArray_Length(arguments) >= 8)
	{
		image->mIsPermanent = OeUtils_TryParseBoolean(arguments[7]);
	}

	if (IStringArray_Length(arguments) >= 9)
	{
		image->SetIsLoopingDisabled(OeUtils_TryParseBoolean(arguments[8]));
	}

	if (IStringArray_Length(arguments) >= 10)
	{
		image->SetLoopPoint(OeUtils_TryParseInt(arguments[9]));
	}

	_mImages[key] = image;*/
}
void MoviePlayer_OperationWait(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 _mIsWaiting = true;
	//TODO C99 _mOperations.push_back(std_shared_ptr<MovieOperation>(new MovieOperationWait(OeUtils_TryParseInt(arguments[0]))));
}
void MoviePlayer_OperationStopShake(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 1)
	{
		return;
	}

	//TODO C99 Broadcast("shake", arguments[0]);
}
void MoviePlayer_OperationShake(MoviePlayer* mp, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 4)
	{
		return;
	}

	/*std_string strImage = arguments[0];
	std_shared_ptr<MovieImage> image = _mImages[strImage];
	if (image != nullptr)
	{
		int min = OeUtils_TryParseInt(arguments[1]);
		int max = OeUtils_TryParseInt(arguments[2]);
		int time = OeUtils_TryParseInt(arguments[3]);
		_mOperations.push_back(std_shared_ptr<MovieOperation>(
			new MovieOperationShake(strImage, image, min, max, time)));
	}*/
}
void MoviePlayer_OperationText(MoviePlayer* mp, const char* operation, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 6)
	{
		return;
	}

	/*MovieTextData textData = GetTextData(arguments);
	std_string str = arguments[0];
	bool isMappedText = false;
	if (Utils_StringEqualTo(operation, "mappedText")
	{
		isMappedText = true;
	}
	int wait = 0;
		if (IStringArray_Length(arguments) >= 7)
		{
			wait = OeUtils_TryParseInt(arguments[6]);
		}
	std_string color = "WHITE";
		if (IStringArray_Length(arguments) >= 8)
		{
			color = arguments[7];
		}
	_mOperations.push_back(std_shared_ptr<MovieOperation>(new MovieOperationText(isMappedText, str, textData.mFont,
		textData.mPosition, textData.mSpeed, textData.mRate, wait, color, false)));*/
}
void MoviePlayer_OperationGiveTime(MoviePlayer* mp)
{
	//TODO C99 OeLogger_LogInformation(std_to_string(_mFrameCounter));
}
MovieTextData MoviePlayer_GetTextData(MoviePlayer* mp, IStringArray* arguments)
{
	MovieTextData temp;
	return temp;
	/*MovieTextData textData = MovieTextData();
	if (IStringArray_Length(arguments) >= 2)
	{
		textData.mFont = arguments[1];
	}
	if (IStringArray_Length(arguments) >= 4)
	{
		textData.mPosition = Vector2(OeUtils_TryParseInt(arguments[2]), OeUtils_TryParseInt(arguments[3]));
	}
	if (IStringArray_Length(arguments) >= 5)
	{
		textData.mSpeed = OeUtils_TryParseInt(arguments[4]);
	}
	if (IStringArray_Length(arguments) >= 6)
	{
		textData.mRate = OeUtils_TryParseInt(arguments[5]);
	}
	return textData;*/
}
void MoviePlayer_OperationFadeText(MoviePlayer* mp, const char* operation, IStringArray* arguments)
{
	if (IStringArray_Length(arguments) < 6)
	{
		return;
	}

	/*MovieFadeTextData fadeTextData = GetFadeTextData(arguments);
	std_string str = arguments[0];
	if (Utils_StringEqualTo(operation, ("mappedFadeText"))
	{
		str = OeStrings_Get(str);
	}
	_mOperations.push_back(std_shared_ptr<MovieOperation>(new MovieOperationFadeText(str, fadeTextData.mFont, fadeTextData.mPosition, fadeTextData.mRampSpeed,
		fadeTextData.mHoldTime, false)));*/
}
MovieFadeTextData MoviePlayer_GetFadeTextData(MoviePlayer* mp, IStringArray* arguments)
{
	MovieFadeTextData temp;
	return temp;
	/*MovieFadeTextData fadeTextData = MovieFadeTextData();
	if (IStringArray_Length(arguments) >= 2)
	{
		fadeTextData.mFont = arguments[1];
	}
	if (IStringArray_Length(arguments) >= 4)
	{
		fadeTextData.mPosition = Vector2(OeUtils_TryParseInt(arguments[2]), OeUtils_TryParseInt(arguments[3]));
	}
	if (IStringArray_Length(arguments) >= 5)
	{
		fadeTextData.mRampSpeed = OeUtils_TryParseInt(arguments[4]);
	}
	if (IStringArray_Length(arguments) >= 6)
	{
		fadeTextData.mHoldTime = OeUtils_TryParseInt(arguments[5]);
	}
	return fadeTextData;*/
}
void MoviePlayer_Broadcast(MoviePlayer* mp, const char* key, const char* value)
{
	/*for (int i = 0; i < _mOperations.size(); i++)
	{
		_mOperations[i]->Broadcast(key, value);
	}*/
}

void MoviePlayer_Init(MoviePlayer* mp, bool useSwappedImages, int scale, const char* movieName)
{
	Utils_memset(mp, 0, sizeof(MoviePlayer));

	//TODO C99 MovieSheetsTool_Init();

	Utils_strlcpy(mp->_mMovieName, movieName, EE_FILENAME_MAX);

	mp->_mUseSwappedImages = useSwappedImages;

	Utils_strlcpy(mp->_mTextData.mFont, "game", EE_FILENAME_MAX);
	Utils_strlcpy(mp->_mTextData.mColor, "WHITE", EE_FILENAME_MAX);

	mp->_mScale = scale;

	//TODO C99
	/*
	if (!OeResourceManagers_MovieManager.HasResource(movieName))
	{
		mp->_mIsComplete = true;
	}
	else
	{
		const char* fileString = OeResourceManagers_MovieManager.GetResourceData(movieName)->mMovieData;
		OeFile_ConvertBigStringToStrings(fileString, _mReader);
		if (OeResourceManagers_MovieTimingManager.HasResource(movieName))
		{
			_mTimingsToUse = OeResourceManagers_MovieTimingManager.GetResourceData(movieName)->mTimings;
		}
	}*/
}

void MoviePlayer_DisableSpeedUp(MoviePlayer* mp)
{
	mp->_mDisableSpeedUp = true;
}
void MoviePlayer_SetComplete(MoviePlayer* mp)
{
	mp->_mIsComplete = true;
	//TODO C99 _mOperations.clear();
}
bool MoviePlayer_IsComplete(MoviePlayer* mp)
{
	return 	mp->_mIsComplete;
}
void MoviePlayer_Update(MoviePlayer* mp)
{
	MoviePlayer_Update2(mp, false);
}
void MoviePlayer_Update2(MoviePlayer* mp, bool doNotAllowMovieSkip)
{
	if (!doNotAllowMovieSkip)
	{
		if (Input_IsTappedByAnyPlayer(ACTIONLIST_GAME_START) || Input_IsEscapeTapped())
		{
			MoviePlayer_SetComplete(mp);
			return;
		}
	}

	/*bool hasLoggedTime = false;
	bool waitBecauseOfStrictTimings = false;
	if (mp->_mUseStrictTiming)
	{
		if (_mTimingsToUse.size() == 0)
		{
			OeLogger_LogInformation("No timings to use, cannot use strict timing");
			_mUseStrictTiming = false;
		}
	}
	if (mp->_mUseStrictTiming)
	{
		int targetTime = _mTimingsToUse[_mCurrentTiming];
		if (mp->_mFrameCounter != targetTime)
		{
			waitBecauseOfStrictTimings = true;
		}
		if (mp->_mFrameCounter > targetTime)
		{
			OeLogger_LogInformation("Frame counter over target time, cannot continue movie");
			if (_mFrameCounter > targetTime + (60 * 5))
			{
				mp->_mIsComplete = true;
			}
		}
	}
	while (!mp->_mIsWaiting && !mp->_mIsBlocking && !mp->_mIsEnded && !waitBecauseOfStrictTimings)
	{
		if (!hasLoggedTime)
		{
			_mTimingsToWrite.push_back(_mFrameCounter);
			mp->_mCurrentTiming++;
			hasLoggedTime = true;
		}

		std_string line = _mReader[_mReaderLoc];
		_mReaderLoc++;

		bool skip = false;
		if (mp->_mIsSkipping)
		{
			if (mp->_mSkipPoint != mp->_mCounter)
			{
				skip = true;
			}
			else
			{
				mp->_mIsSkipping = false;
			}
		}

		if ((line != EE_STR_EMPTY) && !skip)
		{
			if (!OeUtils_StringContains(line, "//"))
			{
				if (mp->_mIsStarted)
				{
					if (OeUtils_StringContains(line, "(") && OeUtils_StringContains(line, ")"))
					{
						int firstIndex = OeUtils_StringIndexOf(line, '(');
						//int secondIndex = OeUtils_StringIndexOf(line, ')');
						std_string operation = line.substr(0, firstIndex);
						std_string argumentString = line.substr(firstIndex + 1, line.size() - firstIndex - 2);
						std_vector<std_string> arguments = {};
						Utils_GetSplitCSV(argumentString, arguments);
						AddOperation(operation, arguments);
					}
				}

				if (line == ("begin()"))
				{
					mp->_mIsStarted = true;
				}
			}
		}

		mp->_mCounter++;
	}

	if (!mp->_mIsEnded)
	{
		for (auto it = _mImages.begin(); it != _mImages.end(); it++)
		{
			it->second->Update();
		}

		bool speedUp = false;
		if (OeInput_IsTappedByAnyPlayer(OeActionList_GAME_MENU_SELECT) && !_mDisableSpeedUp)
		{
			speedUp = true;
		}

		bool allOperationsComplete = true;
		bool allWaitingOperationsComplete = true;
		for (int i = 0; i < _mOperations.size(); i++)
		{
			MovieOperation* op = _mOperations[i].get();

			if (!op->IsComplete())
			{
				if (speedUp)
				{
					op->SpeedUp();
				}

				op->Update();

				if (!op->DoesNotBlock())
				{
					if (op->ForcesWait())
					{
						allWaitingOperationsComplete = false;
					}
					allOperationsComplete = false;
				}
			}
		}

		if (allWaitingOperationsComplete)
		{
			mp->_mIsWaiting = false;
		}
		if (allOperationsComplete)
		{
			mp->_mIsBlocking = false;
		}
	}

	mp->_mFrameCounter++;*/
}
void MoviePlayer_DrawHud(MoviePlayer* mp, SpriteBatch* spriteBatch)
{
	/*for (int i = 0; i < _mOperations.size(); i++)
	{
		_mOperations[i]->DrawHud(spriteBatch);
	}

	for (auto it = _mImages.begin(); it != _mImages.end(); it++)
	{
		it->second->DrawHud(spriteBatch);
	}*/

#if EDITOR
	//TODO C99
	/*
	int targetY = 150;
	spriteBatch->DrawString("game", std_to_string(_mFrameCounter), OeColors_YELLOW, 200, Vector2(0, targetY));
	spriteBatch->DrawString("game", std_to_string(_mFrameCounter / 60), OeColors_YELLOW, 200, Vector2(0, targetY + 16));
	if (_mUseStrictTiming)
	{
		spriteBatch->DrawString("game", "STRICT", OeColors_YELLOW, 200, Vector2(0, targetY + 32));
	}*/
#endif
}
