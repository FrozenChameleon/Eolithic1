#include "DrawActorSys.h"

/*
#include <unordered_map>
#include "../core/OeFunc.h"
#include "../leveldata/OeImageData.h"
#include "../render/OeDrawRenderInfo.h"
#include "../render/OeDrawStateInfo.h"
#include "../globals/OeColors.h"
#include "../globals/OeState.h"
#include "../globals/OePhase.h"
#include "../components/OeComCamera.h"
#include "../utils/OeUtils.h"
#include "../components/OeTagIsUpdateDisabled.h"
#include "../components/OeComFakePosition.h"
#include "../../OeGlobalDefs.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

using namespace OeFunc;

static OeAnimation EmptyAnimation;
static OeImageDataInstance EmptyRender;

static OeComponentPack<OeDrawStateInfo>* GetStateInfos()
{
	return Get_ComponentPack<OeDrawStateInfo>();
}
static OeComponentPack<OeDrawRenderInfo>* GetRenderInfos()
{
	return Get_ComponentPack<OeDrawRenderInfo>();
}

void OeComDrawActorSys::SetupSystem()
{
	_mInitRoutine = InitRoutine;
	_mUpdateLastRenderPositionRoutine = UpdateLastRenderPositionRoutine;
	_mBeforeUpdateRoutine = BeforeUpdateRoutine;
	_mDrawRoutine = DrawRoutine;
}
void OeComDrawActorSys::Setup(OeEntity owner, OeComDrawActor* data,
	OeDictionary<std::string, OeDictionary<std::string, std::vector<OeImageData>>>& imageData, const std::string& defaultDrawState, const std::string& defaultDrawPhase)
{
	std::unordered_map<std::string, int>& drawStateMap = OeState::GetDrawStateMap();
	std::unordered_map<std::string, int>& drawPhaseMap = OePhase::GetDrawPhaseMap();

	OeComponentPack<OeDrawStateInfo>* stateInfos = GetStateInfos();
	OeComponentPack<OeDrawRenderInfo>* renderInfos = GetRenderInfos();

	data->mDefaultDrawState = drawStateMap[defaultDrawState];
	data->mDefaultDrawPhase = drawPhaseMap[defaultDrawPhase];

	const std::vector<std::string>& firstKeys = imageData.Keys;
	for (int i = 0; i < firstKeys.size(); i += 1)
	{
		const std::string& stateString = firstKeys[i];
		int state = drawStateMap[stateString];

		OeDrawStateInfo* stateInfo = stateInfos->Set(owner, true);
		stateInfo->mState = state;
		stateInfo->mCurrentPhase = NOTHING;
		stateInfo->mDepth = -1;

		const std::vector<std::string>& secondKeys = imageData[stateString].Keys;
		for (int j = 0; j < secondKeys.size(); j += 1)
		{
			const std::string& phaseString = secondKeys[j];
			int phase = drawPhaseMap[phaseString];

			std::vector<OeImageData>& images = imageData[stateString][phaseString];
			for (int k = 0; k < images.size(); k += 1)
			{
				OeDrawRenderInfo* renderInfo = renderInfos->Set(owner, true);
				renderInfo->mState = state;
				renderInfo->mPhase = phase;
				renderInfo->mRender = OeImageDataInstance(&images[k]);
			}
		}
	}

	SetImageState(owner, data, data->mDefaultDrawState, data->mDefaultDrawPhase);
}
void OeComDrawActorSys::CreateExplosionModules(OeEntity owner, int state, int phase, int time, int type)
{
	//Vector2 position = Get_Position(owner);
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				switch (type)
				{
				case 0:
					//TODO2024OeComSpecialNdDeathEffectSys::Create(owner, time, OeImageDataInstance.GetCurrentSheet(ref renders.Components[i].mRender), position.X, position.Y);
					break;
				case 1:
					//TODO2024OeComSpecialDrawExplosionSys::Create(owner, time, OeImageDataInstance.GetCurrentSheet(ref renders.Components[i].mRender), position.X, position.Y);
					break;
				}
			}
		}
	}
}
void OeComDrawActorSys::InitRoutine(OeEntity owner, OeComDrawActor* data)
{
	data->mUniversalDepthOverride = -1;
	data->mScale.X = 1;
	data->mScale.Y = 1;
	data->mTintColor = OeColors::WHITE;
	data->mOnScreenCheckMul = OeComCamera::EXTENDED_CAMERA;
}
void OeComDrawActorSys::UpdateLastRenderPositionRoutine(OeComDrawActor* data)
{
	data->mLastRenderPosition = data->mRenderPosition;
}
static void RealUpdateRoutine(OeEntity owner, OeComDrawActor* data, OeComCamera* camera,
	OeComponentPack<OeBody>* bodyPack, OeComponentPack<OeTagIsUpdateDisabled>* isUpdateDisabledPack, OeComponentPack<OeComFakePosition>* fakePositionPack,
	OeComponentPack<OeDrawStateInfo>* stateInfos, OeComponentPack<OeDrawRenderInfo>* renderInfos)
{
	bool wasSuccessful;
	OeBody* body = bodyPack->TryGetComponent(owner, &wasSuccessful);
	if (wasSuccessful)
	{
		data->mIsOnScreen = OeComCamera::IntersectsCamera(camera, OeBody::GetRect(body), data->mOnScreenCheckMul);
		data->mRenderPosition = OeBody::GetPosition(body);
		data->mLastRenderPosition = OeBody::GetLastRenderPosition(body);
	}
	else
	{
		OeComFakePosition* fakePos = fakePositionPack->TryGetComponent(owner, &wasSuccessful);
		Vector2 temp;
		if (wasSuccessful)
		{
			temp = fakePos->mFakePosition;
		}
		else
		{
			temp = Vector2::Zero;
		}
		float posX = temp.X - (TILE_SIZE / 2);
		float posY = temp.Y - (TILE_SIZE / 2);
		data->mIsOnScreen = OeComCamera::IntersectsCamera(camera, static_cast<int>(posX), static_cast<int>(posY), TILE_SIZE, TILE_SIZE, data->mOnScreenCheckMul);
		data->mRenderPosition = temp;
		data->mLastRenderPosition = temp;
	}

	if (!data->mIsUpdateDisabled)
	{
		if (!isUpdateDisabledPack->HasComponent(owner))
		{
			OeComDrawActorSys::UpdateRenders(owner, data, stateInfos, renderInfos);
		}
	}
}
void OeComDrawActorSys::UpdateRoutine(OeEntity owner, OeComDrawActor* data)
{
	RealUpdateRoutine(owner, data, Get_Camera(), Get_ComponentPack<OeBody>(),
		Get_ComponentPack<OeTagIsUpdateDisabled>(), Get_ComponentPack<OeComFakePosition>(), GetStateInfos(), GetRenderInfos());
}
void OeComDrawActorSys::BeforeUpdateRoutine()
{
	OeComponentPack<OeComDrawActor>* pack = Get_ComponentPack<OeComDrawActor>();
	if (!pack->IsAnyEntityInPack())
	{
		return;
	}

	OeComCamera* camera = Get_Camera();
	OeComponentPack<OeBody>* bodyPack = Get_ComponentPack<OeBody>();
	OeComponentPack<OeTagIsUpdateDisabled>* isUpdateDisabledPack = Get_ComponentPack<OeTagIsUpdateDisabled>();
	OeComponentPack<OeComFakePosition>* fakePositionPack = Get_ComponentPack<OeComFakePosition>();
	OeComponentPack<OeDrawStateInfo>* stateInfos = GetStateInfos();
	OeComponentPack<OeDrawRenderInfo>* renderInfos = GetRenderInfos();
	OePackIterator iter = OePackIterator::Begin();
	while (pack->Next(&iter))
	{
		RealUpdateRoutine(iter.mEntity, &pack->Components[iter.mIndex], camera, bodyPack, isUpdateDisabledPack, fakePositionPack, stateInfos, renderInfos);
	}
}
OeDrawStateInfo* OeComDrawActorSys::GetStateInfo(OeEntity owner, int state)
{
	OeComponentPack<OeDrawStateInfo>* stateInfos = GetStateInfos();
	for (int i = 0; i < stateInfos->Length(); i += 1)
	{
		if (stateInfos->Entities[i] == owner)
		{
			if (stateInfos->Components[i].mState == state)
			{
				return &stateInfos->Components[i];
			}
		}
	}
	OeLogger::LogError("State Not Available: " + OeUtils::ToString(state) + " on " + Get_Name(owner));
	return &stateInfos->Components[0];
}
void OeComDrawActorSys::SetDepthOverride(OeEntity owner, int state, int value)
{
	GetStateInfo(owner, state)->mDepth = value;
}
void OeComDrawActorSys::SetImageDataDepth(OeEntity owner, int state, int phase, int depth)
{
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				renders->Components[i].mRender.mData->mDepth = depth;
			}
		}
	}
}
void OeComDrawActorSys::SetImageState(OeEntity owner, OeComDrawActor* data, int state, int phase)
{
	SetImageState(owner, data, state, phase, false);
}
void OeComDrawActorSys::SetImageState(OeEntity owner, OeComDrawActor* data, int state, int newPhase, bool carryAnimationState)
{
	int oldPhase = GetCurrentPhase(owner, state);
	if ((oldPhase == NOTHING) && (newPhase == NOTHING))
	{
		return;
	}

	OeTimer oldFrameTimer = OeTimer::Zero;
	OeTimer oldFlipTimer = OeTimer::Zero;
	bool oldIsReverse = false;

	bool isFirst = true;
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == oldPhase))
			{
				OeImageDataInstance* oldRender = &renders->Components[i].mRender;
				if (oldRender->mData->mCanAnimate)
				{
					if (isFirst)
					{
						if (carryAnimationState) //setup carry
						{
							OeAnimation* oldAnimation = &oldRender->mAnimation;
							oldFrameTimer = oldAnimation->mFrameTimer;
							oldFlipTimer = oldAnimation->mFlipTimer;
							oldIsReverse = oldAnimation->mIsReverse;
						}
						isFirst = false;
					}
					OeAnimation::ResetAnimation(&oldRender->mAnimation);
				}
			}
		}
	}

	if (carryAnimationState)
	{
		isFirst = true;
		for (int i = 0; i < renders->Length(); i += 1)
		{
			if (renders->Entities[i] == owner)
			{
				if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == newPhase))
				{
					if (isFirst)
					{
						OeImageDataInstance* newRender = &renders->Components[i].mRender;
						OeAnimation* newAnimation = &newRender->mAnimation;
						OeTimer* newFrameTimer = &newAnimation->mFrameTimer;
						OeTimer* newFlipTimer = &newAnimation->mFlipTimer;
						newFrameTimer->mCurrent = oldFrameTimer.mCurrent;
						if (oldFlipTimer.mLimit == newFlipTimer->mLimit)
						{
							newFlipTimer->mCurrent = oldFlipTimer.mCurrent;
						}
						else
						{
							float tempTime = oldFlipTimer.mCurrent * (static_cast<float>(newFlipTimer->mLimit) / oldFlipTimer.mLimit);
							newFlipTimer->mCurrent = static_cast<int>(tempTime);
						}
						newAnimation->mIsReverse = oldIsReverse;
						isFirst = false;
					}
				}
			}
		}
	}

	GetStateInfo(owner, state)->mCurrentPhase = newPhase; //set current phase
}
void OeComDrawActorSys::SetStateRotation(OeEntity owner, int state, float rotation)
{
	GetStateInfo(owner, state)->mRotation = rotation;
}
int OeComDrawActorSys::GetCurrentPhase(OeEntity owner, int state)
{
	return GetStateInfo(owner, state)->mCurrentPhase;
}
void OeComDrawActorSys::SetNudge(OeEntity owner, int state, float x, float y)
{
	GetStateInfo(owner, state)->mNudge = Vector2(x, y);
}
OeImageDataInstance* OeComDrawActorSys::GetRender(OeEntity owner, int state, int phase, int index)
{
	int counter = 0;
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				if (index == counter)
				{
					return &renders->Components[i].mRender;
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
int OeComDrawActorSys::GetAnimationPosition(OeEntity owner, int state, int phase)
{
	return GetAnimation(owner, state, phase)->mFrameTimer.mCurrent;
}
OeAnimation* OeComDrawActorSys::GetCurrentAnimation(OeEntity owner, int state)
{
	return GetAnimation(owner, state, GetCurrentPhase(owner, state));
}
OeAnimation* OeComDrawActorSys::GetAnimation(OeEntity owner, int state, int phase)
{
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				if (renders->Components[i].mRender.mData->mCanAnimate)
				{
					return &renders->Components[i].mRender.mAnimation;
				}
			}
		}
	}
	OeLogger::LogError("Unable to get Animation: " + OeUtils::ToString(state) + "," + OeUtils::ToString(phase) + "!");
	return &EmptyAnimation;
}
OeImageDataInstance* OeComDrawActorSys::GetCurrentImageDataRender(OeEntity owner, int state, int phase)
{
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				return &renders->Components[i].mRender;
			}
		}
	}
	OeLogger::LogError("Unable to get Image Data Render: " + OeUtils::ToString(state) + "," + OeUtils::ToString(phase) + "!");
	return &EmptyRender;
}
void OeComDrawActorSys::ResetCurrentAnimation(OeEntity owner, int state)
{
	int currentPhase = GetCurrentPhase(owner, state);
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == currentPhase))
			{
				if (renders->Components[i].mRender.mData->mCanAnimate)
				{
					OeAnimation::ResetAnimation(&renders->Components[i].mRender.mAnimation);
				}
			}
		}
	}
}
void OeComDrawActorSys::SetCurrentAnimationPosition(OeEntity owner, int state, int position)
{
	int currentPhase = GetCurrentPhase(owner, state);
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == currentPhase))
			{
				if (renders->Components[i].mRender.mData->mCanAnimate)
				{
					renders->Components[i].mRender.mAnimation.mFrameTimer.mCurrent = position;
				}
			}
		}
	}
}
void OeComDrawActorSys::SetAnimationPosition(OeEntity owner, int state, int phase, int position)
{
	OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
	for (int i = 0; i < renders->Length(); i += 1)
	{
		if (renders->Entities[i] == owner)
		{
			if ((renders->Components[i].mState == state) && (renders->Components[i].mPhase == phase))
			{
				if (renders->Components[i].mRender.mData->mCanAnimate)
				{
					renders->Components[i].mRender.mAnimation.mFrameTimer.mCurrent = position;
					return;
				}
			}
		}
	}
}
void OeComDrawActorSys::SetShaderProgram(OeEntity owner, int state, OeShaderProgram* shaderProgram)
{
	GetStateInfo(owner, state)->mShader = shaderProgram;
}
void OeComDrawActorSys::UpdateRenders(OeEntity owner, OeComDrawActor* data,
	OeComponentPack<OeDrawStateInfo>* stateInfos, OeComponentPack<OeDrawRenderInfo>* renderInfos)
{
	int stateInfosLen = stateInfos->Length();
	for (int i = 0; i < stateInfosLen; i += 1)
	{
		if (stateInfos->Entities[i] != owner)
		{
			continue;
		}

		OeDrawStateInfo* stateInfo = &stateInfos->Components[i];
		int phase = stateInfo->mCurrentPhase;
		if (phase == NOTHING)
		{
			continue;
		}
		int state = stateInfo->mState;

		int rendersLen = renderInfos->Length();
		for (int j = 0; j < rendersLen; j += 1)
		{
			if (renderInfos->Entities[j] != owner)
			{
				continue;
			}

			OeDrawRenderInfo* renderInfo = &renderInfos->Components[j];
			if ((renderInfo->mState == state) && (renderInfo->mPhase == phase))
			{
				OeImageDataInstance* render = &renderInfo->mRender;
				if (render->mData->mCanAnimate)
				{
					OeAnimation::Update(&render->mAnimation);
					if (render->mData->mAnimationBlanks && render->mAnimation.mIsAnimationComplete)
					{
						SetImageState(owner, data, state, NOTHING);
					}
				}
			}
		}
	}
}
void OeComDrawActorSys::DrawRoutine(OeEntity owner, OeComDrawActor* data, OeSpriteBatch* spriteBatch)
{
	DrawInterpolated(owner, data, spriteBatch, data->mTintColor, data->mRenderPosition, data->mLastRenderPosition, data->mRotation,
		data->mScale, data->mUniversalDepthOverride);
}
void OeComDrawActorSys::DrawInterpolated(OeEntity owner, OeComDrawActor* data, OeSpriteBatch* spriteBatch, Color color, Vector2 currentPosition, Vector2 lastPosition, float rotation, Vector2 scale, int givenDepth)
{
	if (!data->mIsOnScreen)
	{
		return;
	}

	OeComponentPack<OeDrawStateInfo>* stateInfos = GetStateInfos();
	for (int i = 0; i < stateInfos->Length(); i += 1)
	{
		if (stateInfos->Entities[i] == owner)
		{
			OeDrawStateInfo* stateInfo = &stateInfos->Components[i];
			int state = stateInfo->mState;
			int phase = stateInfo->mCurrentPhase;

			if (phase == NOTHING)
			{
				continue;
			}

			OeComponentPack<OeDrawRenderInfo>* renders = GetRenderInfos();
			for (int j = 0; j < renders->Length(); j += 1)
			{
				if (renders->Entities[j] == owner)
				{
					if ((renders->Components[j].mState == state) && (renders->Components[j].mPhase == phase))
					{
						OeImageDataInstance* render = &renders->Components[j].mRender;

						int depthOverride = givenDepth;
						if (depthOverride == -1)
						{
							depthOverride = stateInfo->mDepth;
						}

						Vector2 nudge = stateInfo->mNudge + data->mUniversalNudge;
						Vector2 oldPos = lastPosition + nudge;
						Vector2 newPos = currentPosition + nudge;

						float stateRotation = stateInfo->mRotation;

						OeShaderProgram* shaderProgram = data->mShaderProgram;
						if (shaderProgram == nullptr)
						{
							shaderProgram = stateInfo->mShader;
						}

						OeDrawInstance* drawInstance = OeImageDataInstance::DrawInterpolated(render, spriteBatch, color, shaderProgram,
							newPos, oldPos, scale, rotation + stateRotation, data->mIsFlipX,
							data->mIsFlipY, depthOverride, data->mOffset);
						if (data->mExtraPasses != 0)
						{
							drawInstance->mExtraPasses = data->mExtraPasses;
						}
						if (data->mIsBlendStateAdditive)
						{
							drawInstance->mBlendState = BlendState::Additive;
						}
					}
				}
			}
		}
	}
}
*/