#include "SpecialMcFinalBossEffectSys.h"

#include "../leveldata/ParticleInstance.h"
#include "../core/Func.h"
#include "../globals/Globals.h"
#include "../render/Color.h"
#include "../render/DrawTool.h"
#include "../render/Sheet.h"
#include "../input/Input.h"
#include "../input/InputPlayer.h"

#define BLOOD_SPRAY_DENSITY 100
#define FINAL_BOSS_DEATH 777

static void InitAfterInit(SpecialMcFinalBossEffect* data)
{
	Animation_Init(&data->mAnimation, data->mAnimationName, 5);
	Animation_ResetAnimation(&data->mAnimation);

	data->mTimerLine.mLimit = 5;
	data->mTimerBleed.mLimit = 4;
}
static void DrawRoutine(Entity owner, SpecialMcFinalBossEffect* data, SpriteBatch* spriteBatch)
{
	//TODO C99
	/*
	Sheet* sheet = Animation_GetCurrentSheet(&data->mAnimation);

	Rectangle rect = sheet->mRectangle;

	int width = rect.Width;
	int height = rect.Height;

	if (height >= data->mLineCounter)
	{
		OeSheet_DrawSourceRect(sheet, spriteBatch, OeColors_WHITE, 80, true, nullptr,
			Vector2(data->mPosition.X - (width / 4) + data->mRandomOffset.X, data->mPosition.Y - data->mLineCounter + data->mRandomOffset.Y),
			Rectangle(rect.X, rect.Y, width, height - data->mLineCounter), 2, 0, false, false); //Old depth was 95
	}*/
}
static void UpdateRoutine(Entity owner, SpecialMcFinalBossEffect* data)
{
	if (!data->mDisableShaking)
	{
		Random32* sharedRandom = Globals_GetSharedRandom();
		data->mRandomOffset.X = Random32_NextInt(sharedRandom, 6) * Get_RandomBinaryDirection(sharedRandom);
		data->mRandomOffset.Y = Random32_NextInt(sharedRandom, 6) * Get_RandomBinaryDirection(sharedRandom);
	}

	Rectangle rect = Animation_GetCurrentSheet(&data->mAnimation)->mRectangle;
	int height = rect.Height;
	int cutoff = data->mBloodCutoff;

	if (height - cutoff > data->mLineCounter)
	{
		if (Timer_Update(&data->mTimerBleed))
		{
			for (int i = 0; i < BLOOD_SPRAY_DENSITY; i++)
			{
				ParticleInstance* instance = Do_AddParticle4("FINALBLOODSPLOSION", 
					data->mPosition.X + data->mBloodOffset.X, data->mPosition.Y + data->mBloodOffset.Y);
				instance->mInfluencedDepth = 100;
				if (data->mForcedDirection == 1)
				{
					instance->mInfluencedDirection = Point_Create(-1, 1);
				}
				else if (data->mForcedDirection == -1)
				{
					instance->mInfluencedDirection = Point_Create(1, 1);
				}
				else
				{
					instance->mInfluencedDirection = Point_Create(Get_RandomBinaryDirection(Globals_GetSharedRandom()), 1);
				}
			}
		}
	}

	Animation_Update(&data->mAnimation);

	if (Timer_Update(&data->mTimerLine))
	{
		data->mLineCounter += 2;
	}

	if (height < data->mLineCounter)
	{
		Do_SendBroadcast(FINAL_BOSS_DEATH); //Level Clear Routine
	}
	else
	{
		float percent;
		if (height - cutoff > data->mLineCounter)
		{
			percent = data->mLineCounter / (float)height;
			InputPlayer_Vibrate(Input_GetPlayerOne(), 999, 2, percent, percent);
		}
		else
		{
			int temp = height - data->mLineCounter;
			percent = temp / (float)cutoff;
		}
		InputPlayer_Vibrate(Input_GetPlayerOne(), 999, 2, percent, percent);
	}

	if (!data->mDisableShaking)
	{
		Do_ShakeCamera(1, 2, 1, 2);
	}
}
static void DrawHudRoutine(Entity owner, SpecialMcFinalBossEffect* data, SpriteBatch* spriteBatch)
{
	//TODO C99
	/*
	if (data->mLineCounter == 0)
	{
		OeDrawTool_DrawRectangle(spriteBatch, OeColors_WHITE, 100, Rectangle(0, 0, 1280, 720), 0, false);
	}
	*/
}

void SpecialMcFinalBossEffectSys_Create(Vector2 position, const char* animationName, Vector2 bloodOffset, bool disableShaking, 
	int bloodCutoff, int32_t forcedDirection)
{
	Entity entity = Do_BuildNewEntity("MC Final Boss Effect");
	Do_SetPosition(entity, position.X, position.Y);
	SpecialMcFinalBossEffect* component = Do_InitComponent(C_SpecialMcFinalBossEffect, entity);
	component->mPosition = position;
	component->mAnimationName = animationName;
	component->mBloodOffset = bloodOffset;
	component->mDisableShaking = disableShaking;
	component->mBloodCutoff = bloodCutoff;
	component->mForcedDirection = forcedDirection;
	InitAfterInit(component);
}

System* SpecialMcFinalBossEffectSys_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_SpecialMcFinalBossEffect);
	ss->_mUpdateRoutine = UpdateRoutine;
	ss->_mDrawRoutine = DrawRoutine;
	ss->_mDrawHudRoutine = DrawHudRoutine;
	return SystemSimple_CreateSystem(ss);
}
