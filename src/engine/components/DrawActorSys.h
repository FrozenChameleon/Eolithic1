#pragma once

#include "../leveldata/ThingSettings.h"
#include "../systems/SystemSimple.h"
#include "DrawActor.h"
#include "../leveldata/ImageData.h"
#include "../render/DrawStateInfo.h"
#include "../render/DrawRenderInfo.h"
#include "../gamestate/ComponentPack.h"
#include "limits.h"

typedef struct Animation Animation;
typedef struct ImageDataInstance ImageDataInstance;

enum
{
	DRAWACTORSYS_NOTHING = INT_MIN
};

//void SetupSystem() override;
void DrawActorSys_Setup(Entity owner, DrawActor* data, ThingGraphicsData* sh_graphics_data, const char* defaultDrawState, const char* defaultDrawPhase);
void DrawActorSys_CreateExplosionModules(Entity owner, int state, int phase, int time, int type);
void DrawActorSys_InitRoutine(Entity owner, DrawActor* data);
void DrawActorSys_UpdateLastRenderPositionRoutine(DrawActor* data);
void DrawActorSys_BeforeUpdateRoutine();
void DrawActorSys_UpdateRoutine(Entity owner, DrawActor* data);
DrawStateInfo* DrawActorSys_GetStateInfo(Entity owner, int state);
void DrawActorSys_SetDepthOverride(Entity owner, int state, int value);
void DrawActorSys_SetImageDataDepth(Entity owner, int state, int phase, int depth);
void DrawActorSys_SetImageState(Entity owner, DrawActor* data, int state, int phase);
void DrawActorSys_SetImageState2(Entity owner, DrawActor* data, int state, int newPhase, bool carryAnimationState);
void DrawActorSys_SetStateRotation(Entity owner, int state, float rotation);
int DrawActorSys_GetCurrentPhase(Entity owner, int state);
void DrawActorSys_SetNudge(Entity owner, int state, float x, float y);
ImageDataInstance* DrawActorSys_GetRender(Entity owner, int state, int phase, int index);
int DrawActorSys_GetAnimationPosition(Entity owner, int state, int phase);
Animation* DrawActorSys_GetCurrentAnimation(Entity owner, int state);
Animation* DrawActorSys_GetAnimation(Entity owner, int state, int phase);
ImageDataInstance* DrawActorSys_GetCurrentImageDataRender(Entity owner, int state, int phase);
void DrawActorSys_ResetCurrentAnimation(Entity owner, int state);
void DrawActorSys_SetCurrentAnimationPosition(Entity owner, int state, int position);
void DrawActorSys_SetAnimationPosition(Entity owner, int state, int phase, int position);
void DrawActorSys_SetShaderProgram(Entity owner, int state, ShaderProgram* shaderProgram);
void DrawActorSys_UpdateRenders(Entity owner, DrawActor* data, ComponentPack* stateInfos, ComponentPack* renders);
void DrawActorSys_DrawRoutine(Entity owner, DrawActor* data, SpriteBatch* spriteBatch);
void DrawActorSys_DrawInterpolated(Entity owner, DrawActor* data, SpriteBatch* spriteBatch, Color color, Vector2 currentPosition, Vector2 lastPosition,
	float rotation, Vector2 scale, int givenDepth);
System* DrawActorSys_CreateSystem();