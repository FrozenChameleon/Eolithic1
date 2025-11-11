#pragma once

#include "../systems/SystemSimple.h"
#include "../components/CollisionImprintData.h"
#include "CollisionEngine.h"
#include "Body.h"

typedef struct MetaMapChunk MetaMapChunk;
typedef struct LevelData LevelData;

void CollisionEngineSys_ResolveBody(CollisionEngine* data, bool isVertical, Body* body);
void CollisionEngineSys_CollisionHelper(Body* body, int myDirectionX, int myDirectionY, int collisionBit);
void CollisionEngineSys_ResolveWithOtherBodies(CollisionEngine* data, Body* bodyOne, bool isVertical);
bool CollisionEngineSys_ResolvePush(CollisionEngine* data, Body* pushingBody, Body* pushedBody, bool isVertical);
void CollisionEngineSys_HandleNullDividePlusPushing(CollisionEngine* data, Body* pushingBody, Body* pushedBody, bool isVertical);
void CollisionEngineSys_ImprintToCollisionGridHelper(CollisionEngine* data, CollisionImprintData* imprint);
bool CollisionEngineSys_IsPointSafe(CollisionEngine* data, int x, int y);
//void SortPathNodes(CollisionEngine* data, std::vector<std::shared_ptr<OePathNode>>& nodes);
//int GetIndexOfNode(OePathNode givenNode, std::vector<std::shared_ptr<OePathNode>>& nodes);
bool CollisionEngineSys_CheckPoint(CollisionEngine* data, float checkX, float checkY, int directionX, int directionY, Body* body, bool isVertical);

void CollisionEngineSys_DisableDynamicGravity();

void CollisionEngineSys_CopyCollisionGridFromPristine(CollisionEngine* data);
void CollisionEngineSys_UpdateRoutine(Entity owner, CollisionEngine* data);
bool CollisionEngineSys_PushBody(CollisionEngine* data, bool isBakedCollision, bool isVertical, Body* body, const Rectangle* otherPhysicsRectangle);
bool CollisionEngineSys_IsCollisionValid(Body* bodyOne, Body* bodyTwo, bool isVertical);
void CollisionEngineSys_UpdateParticleBody(CollisionEngine* data, Body* body);
void CollisionEngineSys_RemoveAllCollisionImprints();
void CollisionEngineSys_ImprintToCollisionGrid(CollisionEngine* data, float pixelX, float pixelY, int width, int height, int type);
void CollisionEngineSys_ImprintChunkToCollisionGridWithSolid(CollisionEngine* data, MetaMapChunk* chunk);
void CollisionEngineSys_ImprintChunkToCollisionGrid(CollisionEngine* data, MetaMapChunk* chunk);
int CollisionEngineSys_GetCollisionBit(CollisionEngine* data, float x, float y);
int CollisionEngineSys_GetCollisionBitSafe(CollisionEngine* data, float x, float y, int returnValue);
int CollisionEngineSys_GetCollisionBitSafeGrid(CollisionEngine* data, int x, int y, int returnValue);
int CollisionEngineSys_GetCollisionBitGrid(CollisionEngine* data, int x, int y);
void CollisionEngineSys_SetupCollisionGrid(CollisionEngine* data, LevelData* level);
bool CollisionEngineSys_DoPlatformCollision(Body* platformBody, Body* thingBody);
Point CollisionEngineSys_GetCollisionGridPosition(float x, float y);
bool CollisionEngineSys_CheckSurroundingCollision(CollisionEngine* data, int bodyX, int bodyY, int xDirection, int yDirection, const int* collisionToCheck);
bool CollisionEngineSys_IsRectIntersectsCollision(CollisionEngine* data, int x, int y, int width, int height);
bool CollisionEngineSys_CheckFeetCollision(CollisionEngine* data, Body* body, bool checkLeft, bool checkRight, int offset, int collisionBit);
bool CollisionEngineSys_HasLineOfSight(CollisionEngine* data, float x1, float y1, float x2, float y2, bool respectOneWays);
bool CollisionEngineSys_HasLineOfSight2(CollisionEngine* data, bool draw, SpriteBatch* spriteBatch, float x1, float y1, float x2, float y2, bool respectOneWays);
int CollisionEngineSys_GetPlatformDown();
int CollisionEngineSys_GetPlatformLeft();
int CollisionEngineSys_GetPlatformRight();
int CollisionEngineSys_GetPlatformUp();
Vector2 CollisionEngineSys_GetBestPathNode(CollisionEngine* data, bool returnPosition, bool disableDiagonals, float currentX, float currentY, float targetX, float targetY, int hardLimit);
float CollisionEngineSys_GetCurrentDeceleration(float maxDecel, int framesInAir);
void CollisionEngineSys_HandleDynamicGravityY(Body* body);
void CollisionEngineSys_HandleBodiesHousekeepingHelper(CollisionEngine* data, Body* body);
void CollisionEngineSys_Step(CollisionEngine* data, bool isVertical);
void CollisionEngineSys_ResolveWithBakedCollision(CollisionEngine* data, Body* body, bool vertical);
void CollisionEngineSys_ApplyBodyVelocity(CollisionEngine* data, Body* body, bool isVertical);
void CollisionEngineSys_InitRoutine(Entity owner, CollisionEngine* data);
void CollisionEngineSys_DrawRoutine(Entity owner, CollisionEngine* data, SpriteBatch* spriteBatch);
void CollisionEngineSys_DrawTiles(GameState* scene);
//void CollisionEngineSys_DebugDrawNodes(CollisionEngine* data);
void CollisionEngineSys_DebugGenerateDebugRectangles(CollisionEngine* data);

System* CollisionEngineSys_CreateSystem();