/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#pragma once

#include "stdint.h"
#include "stdbool.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include "../math/Rectangle.h"
#include "../collections/FixedListEightInt.h"

enum
{
	BODY_PHYSICS_SCALER = 100
};

typedef struct Body Body;

typedef bool (*Body_BeforeCollideWithBodyFunc)(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
typedef void (*Body_CollideWithBodyFunc)(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
typedef bool (*Body_CollideWithCollisionFunc)(Body* myBody, int x, int y, int width, int height, int myDirectionX, int myDirectionY, int collisionBit, bool isVertical);

typedef struct Body
{
	int32_t mFramesInAir;
	int32_t mIntTag;
	int32_t mSpecialTag;
	int32_t mAttackID;
	int32_t mType;
	int32_t mDamage;
	int32_t mHitStun;
	int32_t mBodyPushAmount;
	int32_t mLastCollisionBitTouched;
	int32_t mOwner;
	int32_t mMovingPlatformEntityNumber;
	int32_t mInternalResolverCounter;
	int32_t mPhysicsOriginalWidth;
	int32_t mPhysicsOriginalHeight;
	int32_t mPhysicsWidth;
	int32_t mPhysicsHeight;
	float mMaxDeceleration;
	bool mUseOnlyFixedGravity;
	bool mIgnoreFixedGravityY;
	bool mTouchedUp;
	bool mTouchedDown;
	bool mTouchedRight;
	bool mTouchedLeft;
	bool mUsesBulletCollisionEngine;
	bool mUsesSmallerHurtbox;
	bool mCollideWithBulletsNoMatterWhat;
	bool mIsExtraBody;
	bool mIsExtraBodyThatFollows;
	bool mIsDisplayingHitSuccess;
	bool mIsHighPriorityBody;
	bool mIsMovingPlatform;
	bool mIsOneWayPlatform;
	bool mIgnoreBodies;
	bool mIgnorePlayer;
	bool mIgnoreBakedCollision;
	bool mIgnoreAllCollision;
	bool mIgnoreEverythingExceptPlayer;
	bool mIgnoreGravityX;
	bool mIgnoreGravityY;
	bool mHackTouchedWind;
	bool mIsDisabled;
	bool mIsBullet;
	bool mCannotBePushed;
	bool mPushes;
	bool mIsParticle;
	bool mCollideWithBulletsOnly;
	bool mIgnoreBullets;
	bool mIsStatic;
	bool mTouchedBody;
	bool mTouchedCollision;
	bool mTouchedTransition;
	bool mWasPushedByOneWayCollision;
	const char* mPushesThisThing;
	Point mDirection;
	Point mLastDirection;
	Vector2 mOffset;
	Vector2 mImpulse;
	Vector2 mPhysicsVelocity;
	Vector2 mPhysicsPosition;
	Vector2 mPhysicsLastLogicalPosition;
	Vector2 mPhysicsLastRenderPosition;
	Vector2 mPhysicsQueuedVelocity;
	FixedListEightInt mIgnore;
	FixedListEightInt mContact;
	FixedListEightInt mLastCollisionsTouched;
	Body_BeforeCollideWithBodyFunc mBeforeCollideWithBody;
	Body_CollideWithBodyFunc mCollideWithBody;
	Body_CollideWithCollisionFunc mCollideWithCollision;
} Body;

bool Body_DefaultBeforeColliderBody(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
void Body_DefaultColliderBody(Body* myBody, Body* otherBody, int myDirectionX, int myDirectionY, int otherDirectionX, int otherDirectionY, bool isVertical);
bool Body_DefaultColliderCollision(Body* myBody, int x, int y, int width, int height, int myDirectionX, int myDirectionY, int collisionBit, bool isVertical);
void Body_Setup(Body* body, int width, int height, bool isParticle);
void Body_UpdateLastRenderPosition(Body* body);
bool Body_IsPushesThisThingSet(Body* body);
//void DrawBody(Body* body, OeSpriteBatch* spriteBatch, double delta, int depth, Color color);
void Body_ResetCollideWithCollision(Body* body);
void Body_ResetCollideWithBody(Body* body);
void Body_ResetBeforeCollideWithBody(Body* body);
void Body_Resize(Body* body, int width, int height);
void Body_FlipBody(Body* body);
void Body_MoveByVector2(Body* body, Vector2 pixelMovement);
void Body_Move(Body* body, float pixelX, float pixelY);
Vector2 Body_GetPosition(Body* body);
Rectangle Body_GetRect(Body* body);
Rectangle Body_GetPhysicsRect(Body* body);
int Body_GetWidth(Body* body);
void Body_SetWidth(Body* body, int pixelWidth);
int Body_GetHeight(Body* body);
void Body_SetHeight(Body* body, int pixelHeight);
int Body_GetOriginalWidth(Body* body);
int Body_GetOriginalHeight(Body* body);
void Body_SetPositionByVector2(Body* body, Vector2 pixelMovement);
void Body_SetPosition(Body* body, float pixelX, float pixelY);
void Body_SetPositionX(Body* body, float pixelX);
void Body_SetPositionY(Body* body, float pixelY);
void Body_ForcePositionByVector2(Body* body, Vector2 pixelPosition);
void Body_ForcePosition(Body* body, float pixelX, float pixelY);
void Body_ForcePositionX(Body* body, float pixelX);
void Body_ForcePositionY(Body* body, float pixelY);
void Body_ForceMoveByVector2(Body* body, Vector2 pixelMovement);
void Body_ForceMove(Body* body, float pixelX, float pixelY);
void Body_ForceMoveX(Body* body, float pixelX);
void Body_ForceMoveY(Body* body, float pixelY);
Vector2 Body_GetLastRenderPosition(Body* body);
void Body_QueueMoveByVector2(Body* body, Vector2 movement);
void Body_QueueMove(Body* body, float pixelX, float pixelY);
Vector2 Body_GetQueuedVelocity(Body* body);
void Body_CommitOnNextUpdateMove(Body* body);
void Body_ForceVelocity(Body* body, Vector2 pixelVelocity);
void Body_ForceVelocityX(Body* body, float pixelVelocityX);
void Body_ForceVelocityY(Body* body, float pixelVelocityY);
Vector2 Body_GetVelocity(Body* body);
void Body_UpdateLastDirection(Body* body);
Vector2 Body_GetMovementDifference(Body* body);
void Body_UpdateLastLogicalPositionToCurrent(Body* body);
Vector2 Body_GetLastLogicalPosition(Body* body);