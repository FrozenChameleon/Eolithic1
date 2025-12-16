#pragma once

#include "PlaySound.h"
#include "Pause.h"
#include "MovieOperation.h"
#include "../render/Color.h"
#include "../utils/Timer.h"
#include "../math/Vector2.h"

#define AMOUNT_OF_MOVIE_PAUSES 16
#define AMOUNT_OF_MOVIE_PLAY_SOUNDS 16

typedef struct SpriteBatch SpriteBatch;

extern char mTextTypeSound[EE_FILENAME_MAX];

typedef struct MovieOperationText
{
	int32_t mType;
	bool mIsComplete;
	Pause* mPauses;
	PlaySound* mPlaySounds;
	Timer mTimerAddText;
	Timer mTimerWait;
	Vector2 mPosition;
	int32_t mIndex;
	int32_t mRate;
	char mTotalString[EE_FILENAME_MAX];
	char mCurrentString[EE_FILENAME_MAX];
	bool mStringShown;
	char mFont[EE_FILENAME_MAX];
	bool mIsPaused;
	Color mColor;
	bool mIsSpeedIncreased;
	int32_t mSpeedIncreaseCounter;
	bool mIsCentered;
} MovieOperationText;

int MovieOperationText_GetSpeedToIncrease(MovieOperationText* text);
void MovieOperationText_EndUpdate(MovieOperationText* text);
void MovieOperationText_NormalUpdate(MovieOperationText* text);
void MovieOperationText_TextCommandsCheck(MovieOperationText* text, int point);

void MovieOperationText_Init(MovieOperationText* text, bool isMappedText, const char* str, const char* font, Vector2 position, 
	int speed, int rate, int wait, const char* color, bool isTextCentered);

void MovieOperationText_SpeedUp(MovieOperationText* text);
void MovieOperationText_Update(MovieOperationText* text);
void MovieOperationText_DrawHud(MovieOperationText* text, SpriteBatch* spriteBatch);
static void MovieOperationText_SetTextTypeSound(MovieOperationText* text, const char* sound);
