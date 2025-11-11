#include "ParticleInstanceSys.h"

#include "../render/Sheet.h"
#include "../render/Color.h"
#include "../globals/Globals.h"
#include "../math/Math.h"
#include "Particle.h"
#include "../components/Camera.h"
#include "../core/Func.h"
#include "../render/DrawInstance.h"
#include "../math/Random32.h"


static float ReturnSameSign(float newValue, float oldValue)
{
	int newSig = Math_SignumFloat(newValue);
	int oldSig = Math_SignumFloat(oldValue);

	if (newSig != oldSig)
	{
		return -newValue;
	}

	return newValue;
}
static float ReturnOppositeSign(float newValue, float oldValue)
{
	return -ReturnSameSign(newValue, oldValue);
}
static int GetDirection()
{
	return Random32_NextInt(Globals_GetSharedRandom(), 2) == 1 ? -1 : 1;
}
static float GetValue(float min, float max, bool allowNegative)
{
	float newValue = Random32_NextFloat(Globals_GetSharedRandom()) * (max - min) + min;

	if (allowNegative)
	{
		newValue *= GetDirection();
	}

	return newValue;
}
static int GetValueInt(int min, int max)
{
	if (max - min <= 0)
	{
		return min;
	}

	int newValue = Random32_NextInt(Globals_GetSharedRandom(), max - min) + min;

	return newValue;
}
static void UpdateLastRenderPositionRoutine(ParticleInstance* data)
{
	data->mLastRenderPosition = data->mPosition;
}

static void SetConstantFluctuateTimeLimit(ParticleInstance* data)
{
	data->mTimerConstantFluctuate.mLimit = GetValueInt(data->mParticle->mConstantFluctuateIntervalMin, data->mParticle->mConstantFluctuateIntervalMax);
}
static void SetCurveFluctuateTimeLimit(ParticleInstance* data)
{
	data->mTimerCurveFluctuate.mLimit = GetValueInt(data->mParticle->mCurveFluctuateIntervalMin, data->mParticle->mCurveFluctuateIntervalMax);
}
static void GenerateNewCurveMax(ParticleInstance* data)
{
	data->mCurveMaximum.X = GetValue(data->mParticle->mCurveTotalMinimum.X, data->mParticle->mCurveTotalMaximum.X, data->mParticle->mCurveIsNegativeX);
	data->mCurveMaximum.Y = GetValue(data->mParticle->mCurveTotalMinimum.Y, data->mParticle->mCurveTotalMaximum.Y, data->mParticle->mCurveIsNegativeY);
}
static void GenerateNewCurveRate(ParticleInstance* data)
{
	data->mCurveRate.X = GetValue(data->mParticle->mCurveMinimumIncreaseRate.X, data->mParticle->mCurveMaximumIncreaseRate.X, false);
	if (data->mParticle->mCurveIsNegativeX)
	{
		data->mCurveRate.X = ReturnSameSign(data->mCurveRate.X, data->mCurveMaximum.X);
	}

	data->mCurveRate.Y = GetValue(data->mParticle->mCurveMinimumIncreaseRate.Y, data->mParticle->mCurveMaximumIncreaseRate.Y, false);
	if (data->mParticle->mCurveIsNegativeY)
	{
		data->mCurveRate.Y = ReturnSameSign(data->mCurveRate.Y, data->mCurveMaximum.Y);
	}
}
static void GenerateNewOffset(ParticleInstance* data)
{
	data->mOffset.X = GetValue(data->mParticle->mOffsetMinimum.X, data->mParticle->mOffsetMaximum.X, data->mParticle->mOffsetIsNegativeX);
	data->mOffset.Y = GetValue(data->mParticle->mOffsetMinimum.Y, data->mParticle->mOffsetMaximum.Y, data->mParticle->mOffsetIsNegativeY);
}
static void GenerateNewFlicker(ParticleInstance* data)
{
	data->mFlickerStart = GetValueInt(data->mParticle->mFlickerMinimumStart, data->mParticle->mFlickerMaximumStart);
	data->mTimerFlicker.mLimit = GetValueInt(data->mParticle->mFlickerMinimumSpeed, data->mParticle->mFlickerMaximumSpeed);
}
static void GenerateNewConstant(ParticleInstance* data)
{
	data->mConstant.X = GetValue(data->mParticle->mConstantMinimum.X, data->mParticle->mConstantMaximum.X, data->mParticle->mConstantIsNegativeX);
	data->mConstant.Y = GetValue(data->mParticle->mConstantMinimum.Y, data->mParticle->mConstantMaximum.Y, data->mParticle->mConstantIsNegativeY);
}

static void UpdateAttachedPosition(ParticleInstance* data)
{
	//WILLNOTDO 06242023 FOR MUTE CRIMSON DX
	/*
	if (OeEntity_Nothing == data->mAttachedEntity)
	{
		return;
	}

	OeEntity entity = Get_Entity(data->mAttachedEntity);
	if (data->mAttachedThingFollowFlipX && Is_DrawActorPresent(entity))
	{
		data->mFlipX = Is_FlipX(entity);
		data->mPosition.X = Get_X(entity) + data->mAttachedThingOffset.X * Get_FacingDirection(entity);
	}
	else
	{
		data->mPosition.X = Get_X(entity) + data->mAttachedThingOffset.X;
	}
	data->mPosition.Y = Get_Y(entity) + data->mAttachedThingOffset.Y;
	*/
}
static void AttachThing(ParticleInstance* data, Entity entity, int offsetX, int offsetY, bool followFlipX)
{
	data->mAttachedEntity = entity;
	data->mAttachedThingOffset.X = offsetX;
	data->mAttachedThingOffset.Y = offsetY;
	data->mAttachedThingFollowFlipX = followFlipX;
	UpdateAttachedPosition(data);
	UpdateLastRenderPositionRoutine(data);
}
static void HandleConstant(ParticleInstance* data)
{
	data->mPosition.X += data->mConstant.X * data->mInfluencedDirection.X;
	data->mPosition.Y += data->mConstant.Y * data->mInfluencedDirection.Y;

	if (data->mParticle->mConstantIsFluctuating)
	{
		if (Timer_Update(&data->mTimerConstantFluctuate))
		{
			SetConstantFluctuateTimeLimit(data);
			GenerateNewConstant(data);
		}
	}
}
static void HandleCurve(ParticleInstance* data)
{
	data->mCurrentCurveRate.X += data->mCurveRate.X;
	data->mCurrentCurveRate.Y += data->mCurveRate.Y;

	if (data->mCurveMaximum.X > 0)
	{
		if (data->mCurrentCurveRate.X > data->mCurveMaximum.X)
		{
			data->mCurrentCurveRate.X = data->mCurveMaximum.X;
		}
	}
	else if (data->mCurveMaximum.X < 0)
	{
		if (data->mCurrentCurveRate.X < data->mCurveMaximum.X)
		{
			data->mCurrentCurveRate.X = data->mCurveMaximum.X;
		}
	}

	if (data->mCurveMaximum.Y > 0)
	{
		if (data->mCurrentCurveRate.Y > data->mCurveMaximum.Y)
		{
			data->mCurrentCurveRate.Y = data->mCurveMaximum.Y;
		}
	}
	else if (data->mCurveMaximum.Y < 0)
	{
		if (data->mCurrentCurveRate.Y < data->mCurveMaximum.Y)
		{
			data->mCurrentCurveRate.Y = data->mCurveMaximum.Y;
		}
	}

	data->mPosition.X += data->mCurrentCurveRate.X * data->mInfluencedDirection.X;
	data->mPosition.Y += data->mCurrentCurveRate.Y * data->mInfluencedDirection.Y;

	if (data->mParticle->mCurveIsFluctuating)
	{
		if (Timer_Update(&data->mTimerCurveFluctuate))
		{
			SetCurveFluctuateTimeLimit(data);

			if (!data->mParticle->mCurveFluctuateKeepSpeed)
			{
				data->mCurrentCurveRate.X = 0;
				data->mCurrentCurveRate.Y = 0;
			}
			if (data->mParticle->mCurveFluctuateResetRate)
			{
				GenerateNewCurveRate(data);
			}
			if (data->mParticle->mCurveFluctuateResetTotal)
			{
				GenerateNewCurveMax(data);
			}
		}
	}
}
static void DrawRoutineActual(ParticleInstance* data, SpriteBatch* spriteBatch, Vector2 position, Vector2 lastPosition)
{
	if (data->mIsFlickering)
	{
		return;
	}

	/*
	OeSheet* sheet = data->mParticle->mTextureIsAnimation ? OeAnimation_GetCurrentSheet(&data->mAnimation) : data->mSheet;

	float scale = data->mParticle->mScaler;
	OeDrawInstance* drawInstance = OeSheet_DrawInterpolated(sheet, spriteBatch, data->mInfluencedColor, GetDepth(data), true, true, data->mShaderProgram, position, lastPosition,
		Vector2(scale), data->mInfluencedRotation, data->mFlipX, data->mFlipY);
	if (data->mParticle->mIsBlendStateAdditive)
	{
		drawInstance->mBlendState = BlendState_Additive;
	}
	drawInstance->mExtraPasses = data->mParticle->mExtraPasses;*/
}
static void DrawRoutine(ParticleInstance* data, SpriteBatch* spriteBatch)
{
	Vector2 position = Vector2_Add(data->mPosition, data->mOffset);
	Vector2 lastPosition = Vector2_Add(data->mLastRenderPosition, data->mOffset);
	DrawRoutineActual(data, spriteBatch, position, lastPosition);
}
static int GetDepth(ParticleInstance* data)
{
	return data->mInfluencedDepth != -1 ? data->mInfluencedDepth : data->mParticle->mTextureDepth;
}
void ParticleInstanceSys_Setup(ParticleInstance* data, const char* name, Particle* particleData, float x, float y)
{
	data->mInfluencedColor = COLOR_WHITE;
	data->mInfluencedDepth = -1;

	MString_Assign(&data->mName, name);
	data->mParticle = particleData;

	data->mFlipX = false;
	data->mFlipY = false;

	data->mInfluencedDirection.X = 1;
	data->mInfluencedDirection.Y = 1;

	data->mPosition.X = x;
	data->mPosition.Y = y;

	if (data->mParticle->mTextureIsAnimation)
	{
		Animation_Init(&data->mAnimation, MString_GetText(data->mParticle->mTextureName), data->mParticle->mTextureFlipSpeed);
		data->mAnimation.mAnimationLoopPoint = data->mParticle->mTextureLoopPoint;
		data->mAnimation.mIsLoopingDisabled = data->mParticle->mTextureDoesAnimationStop;
	}
	else
	{
		data->mSheet = Sheet_GetSheet(MString_GetText(data->mParticle->mTextureName));
	}

	GenerateNewCurveMax(data);

	GenerateNewConstant(data);

	GenerateNewOffset(data);

	GenerateNewFlicker(data);

	GenerateNewCurveRate(data);

	if (data->mParticle->mCurveIsOppositeX)
	{
		data->mCurveMaximum.X = ReturnOppositeSign(data->mCurveMaximum.X, data->mConstant.X);
		data->mCurveRate.X = ReturnOppositeSign(data->mCurveRate.X, data->mConstant.X);
	}
	if (data->mParticle->mCurveIsOppositeY)
	{
		data->mCurveMaximum.Y = ReturnOppositeSign(data->mCurveMaximum.Y, data->mConstant.Y);
		data->mCurveRate.Y = ReturnOppositeSign(data->mCurveRate.Y, data->mConstant.Y);
	}
	if (data->mParticle->mConstantIsFluctuating)
	{
		SetConstantFluctuateTimeLimit(data);
	}
	if (data->mParticle->mCurveIsFluctuating)
	{
		SetCurveFluctuateTimeLimit(data);
	}
	if (data->mParticle->mMiscTTLMin != -1 && data->mParticle->mMiscTTLMax != -1)
	{
		data->mTimerTimeToLive.mLimit = GetValueInt(data->mParticle->mMiscTTLMin, data->mParticle->mMiscTTLMax);
	}

	UpdateLastRenderPositionRoutine(data);
}
bool ParticleInstanceSys_UpdateRoutine(ParticleInstance* data)
{
	HandleConstant(data);

	HandleCurve(data);

	if (data->mParticle->mFlickerIsFlicker)
	{
		if (data->mCounter == data->mFlickerStart)
		{
			data->mIsFlickering = true;
		}

		if (data->mCounter > data->mFlickerStart)
		{
			if (Timer_Update(&data->mTimerFlicker))
			{
				data->mIsFlickering = !data->mIsFlickering;
			}
		}
	}

	if (data->mParticle->mTextureIsAnimation)
	{
		Animation_Update(&data->mAnimation);
	}

	if (data->mParticle->mMiscTTLMin != -1 && data->mParticle->mMiscTTLMax != -1)
	{
		if (Timer_Update(&data->mTimerTimeToLive))
		{
			data->mIsComplete = true;
		}
	}

	data->mCounter++;

	return data->mIsComplete;
}

static void Update(System* sys)
{
	ComponentPack* pack = Get_ComponentPack(C_ParticleInstance);
	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(pack, &iter))
	{
		if (ParticleInstanceSys_UpdateRoutine(ComponentPack_GetComponentAtIndex(pack, iter.mIndex)))
		{
			Do_UnsetAtIndexAndRemoveDummyEntityIfLast(pack, iter.mIndex);
		}
	}
}
static void UpdateLastRenderPosition(System* sys, GameState* gameState)
{
	/*
	OeComponentPack<ParticleInstance>* pack = gameState->GetComponentPack<ParticleInstance>();

	OePackIterator iter = OePackIterator_Begin();
	while (pack->Next(&iter))
	{
		UpdateLastRenderPositionRoutine(&pack->Components[iter.mIndex]);
	}
	*/
}
static void Draw(System* sys, SpriteBatch* spriteBatch)
{
	/*
	float mul = OeComCamera_EXTENDED_CAMERA;

	OeComCamera* camera = Get_Camera();
	int left = OeComCamera_GetLeft(camera, mul);
	int top = OeComCamera_GetTop(camera, mul);
	int right = OeComCamera_GetRight(camera, mul);
	int bottom = OeComCamera_GetBottom(camera, mul);

	OeComponentPack<ParticleInstance>* pack = Get_ComponentPack<ParticleInstance>();
	OePackIterator iter = OePackIterator_Begin();
	while (pack->Next(&iter))
	{
		if ((pack->Components[iter.mIndex].mPosition.X > left) && (pack->Components[iter.mIndex].mPosition.Y > top))
		{
			if ((pack->Components[iter.mIndex].mPosition.X < right) && (pack->Components[iter.mIndex].mPosition.Y < bottom))
			{
				DrawRoutine(&pack->Components[iter.mIndex], spriteBatch);
			}
		}
	}*/
}

System* ParticleInstanceSys_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	sys->_mUpdateLastRenderPosition = UpdateLastRenderPosition;
	sys->_mDraw = Draw;
	return sys;
}
