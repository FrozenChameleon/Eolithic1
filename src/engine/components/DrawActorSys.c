#include "DrawActorSys.h"

#include "../core/Func.h"
#include "../leveldata/ImageData.h"
#include "../render/DrawRenderInfo.h"
#include "../render/DrawStateInfo.h"
#include "../render/Color.h"
#include "../globals/OeState.h"
#include "../globals/OePhase.h"
#include "../components/Camera.h"
#include "../utils/Utils.h"
#include "../components/TagIsUpdateDisabled.h"
#include "../components/FakePosition.h"
#include "../../GlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

static Animation EmptyAnimation;
static ImageDataInstance EmptyRender;

static ComponentPack* GetDrawStateInfos()
{
	return Get_ComponentPack(C_DrawStateInfo);
}
static ComponentPack* GetDrawRenderInfos()
{
	return Get_ComponentPack(C_DrawRenderInfo);
}

void DrawActorSys_Setup(Entity owner, DrawActor* data, ThingGraphicsData* sh_graphics_data, const char* defaultDrawState, const char* defaultDrawPhase)
{
	/*std_unordered_map<std_string, int>& drawStateMap = OeState_GetDrawStateMap();
	std_unordered_map<std_string, int>& drawPhaseMap = OePhase_GetDrawPhaseMap();

	ComponentPack<DrawStateInfo>* stateInfos = GetDrawStateInfos();
	ComponentPack<OeDrawRenderInfo>* renderInfos = GetDrawRenderInfos();

	data->mDefaultDrawState = drawStateMap[defaultDrawState];
	data->mDefaultDrawPhase = drawPhaseMap[defaultDrawPhase];

	const std_vector<std_string>& firstKeys = imageData.Keys;
	for (int i = 0; i < firstKeys.size(); i += 1)
	{
		const std_string& stateString = firstKeys[i];
		int state = drawStateMap[stateString];

		DrawStateInfo* stateInfo = stateInfos->Set(owner, true);
		stateInfo->mState = state;
		stateInfo->mCurrentPhase = NOTHING;
		stateInfo->mDepth = -1;

		const std_vector<std_string>& secondKeys = imageData[stateString].Keys;
		for (int j = 0; j < secondKeys.size(); j += 1)
		{
			const std_string& phaseString = secondKeys[j];
			int phase = drawPhaseMap[phaseString];

			std_vector<OeImageData>& images = imageData[stateString][phaseString];
			for (int k = 0; k < images.size(); k += 1)
			{
				OeDrawRenderInfo* renderInfo = renderInfos->Set(owner, true);
				renderInfo->mState = state;
				renderInfo->mPhase = phase;
				renderInfo->mRender = ImageDataInstance(&images[k]);
			}
		}
	}

	SetImageState(owner, data, data->mDefaultDrawState, data->mDefaultDrawPhase);*/
}
void DrawActorSys_CreateExplosionModules(Entity owner, int state, int phase, int time, int type)
{
	//Vector2 position = Get_Position(owner);
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				switch (type)
				{
				case 0:
					//TODO2024OeComSpecialNdDeathEffectSys_Create(owner, time, ImageDataInstance.GetCurrentSheet(ref drawRenderInfos.Components[i].mRender), position.X, position.Y);
					break;
				case 1:
					//TODO2024OeComSpecialDrawExplosionSys_Create(owner, time, ImageDataInstance.GetCurrentSheet(ref drawRenderInfos.Components[i].mRender), position.X, position.Y);
					break;
				}
			}
		}
	}
}
void DrawActorSys_InitRoutine(Entity owner, DrawActor* data)
{
	data->mUniversalDepthOverride = -1;
	data->mScale.X = 1;
	data->mScale.Y = 1;
	data->mTintColor = COLOR_WHITE;
	data->mOnScreenCheckMul = CAMERA_EXTENDED_CAMERA;
}
void DrawActorSys_UpdateLastRenderPositionRoutine(DrawActor* data)
{
	data->mLastRenderPosition = data->mRenderPosition;
}
static void RealUpdateRoutine(Entity owner, DrawActor* data, Camera* camera,
	ComponentPack* bodyPack, ComponentPack* isUpdateDisabledPack, ComponentPack* fakePositionPack,
	ComponentPack* stateInfos, ComponentPack* renderInfos)
{
	bool wasSuccessful;
	Body* body = ComponentPack_TryGetComponent(bodyPack, owner, &wasSuccessful);
	if (wasSuccessful)
	{
		Rectangle bodyRect = Body_GetRect(body);
		data->mIsOnScreen = Camera_IntersectsCameraRectMul(camera, &bodyRect, data->mOnScreenCheckMul);
		data->mRenderPosition = Body_GetPosition(body);
		data->mLastRenderPosition = Body_GetLastRenderPosition(body);
	}
	else
	{
		FakePosition* fakePos = ComponentPack_TryGetComponent(fakePositionPack, owner, &wasSuccessful);
		Vector2 temp;
		if (wasSuccessful)
		{
			temp = fakePos->mFakePosition;
		}
		else
		{
			temp = Vector2_Zero;
		}
		float posX = temp.X - (TILE_SIZE / 2);
		float posY = temp.Y - (TILE_SIZE / 2);
		data->mIsOnScreen = Camera_IntersectsCamera(camera, (int)(posX), (int)(posY), TILE_SIZE, TILE_SIZE, data->mOnScreenCheckMul);
		data->mRenderPosition = temp;
		data->mLastRenderPosition = temp;
	}

	if (!data->mIsUpdateDisabled)
	{
		if (!ComponentPack_HasComponent(isUpdateDisabledPack, owner))
		{
			DrawActorSys_UpdateRenders(owner, data, stateInfos, renderInfos);
		}
	}
}
void DrawActorSys_UpdateRoutine(Entity owner, DrawActor* data)
{
	RealUpdateRoutine(owner, data, Get_Camera(), Get_ComponentPack(C_Body),
		Get_ComponentPack(C_TagIsUpdateDisabled), Get_ComponentPack(C_FakePosition), GetDrawStateInfos(), GetDrawRenderInfos());
}
void DrawActorSys_BeforeUpdateRoutine()
{
	ComponentPack* drawActorPack = Get_ComponentPack(C_DrawActor);
	if (!ComponentPack_IsAnyEntityInPack(drawActorPack))
	{
		return;
	}

	Camera* camera = Get_Camera();
	ComponentPack* bodyPack = Get_ComponentPack(C_Body);
	ComponentPack* isUpdateDisabledPack = Get_ComponentPack(C_TagIsUpdateDisabled);
	ComponentPack* fakePositionPack = Get_ComponentPack(C_FakePosition);
	ComponentPack* stateInfos = GetDrawStateInfos();
	ComponentPack* renderInfos = GetDrawRenderInfos();
	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(drawActorPack, &iter))
	{
		DrawActor* component = ComponentPack_GetComponentAtIndex(drawActorPack, iter.mIndex);
		RealUpdateRoutine(iter.mEntity, component, camera, bodyPack, isUpdateDisabledPack, fakePositionPack, stateInfos, renderInfos);
	}
}
DrawStateInfo* DrawActorSys_GetStateInfo(Entity owner, int state)
{
	ComponentPack* drawStateInfos = GetDrawStateInfos();
	for (int i = 0; i < ComponentPack_Length(drawStateInfos); i += 1)
	{
		if (drawStateInfos->Entities[i] == owner)
		{
			DrawStateInfo* component = ComponentPack_GetComponentAtIndex(drawStateInfos, i);
			if (component->mState == state)
			{
				return component;
			}
		}
	}
	//TODO C99 OeLogger_LogError("State Not Available: " + OeUtils_ToString(state) + " on " + Get_Name(owner));
	return ComponentPack_GetComponentAtIndex(drawStateInfos, 0);
}
void DrawActorSys_SetDepthOverride(Entity owner, int state, int value)
{
	DrawActorSys_GetStateInfo(owner, state)->mDepth = value;
}
void DrawActorSys_SetImageDataDepth(Entity owner, int state, int phase, int depth)
{
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				component->mRender.mData->mDepth = depth;
			}
		}
	}
}
void DrawActorSys_SetImageState(Entity owner, DrawActor* data, int state, int phase)
{
	DrawActorSys_SetImageState2(owner, data, state, phase, false);
}
void DrawActorSys_SetImageState2(Entity owner, DrawActor* data, int state, int newPhase, bool carryAnimationState)
{
	int oldPhase = DrawActorSys_GetCurrentPhase(owner, state);
	if ((oldPhase == DRAWACTORSYS_NOTHING) && (newPhase == DRAWACTORSYS_NOTHING))
	{
		return;
	}

	Timer oldFrameTimer = Timer_Zero;
	Timer oldFlipTimer = Timer_Zero;
	bool oldIsReverse = false;

	bool isFirst = true;
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == oldPhase))
			{
				ImageDataInstance* oldRender = &component->mRender;
				if (oldRender->mData->mCanAnimate)
				{
					if (isFirst)
					{
						if (carryAnimationState) //setup carry
						{
							Animation* oldAnimation = &oldRender->mAnimation;
							oldFrameTimer = oldAnimation->mFrameTimer;
							oldFlipTimer = oldAnimation->mFlipTimer;
							oldIsReverse = oldAnimation->mIsReverse;
						}
						isFirst = false;
					}
					Animation_ResetAnimation(&oldRender->mAnimation);
				}
			}
		}
	}

	if (carryAnimationState)
	{
		isFirst = true;
		for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
		{
			if (drawRenderInfos->Entities[i] == owner)
			{
				DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
				if ((component->mState == state) && (component->mPhase == newPhase))
				{
					if (isFirst)
					{
						ImageDataInstance* newRender = &component->mRender;
						Animation* newAnimation = &newRender->mAnimation;
						Timer* newFrameTimer = &newAnimation->mFrameTimer;
						Timer* newFlipTimer = &newAnimation->mFlipTimer;
						newFrameTimer->mCurrent = oldFrameTimer.mCurrent;
						if (oldFlipTimer.mLimit == newFlipTimer->mLimit)
						{
							newFlipTimer->mCurrent = oldFlipTimer.mCurrent;
						}
						else
						{
							float tempTime = oldFlipTimer.mCurrent * ((float)(newFlipTimer->mLimit) / oldFlipTimer.mLimit);
							newFlipTimer->mCurrent = (int)(tempTime);
						}
						newAnimation->mIsReverse = oldIsReverse;
						isFirst = false;
					}
				}
			}
		}
	}

	DrawActorSys_GetStateInfo(owner, state)->mCurrentPhase = newPhase; //set current phase
}
void DrawActorSys_SetStateRotation(Entity owner, int state, float rotation)
{
	DrawActorSys_GetStateInfo(owner, state)->mRotation = rotation;
}
int DrawActorSys_GetCurrentPhase(Entity owner, int state)
{
	return DrawActorSys_GetStateInfo(owner, state)->mCurrentPhase;
}
void DrawActorSys_SetNudge(Entity owner, int state, float x, float y)
{
	DrawActorSys_GetStateInfo(owner, state)->mNudge = Vector2_Create(x, y);
}
ImageDataInstance* DrawActorSys_GetRender(Entity owner, int state, int phase, int index)
{
	int counter = 0;
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				if (index == counter)
				{
					return &component->mRender;
				}
				else
				{
					counter += 1;
				}
			}
		}
	}
	return &EmptyRender;
}
int DrawActorSys_GetAnimationPosition(Entity owner, int state, int phase)
{
	return DrawActorSys_GetAnimation(owner, state, phase)->mFrameTimer.mCurrent;
}
Animation* DrawActorSys_GetCurrentAnimation(Entity owner, int state)
{
	return DrawActorSys_GetAnimation(owner, state, DrawActorSys_GetCurrentPhase(owner, state));
}
Animation* DrawActorSys_GetAnimation(Entity owner, int state, int phase)
{
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				if (component->mRender.mData->mCanAnimate)
				{
					return &component->mRender.mAnimation;
				}
			}
		}
	}
	//TODO C99 OeLogger_LogError("Unable to get Animation: " + OeUtils_ToString(state) + "," + OeUtils_ToString(phase) + "!");
	return &EmptyAnimation;
}
ImageDataInstance* DrawActorSys_GetCurrentImageDataRender(Entity owner, int state, int phase)
{
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				return &component->mRender;
			}
		}
	}
	//TODO C99 OeLogger_LogError("Unable to get Image Data Render: " + OeUtils_ToString(state) + "," + OeUtils_ToString(phase) + "!");
	return &EmptyRender;
}
void DrawActorSys_ResetCurrentAnimation(Entity owner, int state)
{
	int currentPhase = DrawActorSys_GetCurrentPhase(owner, state);
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == currentPhase))
			{
				if (component->mRender.mData->mCanAnimate)
				{
					Animation_ResetAnimation(&component->mRender.mAnimation);
				}
			}
		}
	}
}
void DrawActorSys_SetCurrentAnimationPosition(Entity owner, int state, int position)
{
	int currentPhase = DrawActorSys_GetCurrentPhase(owner, state);
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == currentPhase))
			{
				if (component->mRender.mData->mCanAnimate)
				{
					component->mRender.mAnimation.mFrameTimer.mCurrent = position;
				}
			}
		}
	}
}
void DrawActorSys_SetAnimationPosition(Entity owner, int state, int phase, int position)
{
	ComponentPack* drawRenderInfos = GetDrawRenderInfos();
	for (int i = 0; i < ComponentPack_Length(drawRenderInfos); i += 1)
	{
		if (drawRenderInfos->Entities[i] == owner)
		{
			DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, i);
			if ((component->mState == state) && (component->mPhase == phase))
			{
				if (component->mRender.mData->mCanAnimate)
				{
					component->mRender.mAnimation.mFrameTimer.mCurrent = position;
					return;
				}
			}
		}
	}
}
void DrawActorSys_SetShaderProgram(Entity owner, int state, ShaderProgram* shaderProgram)
{
	DrawActorSys_GetStateInfo(owner, state)->mShader = shaderProgram;
}
void DrawActorSys_UpdateRenders(Entity owner, DrawActor* data,
	ComponentPack* drawStateInfos, ComponentPack* drawRenderInfos)
{
	int stateInfosLen = ComponentPack_Length(drawStateInfos);
	for (int i = 0; i < stateInfosLen; i += 1)
	{
		if (drawStateInfos->Entities[i] != owner)
		{
			continue;
		}

		DrawStateInfo* stateInfo = ComponentPack_GetComponentAtIndex(drawStateInfos, i);
		int phase = stateInfo->mCurrentPhase;
		if (phase == DRAWACTORSYS_NOTHING)
		{
			continue;
		}
		int state = stateInfo->mState;

		int rendersLen = ComponentPack_Length(drawRenderInfos);
		for (int j = 0; j < rendersLen; j += 1)
		{
			if (drawRenderInfos->Entities[j] != owner)
			{
				continue;
			}

			DrawRenderInfo* renderInfo = ComponentPack_GetComponentAtIndex(drawRenderInfos, j);
			if ((renderInfo->mState == state) && (renderInfo->mPhase == phase))
			{
				ImageDataInstance* render = &renderInfo->mRender;
				if (render->mData->mCanAnimate)
				{
					Animation_Update(&render->mAnimation);
					if (render->mData->mAnimationBlanks && render->mAnimation.mIsAnimationComplete)
					{
						DrawActorSys_SetImageState(owner, data, state, DRAWACTORSYS_NOTHING);
					}
				}
			}
		}
	}
}
void DrawActorSys_DrawRoutine(Entity owner, DrawActor* data, SpriteBatch* spriteBatch)
{
	DrawActorSys_DrawInterpolated(owner, data, spriteBatch, data->mTintColor, data->mRenderPosition, data->mLastRenderPosition, data->mRotation,
		data->mScale, data->mUniversalDepthOverride);
}
void DrawActorSys_DrawInterpolated(Entity owner, DrawActor* data, SpriteBatch* spriteBatch,
	Color color, Vector2 currentPosition, Vector2 lastPosition, float rotation, Vector2 scale, int givenDepth)
{
	if (!data->mIsOnScreen)
	{
		return;
	}

	ComponentPack* drawStateInfos = GetDrawStateInfos();
	for (int i = 0; i < ComponentPack_Length(drawStateInfos); i += 1)
	{
		if (drawStateInfos->Entities[i] == owner)
		{
			DrawStateInfo* stateInfo = ComponentPack_GetComponentAtIndex(drawStateInfos, i);
			int state = stateInfo->mState;
			int phase = stateInfo->mCurrentPhase;

			if (phase == DRAWACTORSYS_NOTHING)
			{
				continue;
			}

			ComponentPack* drawRenderInfos = GetDrawRenderInfos();
			for (int j = 0; j < ComponentPack_Length(drawRenderInfos); j += 1)
			{
				if (drawRenderInfos->Entities[j] == owner)
				{
					DrawRenderInfo* component = ComponentPack_GetComponentAtIndex(drawRenderInfos, j);
					if ((component->mState == state) && (component->mPhase == phase))
					{
						ImageDataInstance* render = &component->mRender;

						int depthOverride = givenDepth;
						if (depthOverride == -1)
						{
							depthOverride = stateInfo->mDepth;
						}

						Vector2 nudge = Vector2_Add(stateInfo->mNudge, data->mUniversalNudge);
						Vector2 oldPos = Vector2_Add(lastPosition, nudge);
						Vector2 newPos = Vector2_Add(currentPosition, nudge);

						float stateRotation = stateInfo->mRotation;

						ShaderProgram* shaderProgram = data->mShaderProgram;
						if (shaderProgram == NULL)
						{
							shaderProgram = stateInfo->mShader;
						}

						/*DrawInstance* drawInstance = ImageDataInstance_DrawInterpolated(render, spriteBatch, color, shaderProgram,
							newPos, oldPos, scale, rotation + stateRotation, data->mIsFlipX,
							data->mIsFlipY, depthOverride, data->mOffset);
						if (data->mExtraPasses != 0)
						{
							drawInstance->mExtraPasses = data->mExtraPasses;
						}
						if (data->mIsBlendStateAdditive)
						{
							drawInstance->mBlendState = BLENDSTATE_ADDITIVE;
						}*/
					}
				}
			}
		}
	}
}

System* DrawActorSys_CreateSystem()
{
	SystemSimple* ss = SystemSimple_Create(C_DrawActor);
	ss->_mInitRoutine = DrawActorSys_InitRoutine;
	ss->_mUpdateLastRenderPositionRoutine = DrawActorSys_UpdateLastRenderPositionRoutine;
	ss->_mBeforeUpdateRoutine = DrawActorSys_BeforeUpdateRoutine;
	ss->_mDrawRoutine = DrawActorSys_DrawRoutine;
	return SystemSimple_CreateSystem(ss);
}
