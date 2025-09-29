#pragma once

#pragma once

#include "../utils/Macros.h"
//#include "../gamestate/EntitySearch.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../math/Rectangle.h"
#include "../gamestate/ComponentPack.h"
#include "../utils/Timer.h"
#include "../render/Color.h"
//#include "../utils/OeStringPair.h"
//#include "../utils/TimerDouble.h"
#include "../resources/Resource.h"
#include "../gamestate/GameState.h"
#include "../collision/Body.h"
//#include "../collision/CollisionEngine.h"
#include "../components/Camera.h"
#include "../components/DrawActor.h"
#include "../components/HitFlashKit.h"
#include "../components/MirrorEffect.h"
#include "../components/MoveGetter.h"
#include "../components/SceneCameraData.h"
#include "../components/NodeMovingKit.h"

typedef struct SpriteBatch SpriteBatch;
typedef struct LevelCameraDataInstance LevelCameraDataInstance;
typedef struct ThingInstance ThingInstance;
typedef struct ShaderProgram ShaderProgram;
typedef struct ParticleInstance ParticleInstance;
typedef struct Animation Animation;
typedef struct Random32 Random32;
typedef struct GameSaveData GameSaveData;
typedef struct LevelData LevelData;
typedef struct EntitySearch EntitySearch;
typedef struct TimerDouble TimerDouble;
typedef struct StringPair StringPair;
typedef struct CollisionEngine CollisionEngine;

//REGION DO
void Do_DrawCameraData(SpriteBatch* spriteBatch);
Entity Do_CreatePlayer(float x, float y, const char* name);
int Get_AmountOfPlayers();
bool Has_Players();
Entity Get_FirstPlayer();
Entity Get_Player();
Entity Get_ClosestPlayer(float x, float y);
Entity Get_Player2(int number);
LevelCameraDataInstance* Get_CameraDataInstances();
SceneCameraData* Get_SceneCameraData();
//private
void Do_HandleNormalCamera(bool useAutoHingeCamera, bool forceCameraPosition, LevelCameraDataInstance* instance);
void Do_HandleTransitionCamera(bool useAutoHingeCamera, bool forceCameraPosition, LevelCameraDataInstance* instance);
//
LevelCameraDataInstance* Do_HandleCamera(bool useAutoHingeCamera, bool forceCameraPosition);
LevelCameraDataInstance* Do_HandleCamera2(bool useAutoHingeCamera, bool forceCameraPosition, bool manualSize, int size);
void Do_LoadCamera(bool useAutoHingeCamera, bool forceCameraPosition, LevelCameraDataInstance* instance);
void Do_ResetCollisionGrid();
void Do_LoadCameraNumber(bool useAutoHingeCamera, bool forceCameraPosition, int number);
void Do_ResetCameraDataFullyNoMatterWhat();
void Do_ResetCameraDataIfNotCompletePermanently();
void Do_SetCompleteCameraDataToPermanentlyComplete();
Vector2 Do_FindThingPositionInTileData(const char* name);
void Do_InitAllPermanentThings();
void Do_InitPermanentThingsByRealCoordinates(float realX1, float realY1, float realX2, float realY2, bool startThings);
void Do_InitPermanentThingsByRoomBounds(LevelCameraDataInstance* instance, bool startThings);
void Do_InitPermanentThingsByGridCoordinates(int x1, int y1, int x2, int y2);
void Do_InitPermanentThingsByGridCoordinates2(int x, int y);
void Do_InitPermanentThingsByGridCoordinates3(int x, int y, const char* onlyWithThisName);
//private
Entity Do_BuildThingFromData(int i, int j, ThingInstance* data);
//
void Do_FlipGameState(int nextState);
void Do_FlipGameStateBack();
Entity Do_BuildNewEntity();
Entity Do_BuildNewEntityWithName(const char* name);
void Do_FreezeEntityTillOnScreen(Entity entity);
void Do_FreezeEntityTillOnScreen2(Entity entity, bool facesPlayer, bool isFacingFlipped);
void Do_TurnOnMirrorEffect(Entity entity);
void Do_TurnOffMirrorEffect(Entity entity);
void Do_ActivateHitFlashKit(Entity entity);
void Do_SetBodyMaxDecelerationToInfinite(Entity entity);
void Do_SetBodyMaxDeceleration(Entity entity, float value);
int Get_NextBossMove(Entity entity);
int Get_IntTag(Entity entity);
void Do_SetIntTag(Entity entity, int value);
int Get_StepCounter(Entity entity);
void Do_IncrementStepCounter(Entity entity);
void Do_ResetStepCounter(Entity entity);
void Do_SetMove(Entity entity, int value);
int Get_Move(Entity entity);
void Do_SetStep(Entity entity, int value);
int Get_Step(Entity entity);
int Get_AmountOfBounces(Entity entity);
bool Do_Bounce(Entity entity, float dampener, float jumpSpeed, float velocityIncrease, bool fallFirstBounce);
void Do_ResetStepTimer(Entity entity);
Timer* Get_StepTimer(Entity entity);
bool Do_UpdateStepTimer(Entity entity, const char* tuning);
bool Do_UpdateStepTimer2(Entity entity, int limit);
void Do_SetBodyFramesInAir(Entity entity, int value);
void Do_SetBodyIgnoreGravityY(Entity entity, bool value);
void Do_SetBodyIsOneWayPlatform(Entity entity, bool value);
void Do_SetBodyIsMovingPlatform(Entity entity, bool value);
void Do_SetBodyCannotBePushed(Entity entity, bool value);
void Do_SetBodyPushes(Entity entity, bool value);
void Do_SetBodyCollideWithBody(Entity entity, void (*colliderBody)(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical));
void Do_SetBodyCollideWithCollision(Entity entity, bool (*colliderCollision)(Body* myBody, int x, int y, int width, int height, int myDirectionX, int myDirectionY, int collisionBit, bool isVertical));
void Do_SetBodyIsBullet(Entity entity, bool value);
void Do_SetBodyIgnoreEverythingExceptPlayer(Entity entity, bool value);
void Do_SetBodyIgnoreBullets(Entity entity, bool value);
void Do_SetBodyIgnoreBakedCollision(Entity entity, bool value);
void Do_SetBodyType(Entity entity, int type);
void Do_SetBodyIgnoreAllCollision(Entity entity, bool value);
void Do_SetBodyStatic(Entity entity, bool value);
void Do_SetBodyDisabled(Entity entity, bool value);
void Do_SetBodyDisabled2(Entity entity, bool value, int number);
EntitySearch* Do_SearchForEntitiesWithName(const char* name);
EntitySearch* Do_SearchForEntitiesWithName2(const char* name, bool isReverse);
EntitySearch* Do_SearchForEntitiesWithIntTag(int value);
EntitySearch* Do_SearchForEntitiesWithIntTag2(int value, bool isReverse);
EntitySearch* Do_SearchForChildren(Entity entity);
EntitySearch* Do_SearchForChildren2(Entity entity, bool isReverse);
EntitySearch* Do_SearchForChildrenWithName(Entity entity, const char* name);
EntitySearch* Do_SearchForChildrenWithName2(Entity entity, const char* name, bool isReverse);
EntitySearch* Do_SearchForChildrenWithIntTag(Entity entity, int value);
EntitySearch* Do_SearchForChildrenWithIntTag2(Entity entity, int value, bool isReverse);
void Do_SetIsBlockingLineOfSight(Entity entity, bool value);
void Do_DestroyAllEnemies();
MoveGetter* Do_InitMoveGetter(Entity entity, const char* name, int movesToRemember);
NodeMovingKit* Do_InitNodeMovingKit(Entity entity, int type, bool moveContacts);
HitFlashKit* Do_InitHitFlashKit(Entity entity, int time);
MirrorEffect* Do_InitMirrorEffect(Entity entity, Color color, int depth);
void Do_SetRotate(Entity entity, float value);
void Do_Rotate(Entity entity, float value);
void DeprecatedDo_SetTag(Entity entity, int whatever, int whatever2);

void Do_IdleCircle(Entity entity, float radius, bool useX, bool useY, int idleDegreeIncrease);
void Do_SetAsUsingBulletCollisionEngine(Entity entity);
bool Do_FloatyMoveSomewhere(Entity entity, float destX, float destY, float speedAccel, float speedLimit);
bool Do_FloatyMoveSomewhere2(Entity entity, float destX, float destY, float speedAccel, float speedLimit, bool doNotResetMovementAtEnd);
bool Do_FloatyMoveSomewhere3(float* currentSpeed, Vector2* moveThis, Vector2 destination, float speedAccel, float speedLimit, bool doNotResetMovementAtEnd);
void Do_FloatyMove(Entity entity, float directionX, float directionY, float speedAccel, float speedLimit);
void Do_InitRandom(Entity entity);
void Do_InitBossRandom(Entity entity);
void Do_SetScale(Entity entity, float x, float y);
bool Do_DestroyIfUnderCameraHinge(Entity entity);
bool Do_DestroyIfOffScreen(Entity entity);
void Do_SetIgnoringTransitions(Entity entity, bool value);
void Do_DrawBodyRectangle(Entity entity, SpriteBatch* spriteBatch, double delta, int depth, Color color);
void Do_SetDepthOverride(Entity entity, int value);
void Do_ResetDepthOverride(Entity entity);
void Do_SetDepthOverride2(Entity entity, int state, int value);
void Do_ResetDepthOverride2(Entity entity, int state);
void Do_SetDrawExtraPasses(Entity entity, int extra);
void Do_SetBlendStateAdditive(Entity entity);
void Do_SetBlendStateNormal(Entity entity);
void Do_DrawFullscreenRectangle(SpriteBatch* spriteBatch, Color color);
void Do_SetAnimationTimeLimit(Entity entity, int state, int phase, int time);
void Do_SetShader(Entity entity, ShaderProgram* program);
void Do_SetShader2(Entity entity, int state, ShaderProgram* program);
void Do_SetShaderAsWhiteFlash(Entity entity);
void Do_SetupShaderSingleColorReplace(ShaderProgram* program, uint8_t targetR, uint8_t targetG, uint8_t targetB,
	uint8_t replaceR, uint8_t replaceG, uint8_t replaceB);
void Do_SetupShaderSingleColorReplace2(ShaderProgram* program, uint8_t targetR, uint8_t targetG, uint8_t targetB,
	uint8_t replaceR, uint8_t replaceG, uint8_t replaceB, uint8_t alpha);
void Do_SetupShaderMultiColorLength(ShaderProgram* program, int length);
ShaderProgram* Do_CreateShader(const char* name);
void Do_SetupShaderMultiColor(ShaderProgram* program, int i, uint8_t targetR, uint8_t targetG, uint8_t targetB,
	uint8_t replaceR, uint8_t replaceG, uint8_t replaceB);
void Do_SetupShaderMultiColor2(ShaderProgram* program, int i, uint8_t targetR, uint8_t targetG, uint8_t targetB,
	uint8_t replaceR, uint8_t replaceG, uint8_t replaceB, uint8_t alpha);
Body* Do_InitBody(Entity entity, int width, int height);
Body* Do_InitExtraBody(Entity entity, int width, int height, bool isFollower);
void Do_SetDrawDisabled(Entity entity, bool value);
void Do_SetDrawActorUpdateDisabled(Entity entity, bool value);
void Do_TagAsEnemy(Entity entity);
void Do_SetUpdateDisabled(Entity entity, bool value);
void Do_SetUpdateAndDrawDisabled(Entity entity, bool value);
void Do_SetStunFrames(Entity entity, int value);
void Do_SetStateRotation(Entity entity, int state, float rotation);
DrawActor* Get_DrawActor(Entity entity);
//private
void Do_SetNodes(Entity entity, Point* nodes);
//
void Do_CopyGridNodesFromParent(Entity entity);
void Do_SetStringSettings(Entity entity, StringPair* stringSettings);
void Do_SetComplete(Entity entity);
void Do_SetGridPosition(Entity entity, int x, int y);
void Do_SetInitialPosition(Entity entity, float x, float y);
void Do_SetPosition(Entity entity, float x, float y);
void Do_SetName(Entity entity, const char* name);
void Do_SetDrawOffset(Entity entity, int x, int y);
void Do_DrawLineOfSight(Entity entity, SpriteBatch* spriteBatch, float offsetX, float offsetY, bool limit, int limitAngle);
void Do_MoveCircle(Entity entity, float degree, float degreeOffset, float radius);
void Do_MoveCircle2(Entity entity, float degree, float degreeOffset, float radius, bool useX, bool useY);
void Do_MoveCircle3(Entity entity, float degree, float degreeOffset, float radius, bool useX, bool useY, int directionX, int directionY, float mulX, float mulY);
bool Do_MoveCircleAroundPosition(Entity entity, float degree, float degreeOffset, float radius, Vector2 position, float speed);
Vector2 Get_MoveCircleAroundPositionDestination(float degree, float degreeOffset, float radius, Vector2 position);
void Do_DefaultQuickDebugCamera(Entity entity);
void Do_LoopSound(const char* sound, int number);
void Do_SynchronizeAnimation(Entity entity, int state, int phase);
void Do_SynchronizeAnimation2(Animation* anim);
void Do_Vibrate(int player, int priority, int frames, float leftMotor, float rightMotor);
void Do_Vibrate2(Entity entity, int priority, int frames, float leftMotor, float rightMotor);
void Do_RandomShake(Entity entity, int state, int amount);
void Do_RandomShake2(Entity entity, int amount);
void Do_Shake(Entity entity, int state, int amountX, int amountY);
void Do_ClearShake(Entity entity);
void Do_ClearShake2(Entity entity, int state);
ParticleInstance* Do_AddParticle(Entity entity, const char* name);
ParticleInstance* Do_AddParticle2(const char* name, Vector2 absolutePos);
ParticleInstance* Do_AddParticle3(const char* name, Vector2 absolutePos, int rangeX, int rangeY);
ParticleInstance* Do_AddParticle4(const char* name, float absoluteX, float absoluteY);
Point Get_RandomPointInBounds(Point bounds, bool wrapped, Random32* random);
ParticleInstance* Do_AddParticle5(const char* name, float absoluteX, float absoluteY, int rangeX, int rangeY);
void Do_AddParticles(const char* name, Vector2 absolutePos, int amount);
void Do_AddParticles2(const char* name, float absoluteX, float absoluteY, int amount);
void Do_AddParticles3(const char* name, Vector2 absolutePos, int amount, int rangeX, int rangeY);
void Do_AddParticles4(const char* name, float absoluteX, float absoluteY, int amount, int rangeX, int rangeY);
void Do_DestroyParticlesByName(const char* name);
void Do_ImprintTile1(Vector2 position, int type);
void Do_ImprintTile2(Vector2 position, int type, int offsetX, int offsetY);
void Do_ImprintTile3(Vector2 position, int type, int width, int height);
void Do_ImprintTiles(Entity entity, float x, float y, int type, int amountX, int amountY);
void Do_ImprintTiles4(Vector2 position, int type, int width, int height, int offsetX, int offsetY);
void Do_ImprintTile5(int type, float x, float y);
void Do_ImprintTile6(int type, float x, float y, int offsetX, int offsetY);
void Do_ImprintTiles7(int type, float x, float y, int width, int height);
void Do_FlipX(Entity entity);
void Do_SetFlipX(Entity entity, int value);
void Do_SetFlipX2(Entity entity, float value);
void Do_SetFlipX3(Entity entity, double value);
void Do_SetFlipX4(Entity entity, bool value);
void Do_FlipY(Entity entity);
void Do_SetFlipY(Entity entity, int value);
void Do_SetFlipY2(Entity entity, float value);
void Do_SetFlipY3(Entity entity, double value);
void Do_SetFlipY4(Entity entity, bool value);
void Do_AddCameraShake(int timerLimit, int minX, int maxX, int minY, int maxY);
void Do_ShakeCamera(int minX, int maxX, int minY, int maxY);
void Do_AddCameraShakeWhileOnScreen(Entity entity, int timerLimit, int minX, int maxX, int minY, int maxY, float mul);
void Do_FacePlayer(Entity entity, bool reverse);
void Do_FacePlayer2(Entity entity);
void Do_FaceSomewhere(Entity entity, float x);
void Do_FaceSomewhere2(Entity entity, float x, bool reverse);
void Do_ResetFrameTimers(Timer* timers, int time);
void Do_ResetFrameTimer(Timer* timer, int time);
void Do_ResetFrameTimer2(Timer* timer);
void Do_ResetEaseTimer(TimerDouble* timer, int time);
bool Do_MoveToPlayer(Entity entity, float speed);
bool Do_MoveToPlayer2(Entity entity, float speed, bool nullifyX, bool nullifyY);
void Do_MoveToClosestPlayer(Entity entity, float speed);
void Do_PlaySoundWhileOnScreen(Entity entity, const char* name);
void Do_PauseAllSounds(int priority);
void Do_ResumeAllSounds(int priority);
void Do_StopAllSounds();
void Do_PlaySound(const char* name);
void Do_PlaySoundWithForcedVolume(const char* name, float forcedVolume);
void Do_StopSound(const char* name);
void Do_PauseMusic(int priority);
void Do_ResumeMusic(int priority);
void Do_StopMusic();
void Do_PlayMusic(const char* name);
void Do_PlayMusic2(const char* nextTrack, bool isLooping, bool isForced);
void Do_PlayMusic3(const char* name, bool isLooping, bool isForced, bool isFadeIn, int fadeInTime, bool isFadeOut, int fadeOutTime);
void Do_PlayPreviousTrack();
void Do_FadeOutMusic(int time);
void Do_DestroyChildren(Entity entity);
void Do_DestroyChildrenByName(Entity entity, const char* name);
void Do_DestroyChildrenByName2(Entity entity, const char* name, const char* particle);
void Do_DestroyEntitiesWithName(const char* name);
void Do_DestroyEntitiesWithName2(const char* name, const char* particle);
void Do_KillIfUnderCamera(Entity entity);
void Do_SetDrawDisabledByModuloOverHalf(Entity entity, int value);
void Do_SetDrawDisabledByModuloOverHalf2(Entity entity, int value, int source);
void Do_SetDrawDisabledByModulo(Entity entity, int value, int target);
void Do_SetDrawDisabledByModulo2(Entity entity, int value, int target, int source);
void Do_SetColorByModulo(Entity entity, Color tint, int value, int target);
void Do_SetColorByModulo2(Entity entity, Color tint, int value, int target, int source);
void Do_SetColorByModuloOverHalf(Entity entity, Color tint, int value);
void Do_SetColorByModuloOverHalf2(Entity entity, Color tint, int value, int source);
void Do_SetHitFlashByModulo(Entity entity, int value, int target);
void Do_SetHitFlashByModulo2(Entity entity, int value, int target, int source);
void Do_SetHitFlashByModuloOverHalf(Entity entity, int value);
void Do_SetHitFlashByModuloOverHalf2(Entity entity, int value, int source);
bool Do_MoveSomewhereByPoint(Entity entity, Point target, float speed);
bool Do_MoveSomewhereByVector(Entity entity, Vector2 target, float speed);
bool Do_MoveSomewhere(Entity entity, float targetX, float targetY, float speed);
bool Do_MoveSomewhereToVector(Vector2* moveThis, Vector2 target, float speed);
void Do_SetImage(Entity entity, int state, int phase);
void Do_SetImage2(Entity entity, int state, int phase, bool carry);
void Do_SetImageForced(Entity entity, int state, int phase);
void Do_SetImageForced2(Entity entity, int state, int phase, bool carry);
Entity Do_AddAnimation(Entity entity, float x, float y, int timeLimit, const char* name);
void Do_RestrictOnSides(Entity entity);
void Do_SetColor(Entity entity, Color color);
void Do_MoveByPoint(Entity entity, Point move, float speed);
void Do_MoveByVector(Entity entity, Vector2 move, float speed);
void Do_Move(Entity entity, float x, float y, float speed);
void Do_MoveByPointAbsolute(Entity entity, Point move);
void Do_MoveByVectorAbsolute(Entity entity, Vector2 move);
void Do_MoveAbsolute(Entity entity, float x, float y);
void Do_MoveAtAngle(Entity entity, double angle, float speed);
void Do_AddBrDeathEffect(Entity entity, int state, int phase);
void Do_AddNdDeathEffect(Entity entity, int state, int phase);
void Do_DestroyIfDuplicate(Entity entity);
//ENDREGION

//REGION GET
Random32* Get_SharedRandom();
void Do_SetDebugForcedMove(Entity entity);
int Get_DebugForcedMove(Entity entity);
int Get_AmountOfBodies(Entity entity);
MirrorEffect* Get_MirrorEffect(Entity entity);
Random32* Get_Random(Entity entity);
NodeMovingKit* Get_NodeMovingKit(Entity entity);
HitFlashKit* Get_HitFlashKit(Entity entity);
int DeprecatedGet_Tag(Entity entity, int whatever);
MoveGetter* Get_MoveGetter(Entity entity);
float Get_Rotate(Entity entity);
int Get_AttackId();
int Get_LengthUntilTiles(int xPos, int yPos, int directionX, int directionY);
int Get_ClosestTileUp(Entity entity);
int Get_ClosestTileDown(Entity entity);
int Get_ClosestTileRight(Entity entity);
int Get_ClosestTileLeft(Entity entity);
int Get_ClosestTile(Entity entity);
float Get_ScaleX(Entity entity);
float Get_ScaleY(Entity entity);
Entity* Get_EntitiesInPlay();
GameSaveData* Get_CurrentSaveData();
double Get_CurrentCircleX(float degree, float degreeOffset, float radius);
double Get_CurrentCircleY(float degree, float degreeOffset, float radius);
int Get_DirectionFromBool(bool value);
int Get_DirectionFromBool2(bool value, bool flip);
int Get_TileSize();
int Get_HalfTileSize();
float Get_InterpolatedX(Entity entity, double delta);
float Get_InterpolatedY(Entity entity, double delta);
Vector2 Get_AdjustedMouse();
float Get_AdjustedMouseX();
float Get_AdjustedMouseY();
float Get_MouseX();
float Get_MouseY();
Color Get_Color(Entity entity);
CollisionEngine* Get_CollisionEngine();
Point Get_Node(Entity entity, int i);
Point Get_NodeAsGrid(Entity entity, int i);
int Get_IndexOfRandomNode(Entity entity, Random32* random);
int Get_IndexOfRandomNode2(Entity entity, Random32* random, int ignore);
int Get_AmountOfNodes(Entity entity);
Point Get_RandomNode(Entity entity, Random32* random);
Point Get_RandomNode2(Entity entity, Random32* random, int ignore);
int Get_IndexOfClosestNodeToPlayerX(Entity entity, int losOffsetX, int losOffsetY);
int Get_IndexOfClosestNodeToThing(Entity entity, Entity target);
Point Get_ClosestNodeToPlayerX(Entity entity, int losOffsetX, int losOffsetY);
Point Get_ClosestNodeToPlayerY(Entity entity);
Entity Get_ParentEntity(Entity entity);
Entity Get_Entity(int entityNumber);
int Get_ParentNumber(Entity entity);
void Do_SetParentNumber(Entity entity, int value);
const char* Get_Name(Entity entity);
Vector2 Get_InitialPosition(Entity entity);
Point Get_InitialPositionAsPoint(Entity entity);
Vector2 Get_FakePosition(Entity entity);
Point Get_GridPosition(Entity entity);
int Get_CurrentImagePhase(Entity entity, int state);
Camera* Get_Camera();
Rectangle Get_CameraRectangle();
Rectangle Get_CameraRectangleExtended();
float Get_CenterOfCameraX();
float Get_CenterOfCameraY();
float Get_TopOfCamera();
float Get_RightOfCamera();
float Get_BottomOfCamera();
float Get_LeftOfCamera();
int Get_EntityNumber(Entity entity);
int Get_PlayerNumber(Entity entity);
void Do_SetPlayerNumber(Entity entity, int playerNumber);
GameState* Get_ActiveGameState();
LevelData* Get_LevelData();
Resource* Get_LevelDataResource();
const char* Get_LevelFileName();;
Rectangle Get_BodyRectangle(Entity entity);
Body* Get_Body(Entity entity);
Body* Get_Body2(Entity entity, int number);
float Get_X(Entity entity);
float Get_Y(Entity entity);
Vector2 Get_PositionFromBody(Entity entity);
Vector2 Get_Position(Entity entity);
Vector2 Get_LastRenderPosition(Entity entity);
float Get_InitialX(Entity entity);
float Get_InitialY(Entity entity);
StringPair* Get_InitialStringSettingsFromMap(ComponentType componentType);
const char* Get_TypeName(void* anyObject);
int Get_FacingDirection(Entity entity);
int Get_RandomValidSpot(Entity entity, Random32* random, Vector2* spotTo);
int Get_RandomValidSpot2(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY);
int Get_RandomValidSpot3(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY, bool lockToTile);
int Get_RandomValidSpot4(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY, bool lockToTile, float anchorX, float anchorY, float minLimitToAnchor, float maxLimitToAnchor);
int Get_RandomValidSpot5(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY, bool lockToTile, float anchorX,
	float anchorY, float minLimitToAnchor, float maxLimitToAnchor, float minLimitToCurrentSpot, float maxLimitToCurrentSpot);
int Get_RandomValidSpot6(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY, bool lockToTile, float anchorX,
	float anchorY, float minLimitToAnchor, float maxLimitToAnchor, float minLimitToCurrentSpot, float maxLimitToCurrentSpot, int validityCondition);
int Get_RandomValidSpot7(Entity entity, Random32* random, Vector2* spotTo, bool lockX, bool lockY, bool lockToTile, float distAnchorX,
	float distAnchorY, float minLimitToAnchor, float maxLimitToAnchor, float minLimitToCurrentSpot, float maxLimitToCurrentSpot, int validityCondition, float lineOfSightAnchorX, float lineOfSightAnchorY);
int Get_ValueLockedToTileSize(float value);
int Get_TuningAsInt(Entity entity, const char* dataName);
float Get_TuningAsFloat(Entity entity, const char* dataName);
int Get_GlobalTuningAsInt(Entity entity, const char* dataName);
float Get_GlobalTuningAsFloat(Entity entity, const char* dataName);
int Get_Global777TuningAsInt(Entity entity, const char* dataName);
float Get_Global777TuningAsFloat(Entity entity, const char* dataName);
int Get_System777TuningAsInt(Entity entity, const char* dataName);
float Get_System777TuningAsFloat(Entity entity, const char* dataName);
//private
const char* Get_TuningNameAsInt(Entity entity, const char* dataName);
const char* Get_TuningName(Entity entity, const char* dataType, const char* dataName);
//
const char* Get_TuningNameAsFloat(Entity entity, const char* dataName);
int Get_ClampedValueAsInt(int value, int limit);
float Get_ClampedValueAsSingle(float value, float limit);
double Get_ClampedValueAsDouble(double value, double limit);
int Get_AmountOfTiles(float x, float y, int directionX, int directionY, const int* types);
int Get_AmountOfTiles2(float x, float y, int directionX, int directionY, const int* types, int returnOnFailure);
int Get_NearestTileDirection(float x, float y, const int* types);
void Get_NearestTileDirectionAsPoint(Point* point, float x, float y, const int* types);
int Get_AmountOfTilesInDirection(float x, float y, int direction, int outOfBoundsExtra, const int* types);
int Get_AmountOfTilesInDirection2(float x, float y, int direction, int outOfBoundsExtra, const int* types, int returnValue);
int Get_LengthUntilTiles2(int x, int y, int directionX, int directionY, int outOfBoundsExtra, const int* types);
int Get_LengthUntilTiles3(int x, int y, int directionX, int directionY, int outOfBoundsExtra, const int* types, int returnValue);
Animation* Get_Animation(Entity entity, int state, int phase);
Animation* Get_CurrentAnimation(Entity entity, int state);
void Get_PointDirectionFromEightWayIntegerDirection(Point* point, int value);
Body* Get_PlayerBody();
Entity Get_ClosestPlayer2(Entity entity);
Vector2 Get_PlayerPosition();
float Get_PlayerX();
float Get_PlayerY();
float Get_PlayerX2(int i);
float Get_PlayerY2(int i);
float Get_ClosestPlayerX(Entity entity);
float Get_ClosestPlayerY(Entity entity);
double Get_AngleToPlayer(Entity entity);
double Get_AngleToPlayer2(Entity entity, int i);
double Get_AngleToClosestPlayer(Entity entity);
double Get_AngleToThing(Entity entity, Entity target);
double Get_AngleToSomewhere(Entity entity, float otherX, float otherY);
double Get_AngleToSomewhere2(Vector2 valueA, Vector2 valueB);
float Get_DegreeAngleFromRadianAngle(float degree);
double Get_Angle(float x1, float y1, float x2, float y2);
void Get_VectorAngle(float x1, float y1, float x2, float y2, Vector2* vec);
void Get_VectorAngleToSomewhere(Entity entity, float otherX, float otherY, Vector2* vec);
int Get_Width(Entity entity);
int Get_Height(Entity entity);
Point Get_BodyCollisionGridPosition(Entity entity);
int Get_BodyCollisionGridPositionX(Entity entity);
int Get_BodyCollisionGridPositionY(Entity entity);
int Get_AmountOfMyChildrenByName(Entity entity, const char* name);
int Get_AmountOfMyChildren(Entity entity);
const char* Get_StringSettingAsString(Entity entity, const char* key);
StringPair* Get_StringSettings(Entity entity);
int Get_StringSettingAsInt(Entity entity, const char* setting);
bool Get_StringSettingAsBooleanByChar(Entity entity, const char* setting);
float Get_StringSettingAsFloat(Entity entity, const char* setting);
bool Get_StringSettingAsBoolean(Entity entity, const char* setting);
double Get_VectorFromRadianAngleX(double radianAngle);
double Get_VectorFromRadianAngleY(double radianAngle);
void Get_VectorFromRadianAngle(double radianAngle, Vector2* vec);
void Get_VectorFromDegreeAngle(float degreeAngle, Vector2* vec);
double Get_VectorDirectionToPlayerX(Entity entity);
double Get_VectorDirectionToPlayerY(Entity entity);
double Get_VectorToAngleLegacyDoNotUse(float x, float y);
double Get_VectorToAngle(float x, float y);
double Get_WrappedAngle(double radians);
float Get_WrappedDegreeAngle(float degree);
double Get_LimitedAngle(double target, double current, double limit);
double Get_AngleDifference(double target, double current);
int Get_OriginalWidth(Entity entity);
int Get_OriginalHeight(Entity entity);
Entity Get_ChildByName(Entity entity, const char* name);
Entity Get_ChildByName2(Entity entity, const char* name, int number);
Entity Get_ChildByTag(Entity entity, int value);
Entity Get_ChildByTag2(Entity entity, int value, int number);
int Get_DirectionToPlayerX(Entity entity);
int Get_DirectionToPlayerY(Entity entity);
int Get_DirectionToSomewhereX(Entity entity, float value);
int Get_DirectionToSomewhereY(Entity entity, float value);
int Get_DirectionHelper(float target, float me);
bool Get_DirectionToPlayerBoolean(Entity entity);
bool Get_Direction(int value);
float Get_DistanceToPlayerX(Entity entity);
float Get_DistanceToPlayerY(Entity entity);
Vector2 Get_DistanceToPlayerAsVec2(Entity entity);
Vector2 Get_DistanceAsVec2(Entity entity, Vector2 pos2);
Vector2 Get_DistanceAsVec22(Vector2 pos1, Vector2 pos2);
double Get_DistanceToPlayer(Entity entity);
double Get_Distance(Entity entity, Entity target);
double Get_Distance2(Entity entity, float pos2X, float pos2Y);
double Get_Distance3(Entity entity, Vector2 pos2);
double Get_Distance4(Vector2 pos1, Vector2 pos2);
float Get_Distance5(float x1, float x2);
double Get_Distance6(float x1, float y1, float x2, float y2);
int Get_RandomBinaryDirection(Random32* random);
int Get_RandomDirection(Random32* random);
float Get_ArcVelocityX(float targetPosX, float throwPosX, int travelTime, float mul);
float Get_ArcVelocityY(float targetPosY, float throwPosY, float grav, int travelTime, float mul);
int Get_LevelFrameCount();
int Get_CollisionBit(float posX, float posY, int tileOffsetX, int tileOffsetY);
int Get_CollisionBitSafe(float posX, float posY, int tileOffsetX, int tileOffsetY, int returnValue);
int Get_DirectionFromCameraSideX(Entity entity);
int Get_DirectionFromCameraSideY(Entity entity);
Entity Do_BuildActor(Vector2 initialPosition, ThingInstance* instanceData, const char* name);
Entity Do_BuildActor2(float initialPositionX, float initialPositionY, ThingInstance* instanceData, const char* name);
Entity Do_BuildActor3(Vector2 initialPosition, ThingInstance* instanceData, const char* name, Entity parent);
Entity Do_BuildActor4(float initialPositionX, float initialPositionY, ThingInstance* instanceData, const char* name, Entity parent);
Entity Do_BuildActor5(int gridPositionX, int gridPositionY, float initialPositionX, float initialPositionY, ThingInstance* instanceData, const char* name);
Entity Do_BuildActor6(int gridPositionX, int gridPositionY, float initialPositionX, float initialPositionY, ThingInstance* instanceData, const char* name, Entity parent);
void Do_SetSeedFromInitialCoordinates(Entity entity, Random32* random);
void Do_SendBroadcast(int type);
void Do_SendBroadcast2(int type, int packet1);
void Do_SendBroadcast3(int type, int packet1, int packet2);
void Do_SendBroadcast4(int type, int packet1, int packet2, int packet3);
int Get_CameraHingeBottom();
void Do_SaveGame();
void Do_SaveUserConfig();
//ENDREGION

//REGION IS
bool Is_IntersectingCameraExtended(Camera* camera, int posX, int posY, int width, int height, bool isCentered);
bool Is_IntersectingCamera(Camera* camera, int posX, int posY, int width, int height, bool isCentered);
bool Is_IntersectingCamera2(Camera* camera, int posX, int posY, int width, int height, bool isCentered, float mul);
Rectangle Get_LevelBoundsRectangle();
bool Is_InLevelBounds(Entity entity);
bool Is_ThisBodyThePlayerBody(Body* body);
bool Is_TouchingUp(Entity entity);
bool Is_TouchingRight(Entity entity);
bool Is_TouchingDown(Entity entity);
bool Is_TouchingLeft(Entity entity);
bool Is_TouchingBody(Entity entity);
bool Is_TouchingCollision(Entity entity);
bool Is_TouchingLeftOrRight(Entity entity);
bool Is_TouchingUpOrDown(Entity entity);
bool Is_BodyDisabled(Entity entity);
bool Is_BlockingLineOfSight(Entity entity);
bool Is_IgnoringTransitions(Entity entity);
bool Is_PlayerPresent(bool logWarning);
bool Is_Player(Entity entity);
bool Is_OnRightSideOfScreen(Entity entity);
bool Is_OnBottomSideOfScreen(Entity entity);
bool Is_NodesPresent(Entity entity);
bool DeprecatedIs_TagPresent(Entity entity, int i);
bool Is_DrawActorPresent(Entity entity);
bool Is_BodyPresent(Entity entity);
bool Is_Child(Entity entity);
bool Is_Complete(Entity entity);
bool Is_OnScreen(Entity entity);
bool Is_OnScreen2(Entity entity, float mul);
bool Is_OnScreen3(const Rectangle* rect);
bool Is_OnScreen4(const Rectangle* rect, float mul);
bool Is_OnScreen5(Vector2 pos);
bool Is_OnScreen6(Vector2 pos, float mul);
bool Is_OnScreenExtended(Entity entity);
bool Is_InitialStringSettingsMapPresent(ComponentType componentType);
bool Is_StringSettingsPresent(Entity entity);
bool Is_FlipX(Entity entity);
bool Is_FlipY(Entity entity);
bool Is_NearCollisionLowerRight(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionLowerLeft(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionUpperCenter(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionLowerCenter(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionMiddleRight(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionMiddleLeft(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionUpperRight(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionCenter(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollision(int x, int y, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_NearCollisionUpperLeft(Entity entity, int xDirection, int yDirection, const int* collisionToCheck);
bool Is_LineOfSight(float x1, float y1, float x2, float y2, bool respectOneWays);
bool Is_LineOfSight2(float x1, float y1, float x2, float y2);
bool Is_InLineOfSightWith(Entity entity, float targetX, float targetY, float offsetX, float offsetY);
bool Is_InLineOfSightWith2(Entity entity, float targetX, float targetY, float offsetX, float offsetY, bool respectOneWays);
bool Is_InLineOfSightWithPlayer(Entity entity);
bool Is_InLineOfSightWithPlayer2(Entity entity, float offsetX, float offsetY, int limAngle);
bool Is_InLineOfSightWithPlayer3(Entity entity, float offsetX, float offsetY);
bool Is_PlayerNearBody(Entity entity, int buffer);
bool Is_ClosestPlayerNearBody(Entity entity, int buffer);
bool Is_LeftOfCamera(Entity entity);
bool Is_RightOfCamera(Entity entity);
bool Is_TopOfCamera(Entity entity);
bool Is_BottomOfCamera(Entity entity);
bool Is_UnderCameraHinge(Entity entity);
bool Is_UnderCameraHinge2(Entity entity, int offset);
bool Is_UnderLevelBounds(Entity entity);
bool Is_UnderLevelBounds2(Entity entity, int offset);
bool Is_UnderCamera(Entity entity);
bool Is_UnderCamera2(Entity entity, int offset);
bool Is_NearPlayerX(Entity entity, int buffer);
bool Is_NearPlayerY(Entity entity, int buffer);
bool Is_OnDrawPhase(Entity entity, int state, int phaseToCheck);
bool Is_AnimationComplete(Entity entity, int state, int phase);
bool Is_ImagePhaseTheSame(Entity entity, int state, int phase);
bool Is_LevelFrameCountModuloOverHalf(int value);
bool Is_LevelFrameCountModulo(int value, int target);
bool Is_UpdateDisabled(Entity entity);
bool Is_TaggedAsEnemy(Entity entity);
bool Is_DrawDisabled(Entity entity);
//ENDREGION

//TEMPLATE STUFF

void* Get_Component(ComponentType ctype, Entity entity);
void* Do_InitComponent(ComponentType ctype, Entity entity);
Entity Get_ChildByComponent(ComponentType ctype, Entity entity);
void Do_SetBoolTag(ComponentType ctype, Entity entity, bool value);
void Do_RemoveComponent(ComponentType ctype, Entity entity);
bool Is_ComponentPackPresent(ComponentType ctype);
bool Is_ComponentPresent(ComponentType ctype, Entity entity);
ComponentPack* Get_ComponentPack(ComponentType ctype);
Entity Get_FirstSetEntity(ComponentType ctype);
void* Get_FirstSetComponent(ComponentType ctype);
bool Is_AnyEntityInPack(ComponentType ctype);
void* TryGet_Component(ComponentType ctype, Entity entity, bool* wasSuccessful);
void* TryGet_FirstSetComponent(ComponentType ctype, bool* wasSuccessful);
/*
Entity Do_FindEntityByPosition(float positionX, float positionY, bool useX, bool useY, bool useInitial)
{
	std::vector<Entity> entitiesInPlay = Get_ActiveGameState()->GetEntitiesInPlay();
	for (int i = 0; i < entitiesInPlay.size(); i += 1)
	{
		Entity entity = entitiesInPlay[i];
		if (Is_ComponentPresent<T>(entity))
		{
			if (useX)
			{
				if ((!useInitial && Get_X(entity) == positionX) || (useInitial && Get_InitialX(entity) == positionX))
				{
					return entity;
				}
			}
			if (useY)
			{
				if ((!useInitial && Get_Y(entity) == positionY) || (useInitial && Get_InitialY(entity) == positionY))
				{
					return entity;
				}
			}
		}
	}
	return Entity::Nothing;
}
Entity Get_DummyEntityUniqueToPack(OeComponentPack<T>* pack, const char* name)
{
	if (!pack->IsAnyEntityInPack())
	{
		Entity entity = Get_ActiveGameState()->BuildNewEntity();
		Do_SetName(entity, name);
		return entity;
	}
	else
	{
		return pack->GetFirstSetEntity();
	}
}
void Do_RemoveUniqueDummyEntity(OeComponentPack<T>* pack)
{
	if (pack->IsAnyEntityInPack())
	{
		Get_ActiveGameState()->RemoveEntity(pack->GetFirstSetEntity());
	}
}
void Do_RemoveUniqueDummyEntity()
{
	Do_RemoveUniqueDummyEntity(Get_ComponentPack<T>());
}
Entity Get_DummyEntityUniqueToPack(const char* name)
{
	return Get_DummyEntityUniqueToPack(Get_ComponentPack<T>(), name);
}
void Do_RemoveAndInitComponent(Entity entity)
{
	Do_RemoveComponent<T>(entity);
	Do_InitComponent<T>(entity);
}
template<class TCheckForThisTag, class TSetThisTag> void Do_SetBoolTagToEntitiesWithThisTag(bool value)
{
	EntitySearch checkForSearch = EntitySearch::SearchForEntitiesWithThisComponent<TCheckForThisTag>(EntitySearch::CreateNewAllEntitySearch(), EntitySearch(), false);
	for (int i = 0; i < checkForSearch.mList.size(); i += 1)
	{
		Do_SetBoolTag<TSetThisTag>(checkForSearch.mList[i], value);
	}
}
template<class TIgnoreThisTag, class TCheckForThisTag, class TSetThisTag> void Do_SetBoolTagToEntitiesWithThisTag(bool value)
{
	std::shared_ptr<EntitySearch> filterOutIgnoreSearch = EntitySearch::SearchForEntitiesWithThisComponent<TIgnoreThisTag>(EntitySearch::CreateNewAllEntitySearch(), EntitySearch::CreateNewBlankSearch(), true);
	std::shared_ptr<EntitySearch> checkForSearch = EntitySearch::SearchForEntitiesWithThisComponent<TCheckForThisTag>(filterOutIgnoreSearch, EntitySearch::CreateNewBlankSearch(), false);
	for (int i = 0; i < checkForSearch->mList.size(); i += 1)
	{
		Do_SetBoolTag<TSetThisTag>(checkForSearch->mList[i], value);
	}
}
std::shared_ptr<EntitySearch> Do_SearchForEntitiesWithComponent(bool isReverse)
{
	return EntitySearch::SearchForEntitiesWithThisComponent<T>(EntitySearch::CreateNewAllEntitySearch(), EntitySearch::CreateNewBlankSearch(), isReverse);
}
std::shared_ptr<EntitySearch> Do_SearchForChildrenWithComponent(Entity entity, bool isReverse)
{
	return EntitySearch::SearchForEntitiesWithThisComponent<T>(Do_SearchForChildren(entity, isReverse), EntitySearch::CreateNewBlankSearch(), isReverse);
}
std::shared_ptr<EntitySearch> Do_SearchForChildrenWithComponent(Entity entity)
{
	return Do_SearchForChildrenWithComponent<T>(entity, false);
}
std::shared_ptr<EntitySearch> Do_SearchForEntitiesWithComponent()
{
	return Do_SearchForEntitiesWithComponent<T>(false);
}
void Do_DestroyChildrenWithComponent(Entity entity)
{
	Do_DestroyChildrenWithComponent<T>(entity, "");
}
void Do_DestroyChildrenWithComponent(Entity entity, const char* particle)
{
	std::shared_ptr<EntitySearch> search = Do_SearchForChildrenWithComponent<T>(entity);
	for (int i = 0; i < search->mList.size(); i += 1)
	{
		Entity target = search->mList[i];
		if (particle != "")
		{
			Do_AddParticle(particle, Get_Position(target));
		}
		Do_SetComplete(target);
	}
}
void Do_DestroyEntitiesWithComponent(const char* particle)
{
	std::shared_ptr<EntitySearch> search = Do_SearchForEntitiesWithComponent<T>();
	for (int i = 0; i < search->mList.size(); i += 1)
	{
		Entity target = search->mList[i];
		if (particle != "")
		{
			Do_AddParticle(particle, Get_Position(target));
		}
		Do_SetComplete(target);
	}
}
void Do_DestroyEntitiesWithComponent()
{
	Do_DestroyEntitiesWithComponent<T>("");
}
void Do_UnsetAtIndexAndRemoveDummyEntityIfLast(OeComponentPack<T>* pack, int index)
{
	Entity dummyEntity = pack->Entities[index];
	pack->UnsetAtIndex(index);
	if (!pack->IsAnyEntityInPack())
	{
		Get_ActiveGameState()->RemoveEntity(dummyEntity);
	}
}
int Get_AmountOfEntitiesWithComponent()
{
	std::shared_ptr<EntitySearch> search = Do_SearchForEntitiesWithComponent<T>();
	return search->mList.size();
}
int Get_AmountOfMyChildrenWithComponent(Entity entity)
{
	std::shared_ptr<EntitySearch> search = Do_SearchForChildrenWithComponent<T>(entity);
	return search->mList.size();
}
Entity Get_ChildByComponent(Entity entity, int number)
{
	std::shared_ptr<EntitySearch> search = Do_SearchForChildrenWithComponent<T>(entity);
	if (number < search->mList.size())
	{
		return search->mList[number];
	}
	else
	{
		return Entity::Nothing;
	}
}

Entity Get_ClosestThingWithComponent(Entity entity, bool checkOnScreen, float cameraMul)
{
	return Get_ClosestThingWithComponent<T>(entity, checkOnScreen, cameraMul, false, 0, 0);
}
Entity Get_ClosestThingWithComponent(Entity entity, bool checkOnScreen,
	float cameraMul, bool usesLineOfSight, float losOffsetX, float losOffsetY)
{
	std::vector<Entity>& things = Get_EntitiesInPlay();

	int valid = -1;
	double diff = DBL_MAX;
	for (int i = 0; i < things.size(); i += 1)
	{
		Entity target = things[i];
		if (!Is_Complete(target))
		{
			if (Is_ComponentPresent<T>(entity))
			{
				bool isValid = true;
				if (checkOnScreen)
				{
					if (!Is_OnScreen(target, cameraMul))
					{
						isValid = false;
					}
				}
				if (isValid)
				{
					if (usesLineOfSight)
					{
						if (!Is_InLineOfSightWith(entity, Get_X(target), Get_Y(target), losOffsetX, losOffsetY))
						{
							isValid = false;
						}
					}
				}
				if (isValid)
				{
					double dist = Get_Distance(entity, Get_X(target), Get_Y(target));

					if (dist < diff)
					{
						valid = i;
						diff = dist;
					}
				}
			}
		}
	}

	if (valid != -1)
	{
		return things[valid];
	}

	return Entity::Nothing;
}

//*/