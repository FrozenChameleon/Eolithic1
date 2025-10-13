#pragma once

/*
#include "../collections/OeDictionary.h"
#include <string>
#include "../systems/OeSystemSimple.h"
#include "OeComDrawActor.h"
#include "../leveldata/OeImageData.h"
#include "../render/OeDrawStateInfo.h"
#include "../render/OeDrawRenderInfo.h"
#include "../gamestate/OeComponentPack.h"

class OeAnimation;
class OeImageDataInstance;

class OeComDrawActorSys final : public OeSystemSimple<OeComDrawActor>
{
public:
	enum
	{
		NOTHING = INT_MIN
	};

	void SetupSystem() override;
	static void Setup(OeEntity owner, OeComDrawActor* data,
		OeDictionary<std::string, OeDictionary<std::string, std::vector<OeImageData>>>& imageData, const std::string& defaultDrawState, const std::string& defaultDrawPhase);
	static void CreateExplosionModules(OeEntity owner, int state, int phase, int time, int type);
	static void InitRoutine(OeEntity owner, OeComDrawActor* data);
	static void UpdateLastRenderPositionRoutine(OeComDrawActor* data);
	static void BeforeUpdateRoutine();
	static void UpdateRoutine(OeEntity owner, OeComDrawActor* data);
	static OeDrawStateInfo* GetStateInfo(OeEntity owner, int state);
	static void SetDepthOverride(OeEntity owner, int state, int value);
	static void SetImageDataDepth(OeEntity owner, int state, int phase, int depth);
	static void SetImageState(OeEntity owner, OeComDrawActor* data, int state, int phase);
	static void SetImageState(OeEntity owner, OeComDrawActor* data, int state, int newPhase, bool carryAnimationState);
	static void SetStateRotation(OeEntity owner, int state, float rotation);
	static int GetCurrentPhase(OeEntity owner, int state);
	static void SetNudge(OeEntity owner, int state, float x, float y);
	static OeImageDataInstance* GetRender(OeEntity owner, int state, int phase, int index);
	static int GetAnimationPosition(OeEntity owner, int state, int phase);
	static OeAnimation* GetCurrentAnimation(OeEntity owner, int state);
	static OeAnimation* GetAnimation(OeEntity owner, int state, int phase);
	static OeImageDataInstance* GetCurrentImageDataRender(OeEntity owner, int state, int phase);
	static void ResetCurrentAnimation(OeEntity owner, int state);
	static void SetCurrentAnimationPosition(OeEntity owner, int state, int position);
	static void SetAnimationPosition(OeEntity owner, int state, int phase, int position);
	static void SetShaderProgram(OeEntity owner, int state, OeShaderProgram* shaderProgram);
	static void UpdateRenders(OeEntity owner, OeComDrawActor* data, OeComponentPack<OeDrawStateInfo>* stateInfos, OeComponentPack<OeDrawRenderInfo>* renders);
	static void DrawRoutine(OeEntity owner, OeComDrawActor* data, OeSpriteBatch* spriteBatch);
	static void DrawInterpolated(OeEntity owner, OeComDrawActor* data, OeSpriteBatch* spriteBatch, Color color, Vector2 currentPosition, Vector2 lastPosition,
		float rotation, Vector2 scale, int givenDepth);
};*/