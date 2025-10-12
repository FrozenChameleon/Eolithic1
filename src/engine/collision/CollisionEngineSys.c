#include "CollisionEngineSys.h"

#include "../render/Color.h"
//#include "../globals/OeColors.h"
#include "../core/GameHelper.h"
#include "../core/Func.h"
#include "../globals/ObjectTypes.h"
#include "CollisionCheckData.h"
#include "../leveldata/LevelData.h"
//#include "../render/DrawTool.h"
#include "../math/Math.h"
#include "../utils/Utils.h"
#include "../globals/Globals.h"
#include "../../GlobalDefs.h"
#include "../utils/Logger.h"
#include "../globals/ObjectTypes.h"
#include "../../third_party/stb_ds.h"

#define TILE_SIZE GLOBAL_DEF_TILE_SIZE

#define USE_SCREEN_DISTANCE_CULL
#ifdef USE_SCREEN_DISTANCE_CULL
static const int SCREEN_DISTANCE_CULL_WIDTH = (1280 * BODY_PHYSICS_SCALER);
static const int SCREEN_DISTANCE_CULL_HEIGHT = (720 * BODY_PHYSICS_SCALER);
#endif

#define RESOLUTION_LIMIT 40
#define CORNER_CHECKS_LEN 8

static const Color mDebugColorActive = { 0, 255, 0, 191 };
static const Color mDebugColorTouched = { 127, 0, 127, 191 };
static const Color mDebugColor = { 128, 128, 128, 127 };
static const Color mDebugGridColor = { 255, 0, 0, 51 };
static int* _mDynamicBodies;

static bool _mCornerChecks[CORNER_CHECKS_LEN];
static ComponentPack* _mBodyPack;
static ComponentPack* _mImprintPack;
static bool _mIsDynamicGravityDisabled;

static int GetTilePos1D(int i, int j, CollisionEngine* data)
{
	return i + (j * data->mCollisionGridSize.Width);
}
static bool IsBodyUnderResolveLimit(Body* body)
{
	return (body->mInternalResolverCounter < RESOLUTION_LIMIT);
}

//private
void CollisionEngineSys_ResolveBody(CollisionEngine* data, bool isVertical, Body* body)
{
	if (IsBodyUnderResolveLimit(body))
	{
		CollisionEngineSys_ResolveWithBakedCollision(data, body, isVertical);

		CollisionEngineSys_ResolveWithOtherBodies(data, body, isVertical);
	}
	else
	{
		return;
	}
}
void CollisionEngineSys_CollisionHelper(Body* body, int myDirectionX, int myDirectionY, int collisionBit)
{
	body->mLastCollisionBitTouched = collisionBit;

	if (myDirectionY == 1)
	{
		body->mFramesInAir = 0;
		body->mTouchedDown = true;
	}

	if (myDirectionY == -1)
	{
		body->mTouchedUp = true;
	}

	if (myDirectionX == 1)
	{
		body->mTouchedRight = true;
	}

	if (myDirectionX == -1)
	{
		body->mTouchedLeft = true;
	}
}
void CollisionEngineSys_ResolveWithOtherBodies(CollisionEngine* data, Body* bodyOne, bool isVertical)
{
	if (bodyOne->mIgnoreBodies || bodyOne->mIgnoreAllCollision || bodyOne->mIsDisabled || bodyOne->mIsStatic || !IsBodyUnderResolveLimit(bodyOne))
	{
		return;
	}

	bodyOne->mInternalResolverCounter += 1;

	ptrdiff_t bodiesLen = arrlen(_mDynamicBodies);
	for (int i = 0; i < bodiesLen; i += 1)
	{
		Body* bodyTwo = ComponentPack_GetComponentAtIndex(_mBodyPack, _mDynamicBodies[i]);

		if (CollisionEngineSys_IsCollisionValid(bodyOne, bodyTwo, isVertical)) // Basic checks, ending with collision detection callback code.
		{
			bool pushed = false;

			if (CollisionEngineSys_ResolvePush(data, bodyOne, bodyTwo, isVertical))
			{
				pushed = true;
			}
			else
			{
				if (CollisionEngineSys_ResolvePush(data, bodyTwo, bodyOne, isVertical))
				{
					pushed = true;
				}
			}

			if (pushed)
			{
				CollisionEngineSys_ResolveWithOtherBodies(data, bodyOne, isVertical); // Restart this function - the array from the broad search is no longer 100% valid after pushing.
				return;
			}
		}
	}
}
bool CollisionEngineSys_ResolvePush(CollisionEngine* data, Body* pushingBody, Body* pushedBody, bool isVertical)
{
	if (Body_IsPushesThisThingSet(pushingBody))
	{
		if ((Get_Entity(pushingBody->mOwner) == ENTITY_NOTHING) || (Get_Entity(pushedBody->mOwner) == ENTITY_NOTHING))
		{
			return false;
		}
		if (pushingBody->mPushesThisThing != (Get_Name(Get_Entity(pushedBody->mOwner))))
		{
			return false;
		}
	}
	else
	{
		if (!pushingBody->mPushes) // Push check time.
		{
			return false;
		}
	}

	if (pushedBody->mCannotBePushed || pushedBody->mIsStatic)
	{
		return false;
	}

	Rectangle otherPhysicsRectangle = Body_GetPhysicsRect(pushingBody);
	if (CollisionEngineSys_PushBody(data, false, isVertical, pushedBody,&otherPhysicsRectangle))
	{
		Rectangle pushedBodyRectangle = Body_GetRect(pushedBody);
		Rectangle pushingBodyRectangle = Body_GetRect(pushingBody);
		if (Rectangle_Center(&pushedBodyRectangle).Y < Rectangle_Center(&pushingBodyRectangle).Y)
		{
			if (pushingBody->mIsMovingPlatform && isVertical && (pushedBody->mMovingPlatformEntityNumber == ENTITY_NOTHING) 
				&& (pushedBody->mLastDirection.Y > 0)) // Moving platform check.
			{
				pushedBody->mMovingPlatformEntityNumber = pushingBody->mOwner;
			}
		}

		if (data->mIsNullDividePlus)
		{
			CollisionEngineSys_HandleNullDividePlusPushing(data, pushingBody, pushedBody, isVertical);
		}

		return true;
	}
	else
	{
		return false;
	}
}
void CollisionEngineSys_HandleNullDividePlusPushing(CollisionEngine* data, Body* pushingBody, Body* pushedBody, bool isVertical)
{
	if (data->mDefaultBodyPushAmount != 0)
	{
		int pushingDirectionX = pushingBody->mLastDirection.X;
		int pushingDirectionY = pushingBody->mLastDirection.Y;

		if (isVertical)
		{
			pushingDirectionX = 0;
		}
		else
		{
			pushingDirectionY = 0;
		}

		if (pushingBody->mBodyPushAmount == 0)
		{
			Body_QueueMove(pushedBody, pushingDirectionX * data->mDefaultBodyPushAmount, pushingDirectionY * data->mDefaultBodyPushAmount);
			Body_QueueMove(pushingBody, -pushingDirectionX * data->mDefaultBodyPushAmount, -pushingDirectionY * data->mDefaultBodyPushAmount);
		}
		else
		{
			Body_QueueMove(pushedBody, pushingDirectionX * pushingBody->mBodyPushAmount, pushingDirectionY * pushingBody->mBodyPushAmount);
			Body_QueueMove(pushingBody, -pushingDirectionX * pushedBody->mBodyPushAmount, -pushingDirectionY * pushedBody->mBodyPushAmount);
		}
	}
}
void CollisionEngineSys_ImprintToCollisionGridHelper(CollisionEngine* data, CollisionImprintData* imprint)
{
	for (int i = 0; i < imprint->mWidth; i += 1)
	{
		for (int j = 0; j < imprint->mHeight; j += 1)
		{
			int tempX = imprint->mPosition.X + i;
			int tempY = imprint->mPosition.Y + j;
			if ((tempX >= 0) && (tempY >= 0) && (tempX < data->mCollisionGridSize.Width) && (tempY < data->mCollisionGridSize.Height))
			{
				data->mCollisionGrid[GetTilePos1D(tempX, tempY, data)] = imprint->mType;
			}
			else
			{
				Logger_LogError("Collision imprint out of bounds");
			}
		}
	}
}
bool CollisionEngineSys_IsPointSafe(CollisionEngine* data, int x, int y)
{
	int gridWidth = data->mCollisionGridSize.Width;
	int gridHeight = data->mCollisionGridSize.Height;
	if ((x < 0) || (y < 0) || (x >= gridWidth) || (y >= gridHeight))
	{
		return false;
	}

	return true;
}
/*
void CollisionEngineSys_SortPathNodes(CollisionEngine* data, std_vector<std_shared_ptr<OePathNode>>& nodes)
{
	//for (int i = 0; i < nodes.Count; i += 1)
	//{
	//	OePathNode node = nodes[i];
	//	int index = data.mTempNodes.Count;
	//	for (int j = 0; j < data.mTempNodes.Count; j += 1)
	//	{
	//		OePathNode tempNode = data.mTempNodes[j];
	//		if (node.mTotalDistance <= tempNode.mTotalDistance)
	//		{
	//			index = j;
	//			break;
	//		}
	//	}
	//	data.mTempNodes.Insert(index, node);
	//}
	//
	//nodes.Clear();
	//
	//for (int i = 0; i < data.mTempNodes.Count; i += 1)
	//{
	//	nodes.Add(data.mTempNodes[i]);
	//}
	//
	//data.mTempNodes.Clear();
}
int CollisionEngineSys_GetIndexOfNode(OePathNode givenNode, std_vector<std_shared_ptr<OePathNode>>& nodes)
{
	return 0;
	//return OeListTools.GetIndexOfValue(givenNode, nodes);
}
*/
bool CollisionEngineSys_CheckPoint(CollisionEngine* data, float checkX, float checkY, int directionX, int directionY, Body* body, bool isVertical)
{
	Point point = CollisionEngineSys_GetCollisionGridPosition(checkX, checkY);
	if ((point.X >= 0) && (point.Y >= 0) && (point.X < data->mCollisionGridSize.Width) // Check for safety make this a universal method some time.
		&& (point.Y < data->mCollisionGridSize.Height))
	{
		if (data->mCollisionGrid[GetTilePos1D(point.X, point.Y, data)] != 0)
		{
			int tempX = (point.X * TILE_SIZE);
			int tempY = (point.Y * TILE_SIZE);
			int tempWidth = TILE_SIZE;
			int tempHeight = TILE_SIZE;

			//collision check
			bool collide = false;
			int physicsScaler = BODY_PHYSICS_SCALER;
			Rectangle physicsRect = Body_GetPhysicsRect(body);
			Rectangle testRect = { tempX * physicsScaler, tempY * physicsScaler, tempWidth * physicsScaler, tempHeight * physicsScaler };
			if (Rectangle_Intersects(&physicsRect, &testRect))
			{
				collide = true;
			}

			if (collide)
			{
				CollisionCheckData collisionCheckData = { 0 };
				int collisionToCheck = data->mCollisionGrid[GetTilePos1D(point.X, point.Y, data)];
				if (!FixedListEightInt_Contains(&body->mLastCollisionsTouched, collisionToCheck))
				{
					FixedListEightInt_Add(&body->mLastCollisionsTouched, collisionToCheck);
				}
				if (FixedListEightInt_Contains(&body->mIgnore, collisionToCheck))
				{
					return false;
				}

				collisionCheckData.mCollisionToReport = collisionToCheck;

				//TODO C99GameHelper_BakedCollisionCheck(tempX, tempY, collisionToCheck, body, isVertical, &collisionCheckData);

				if (!collisionCheckData.mDisableCollision)
				{
					bool move = body->mCollideWithCollision(body, tempX, tempY, tempWidth, tempHeight, directionX, directionY, collisionCheckData.mCollisionToReport, isVertical);

					if (move)
					{
						Rectangle otherPhysicsRectangle = { tempX * physicsScaler, tempY * physicsScaler, tempWidth * physicsScaler, tempHeight * physicsScaler };
						CollisionEngineSys_PushBody(data, true, isVertical, body, &otherPhysicsRectangle);

						body->mTouchedCollision = true;

						CollisionEngineSys_CollisionHelper(body, directionX, directionY, collisionCheckData.mCollisionToReport);
						return true;
					}
				}
			}
		}
	}
	return false;
}

//public
void CollisionEngineSys_DisableDynamicGravity()
{
	_mIsDynamicGravityDisabled = true;
}
void CollisionEngineSys_SetupSystem()
{
	//_mUpdateRoutine = UpdateRoutine;
	//_mInitRoutine = InitRoutine;
	//_mDrawRoutine = DrawRoutine;
}
void CollisionEngineSys_CopyCollisionGridFromPristine(CollisionEngine* data)
{
	data->mCollisionGrid = data->mCollisionGridPristine;
}
void CollisionEngineSys_UpdateRoutine(Entity owner, CollisionEngine* data)
{
	_mImprintPack = Get_ComponentPack(C_CollisionImprintData);
	_mBodyPack = Get_ComponentPack(C_Body);

	// Prepare collision grid
	CollisionEngineSys_CopyCollisionGridFromPristine(data);
	PackIterator iter = PackIterator_Begin;
	while (ComponentPack_Next(_mImprintPack, &iter))
	{
		CollisionEngineSys_ImprintToCollisionGridHelper(data, ComponentPack_GetComponentAtIndex(_mImprintPack, iter.mIndex));
	}
	//

	// House keeping
	iter = PackIterator_Begin;
	while (ComponentPack_Next(_mBodyPack, &iter))
	{
		Body* body = ComponentPack_GetComponentAtIndex(_mBodyPack, iter.mIndex);
		if (!body->mIsDisabled)
		{
			CollisionEngineSys_HandleBodiesHousekeepingHelper(data, body);
			arrput(_mDynamicBodies, iter.mIndex);
		}
	}
	//

	CollisionEngineSys_Step(data, true); // Step Y

	CollisionEngineSys_Step(data, false); // Step X

	ptrdiff_t bodiesLen = arrlen(_mDynamicBodies);
	for (int i = 0; i < bodiesLen; i += 1)
	{
		Body* body = ComponentPack_GetComponentAtIndex(_mBodyPack, _mDynamicBodies[i]);
		body->mPhysicsVelocity = Vector2_Zero;
	}

	arrsetlen(data->mDynamicDebugManyRectangles, 0);

#if EDITOR
	DebugGenerateDebugRectangles(data);
#endif

	arrsetlen(_mDynamicBodies, 0);
	Utils_ResetArrayAsBool(_mCornerChecks, CORNER_CHECKS_LEN, false);
	_mImprintPack = NULL;
	_mBodyPack = NULL;
}
bool CollisionEngineSys_PushBody(CollisionEngine* data, bool isBakedCollision, bool isVertical, Body* body, const Rectangle* otherPhysicsRectangle)
{
	int xDiff;
	int yDiff;

	Rectangle myPhysicsRectangle = Body_GetPhysicsRect(body);

	int32_t rightDif = Rectangle_Left(otherPhysicsRectangle) - Rectangle_Right(&myPhysicsRectangle) - 1; // Get minimums.
	int32_t leftDif = Rectangle_Right(otherPhysicsRectangle) - Rectangle_Left(&myPhysicsRectangle) + 1;
	int32_t bottomDif = Rectangle_Top(otherPhysicsRectangle) - Rectangle_Bottom(&myPhysicsRectangle) - 1;
	int32_t topDif = Rectangle_Bottom(otherPhysicsRectangle) - Rectangle_Top(&myPhysicsRectangle) + 1;

	if (Math_abs(topDif) < Math_abs(bottomDif)) // Find minimum.
	{
		yDiff = topDif;
	}
	else
	{
		yDiff = bottomDif;
	}

	if (Math_abs(rightDif) < Math_abs(leftDif))
	{
		xDiff = rightDif;
	}
	else
	{
		xDiff = leftDif;
	}

	if (isVertical) // Zero out the incorrect one.
	{
		xDiff = 0;
	}
	else
	{
		yDiff = 0;
	}

	body->mPhysicsPosition.X += xDiff;
	body->mPhysicsPosition.Y += yDiff;

	bool hasPushed = false;
	if ((xDiff != 0) || (yDiff != 0)) // We have pushed if these are not 0.
	{
		if (isVertical) // Lock to integer after being pushed.
		{
			body->mPhysicsPosition.Y = (int)(body->mPhysicsPosition.Y);
		}
		else
		{
			body->mPhysicsPosition.X = (int)(body->mPhysicsPosition.X);
		}

		if (!body->mUsesBulletCollisionEngine && !body->mIsParticle)
		{
			if (body->mPushes || Body_IsPushesThisThingSet(body)) // Recursively resolve bodies until there is no problems.
			{
				CollisionEngineSys_ResolveBody(data, isVertical, body);
			}
		}

		hasPushed = true;
	}

	return hasPushed;
}
bool CollisionEngineSys_IsCollisionValid(Body* bodyOne, Body* bodyTwo, bool isVertical)
{
#ifdef USE_SCREEN_DISTANCE_CULL
	if ((abs(bodyOne->mPhysicsPosition.X - bodyTwo->mPhysicsPosition.X) > SCREEN_DISTANCE_CULL_WIDTH) ||
		(abs(bodyOne->mPhysicsPosition.Y - bodyTwo->mPhysicsPosition.Y) > SCREEN_DISTANCE_CULL_HEIGHT))
	{
		return false;
	}
#endif

	if (bodyOne->mOwner == bodyTwo->mOwner)
	{
		return false;
	}

	if (bodyOne->mIsDisabled || bodyTwo->mIsDisabled)
	{
		return false;
	}

	if (bodyOne->mIgnoreBodies || bodyTwo->mIgnoreBodies)
	{
		return false;
	}

	if (bodyOne->mIgnoreAllCollision || bodyTwo->mIgnoreAllCollision)
	{
		return false;
	}

	if (bodyOne->mIsStatic && bodyTwo->mIsStatic)
	{
		return false;
	}

	if (((bodyOne->mType == OBJECTTYPES_PLAYER) && bodyTwo->mIgnorePlayer) ||
		((bodyTwo->mType == OBJECTTYPES_PLAYER) && bodyOne->mIgnorePlayer))
	{
		return false;
	}

	if (((bodyOne->mType != OBJECTTYPES_PLAYER) && bodyTwo->mIgnoreEverythingExceptPlayer) ||
		(bodyOne->mIgnoreEverythingExceptPlayer && (bodyTwo->mType != OBJECTTYPES_PLAYER)))
	{
		return false;
	}

	if ((bodyOne->mCollideWithBulletsOnly && !bodyTwo->mIsBullet) || (!bodyOne->mIsBullet && bodyTwo->mCollideWithBulletsOnly))
	{
		return false;
	}

	if (!bodyOne->mCollideWithBulletsNoMatterWhat && !bodyTwo->mCollideWithBulletsNoMatterWhat)
	{
		if ((bodyOne->mIgnoreBullets && bodyTwo->mIsBullet) || (bodyTwo->mIgnoreBullets && bodyOne->mIsBullet))
		{
			return false;
		}
	}

	if (FixedListEightInt_Contains(&bodyOne->mIgnore, bodyTwo->mType))
	{
		return false;
	}

	if (FixedListEightInt_Contains(&bodyTwo->mIgnore, bodyOne->mType))
	{
		return false;
	}

	//Rectangle intersection routine split in two for optimization reasons...
	//X AXIS
	int rect1_width = bodyOne->mPhysicsWidth;
	int rect1_x = (int)(bodyOne->mPhysicsPosition.X - (rect1_width / 2));

	int rect2_width = bodyTwo->mPhysicsWidth;
	int rect2_x = (int)(bodyTwo->mPhysicsPosition.X - (rect2_width / 2));

	if ((rect2_x >= (rect1_x + rect1_width)) || (rect1_x >= (rect2_x + rect2_width)))
	{
		return false;
	}
	//
	//Y AXIS
	int rect1_height = bodyOne->mPhysicsHeight;
	int rect1_y = (int)(bodyOne->mPhysicsPosition.Y - (rect1_height / 2));

	int rect2_height = bodyTwo->mPhysicsHeight;
	int rect2_y = (int)(bodyTwo->mPhysicsPosition.Y - (rect2_height / 2));

	if ((rect2_y >= (rect1_y + rect1_height)) || (rect1_y >= (rect2_y + rect2_height)))
	{
		return false;
	}
	//
	//

	/*
	bool rect_intersects = ((rect2_x < (rect1_x + rect1_width)) &&
		(rect1_x < (rect2_x + rect2_width)) &&
		(rect2_y < (rect1_y + rect1_height)) &&
		(rect1_y < (rect2_y + rect2_height)));

	if (!rect_intersects)
	{
		return false;
	}
	*/

	//Hard coded this...
	/*
	if (!Body_GetPhysicsRect(bodyOne).Intersects(Body_GetPhysicsRect(bodyTwo)))
	{
		return false;
	}
	*/

	if (!bodyOne->mIsMovingPlatform || !bodyTwo->mIsMovingPlatform) // One way platform check.
	{
		if (bodyOne->mIsOneWayPlatform || bodyTwo->mIsOneWayPlatform)
		{
			if (isVertical)
			{
				bool valid;
				if (bodyOne->mIsOneWayPlatform)
				{
					valid = CollisionEngineSys_DoPlatformCollision(bodyOne, bodyTwo);
				}
				else
				{
					valid = CollisionEngineSys_DoPlatformCollision(bodyTwo, bodyOne);
				}
				if (!valid)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	int bodyOneDirectionX = isVertical ? 0 : bodyOne->mLastDirection.X; // Directions that are given to callbacks are only for the current step type.
	int bodyOneDirectionY = isVertical ? bodyOne->mLastDirection.Y : 0;
	int bodyTwoDirectionX = isVertical ? 0 : bodyTwo->mLastDirection.X;
	int bodyTwoDirectionY = isVertical ? bodyTwo->mLastDirection.Y : 0;

	bool beforeCollisionCheck1 = bodyOne->mBeforeCollideWithBody(bodyOne, bodyTwo, bodyOneDirectionX, bodyOneDirectionY, bodyTwoDirectionX, bodyTwoDirectionY, isVertical);
	bool beforeCollisionCheck2 = bodyTwo->mBeforeCollideWithBody(bodyTwo, bodyOne, bodyTwoDirectionX, bodyTwoDirectionY, bodyOneDirectionX, bodyOneDirectionY, isVertical);
	if (!beforeCollisionCheck1 || !beforeCollisionCheck2)
	{
		return false;
	}

	if (!FixedListEightInt_Contains(&bodyOne->mContact, bodyTwo->mOwner) && !FixedListEightInt_Contains(&bodyTwo->mContact, bodyOne->mOwner)) // Contact confirmed! Callback code going.
	{
		if (bodyTwo->mPushes)
		{
			CollisionEngineSys_CollisionHelper(bodyOne, bodyOneDirectionX, bodyOneDirectionY, bodyOne->mType);
		}
		bodyOne->mCollideWithBody(bodyOne, bodyTwo, bodyOneDirectionX, bodyOneDirectionY, bodyTwoDirectionX, bodyTwoDirectionY, isVertical);
		FixedListEightInt_Add(&bodyOne->mContact, bodyTwo->mOwner);

		if (bodyOne->mPushes)
		{
			CollisionEngineSys_CollisionHelper(bodyTwo, bodyTwoDirectionX, bodyTwoDirectionY, bodyTwo->mType);
		}
		bodyTwo->mCollideWithBody(bodyTwo, bodyOne, bodyTwoDirectionX, bodyTwoDirectionY, bodyOneDirectionX, bodyOneDirectionY, isVertical);
		FixedListEightInt_Add(&bodyTwo->mContact, bodyOne->mOwner);
	}

	bodyOne->mTouchedBody = true;
	bodyTwo->mTouchedBody = true;

	return true;
}
void CollisionEngineSys_UpdateParticleBody(CollisionEngine* data, Body* body)
{
	body->mInternalResolverCounter = 0;
	if (body->mIsDisabled)
	{
		return;
	}

	Body_UpdateLastLogicalPositionToCurrent(body);
	Body_UpdateLastDirection(body);

	body->mPhysicsPosition.Y += body->mPhysicsVelocity.Y; // Y
	CollisionEngineSys_ResolveWithBakedCollision(data, body, true);
	if (!body->mIsDisabled) // X
	{
		body->mPhysicsPosition.X += body->mPhysicsVelocity.X;
		CollisionEngineSys_ResolveWithBakedCollision(data, body, false);
	}

	body->mPhysicsVelocity = Vector2_Zero;
}
void CollisionEngineSys_RemoveAllCollisionImprints()
{
	GameState_UnsetAll(Get_ActiveGameState(), C_CollisionImprintData);
}
void CollisionEngineSys_ImprintToCollisionGrid(CollisionEngine* data, float pixelX, float pixelY, int width, int height, int type)
{
	Entity collisionEntity = Get_FirstSetEntity(C_CollisionEngine);
	ComponentPack* imprintPack = Get_ComponentPack(C_CollisionImprintData);
	Point point = CollisionEngineSys_GetCollisionGridPosition(pixelX, pixelY);
	CollisionImprintData* imprintData = ComponentPack_SetExclusive(imprintPack, collisionEntity, true);
	imprintData->mPosition = point;
	imprintData->mWidth = width;
	imprintData->mHeight = height;
	imprintData->mType = type;
	CollisionEngineSys_ImprintToCollisionGridHelper(data, imprintData);
}
void CollisionEngineSys_ImprintChunkToCollisionGridWithSolid(CollisionEngine* data, MetaMapChunk* chunk)
{
	//Point position = chunk->GetRealPosition();
	//ImprintToCollisionGrid(data, position.X, position.Y, chunk.GetTilesWidth(), chunk.GetTilesHeight(), OeObjectTypes.SOLID);
}
void CollisionEngineSys_ImprintChunkToCollisionGrid(CollisionEngine* data, MetaMapChunk* chunk)
{
	//TODO LATER
	/*
	chunk.ImprintToCollisionArray(data.mCollisionGridPristine);
	chunk.ImprintToCollisionArray(data.mCollisionGrid);
	*/
}
int CollisionEngineSys_GetCollisionBit(CollisionEngine* data, float x, float y)
{
	Point point = CollisionEngineSys_GetCollisionGridPosition(x, y);
	return data->mCollisionGrid[GetTilePos1D(point.X, point.Y, data)];
}
int CollisionEngineSys_GetCollisionBitSafe(CollisionEngine* data, float x, float y, int returnValue)
{
	Point point = CollisionEngineSys_GetCollisionGridPosition(x, y);
	if (!CollisionEngineSys_IsPointSafe(data, point.X, point.Y))
	{
		return returnValue;
	}
	return data->mCollisionGrid[GetTilePos1D(point.X, point.Y, data)];
}
int CollisionEngineSys_GetCollisionBitSafeGrid(CollisionEngine* data, int x, int y, int returnValue)
{
	if (!CollisionEngineSys_IsPointSafe(data, x, y))
	{
		return returnValue;
	}

	return data->mCollisionGrid[GetTilePos1D(x, y, data)];
}
int CollisionEngineSys_GetCollisionBitGrid(CollisionEngine* data, int x, int y)
{
	return data->mCollisionGrid[GetTilePos1D(x, y, data)];
}
void CollisionEngineSys_SetupCollisionGrid(CollisionEngine* data, LevelData* level)
{
	//TODO C99
	/*
	data->mCollisionGridSize.X = 0;
	data->mCollisionGridSize.Y = 0;
	data->mCollisionGridSize.Width = level->GetGridSizeWidth();
	data->mCollisionGridSize.Height = level->GetGridSizeHeight();

	if (level->IsMetaMap())
	{
		data->mCollisionGridPristine = level->CreateEmptyCollisionArray();
		data->mCollisionGrid = level->CreateEmptyCollisionArray();
	}
	else
	{
		data->mCollisionGridPristine = level->CreateCollisionArray();
		data->mCollisionGrid = level->CreateEmptyCollisionArray();
		CopyCollisionGridFromPristine(data);
	}
	*/
}
bool CollisionEngineSys_DoPlatformCollision(Body* platformBody, Body* thingBody)
{
	Vector2 velocity = Body_GetVelocity(thingBody);
	Vector2 lastLogicalPosition = Body_GetLastLogicalPosition(thingBody);
	float halfHeightOffset = Body_GetHeight(thingBody) / 2;
	float leeway = 0;//TODOC99 GameHelper_GetMovingPlatformLeeway();
	float heightCheck = lastLogicalPosition.Y + halfHeightOffset - leeway;
	Rectangle bodyRectangle = Body_GetRect(platformBody);
	float platformTop = Rectangle_Top(&bodyRectangle);
	if ((velocity.Y <= 0) || (heightCheck >= platformTop))
	{
		return false;
	}
	return true;
}
Point CollisionEngineSys_GetCollisionGridPosition(float x, float y)
{
	Point temp = { (int)(x / TILE_SIZE), (int)(y / TILE_SIZE) };
	return temp;
}
bool CollisionEngineSys_CheckSurroundingCollision(CollisionEngine* data, int bodyX, int bodyY, int xDirection, int yDirection, const int* collisionToCheck)
{
	return false;
	//TODO C99
	/*
	Point point = Point_Add(CollisionEngineSys_GetCollisionGridPosition(bodyX, bodyY), Point_Create(xDirection, yDirection));

	if ((point.X < 0) || (point.Y < 0) || (point.X >= data->mCollisionGridSize.Width) || (point.Y >= data->mCollisionGridSize.Height))
	{
		return false;
	}

	int tilePos1D = GetTilePos1D(point.X, point.Y, data);
	int collisionToCheckLen = collisionToCheck.size();
	if (collisionToCheckLen == 0)
	{
		if (data->mCollisionGrid[tilePos1D] != OBJECTTYPES_NOTHING)
		{
			return true;
		}
	}
	else
	{
		for (int i = 0; i < collisionToCheckLen; i += 1)
		{
			if (collisionToCheck[i] != OBJECTTYPES_NOTHING)
			{
				if (data->mCollisionGrid[tilePos1D] == collisionToCheck[i])
				{
					return true;
				}
			}
		}
	}

	return false;*/
}
bool CollisionEngineSys_IsRectIntersectsCollision(CollisionEngine* data, int x, int y, int width, int height)
{
	int expansionX = ((width / TILE_SIZE) + 1);
	int expansionY = ((height / TILE_SIZE) + 1);

	for (int i = 0; i < 1 + (expansionX * 2); i += 1)
	{
		for (int j = 0; j < 1 + (expansionY * 2); j += 1)
		{
			Point point = CollisionEngineSys_GetCollisionGridPosition(x, y);
			int tileX = point.X - expansionX;
			int tileY = point.Y - expansionY;

			int currentX = tileX + i;
			int currentY = tileY + j;

			if (!CollisionEngineSys_IsPointSafe(data, currentX, currentY))
			{
				continue;
			}

			if (data->mCollisionGrid[GetTilePos1D(currentX, currentY, data)] == OBJECTTYPES_NOTHING)
			{
				continue;
			}

			currentX *= TILE_SIZE;
			currentY *= TILE_SIZE;

			Rectangle rect1 = { x, y, width, height };
			Rectangle rect2 = { currentX, currentY, TILE_SIZE, TILE_SIZE };
			if (Rectangle_Intersects(&rect1, &rect2))
			{
				return true;
			}
		}
	}
	return false;
}
bool CollisionEngineSys_CheckFeetCollision(CollisionEngine* data, Body* body, bool checkLeft, bool checkRight, int offset, int collisionBit)
{
	Rectangle rect = Body_GetRect(body); // Add Vector2s (quadrants of the rectangle)

	Point pnt1 = CollisionEngineSys_GetCollisionGridPosition(Rectangle_Left(&rect) + offset, Rectangle_Bottom(&rect) + 1);
	Point pnt2 = CollisionEngineSys_GetCollisionGridPosition(Rectangle_Right(&rect) - offset, Rectangle_Bottom(&rect) + 1);

	if ((pnt1.X < 0) || (pnt1.Y < 0) || (pnt1.X >= data->mCollisionGridSize.Width) || (pnt1.Y >= data->mCollisionGridSize.Height))
	{
		return false;
	}

	if (collisionBit == OBJECTTYPES_ALL)
	{
		if (checkLeft)
		{
			if (data->mCollisionGrid[GetTilePos1D(pnt1.X, pnt1.Y, data)] != OBJECTTYPES_NOTHING)
			{
				return true;
			}
		}

		if (checkRight)
		{
			if (data->mCollisionGrid[GetTilePos1D(pnt2.X, pnt2.Y, data)] != OBJECTTYPES_NOTHING)
			{
				return true;
			}
		}
	}
	else
	{
		if (checkLeft)
		{
			if (data->mCollisionGrid[GetTilePos1D(pnt1.X, pnt1.Y, data)] == collisionBit)
			{
				return true;
			}
		}

		if (checkRight)
		{
			if (data->mCollisionGrid[GetTilePos1D(pnt2.X, pnt2.Y, data)] == collisionBit)
			{
				return true;
			}
		}
	}
	return false;
}
bool CollisionEngineSys_HasLineOfSight(CollisionEngine* data, float x1, float y1, float x2, float y2, bool respectOneWays)
{
	return CollisionEngineSys_HasLineOfSight2(data, false, NULL, x1, y1, x2, y2, respectOneWays);
}
bool CollisionEngineSys_HasLineOfSight2(CollisionEngine* data, bool draw, SpriteBatch* spriteBatch, float x1, float y1, float x2, float y2, bool respectOneWays)
{
	return false;
	//TODO
	/*
	int directionX = x2 - x1 > 0 ? 1 : -1;
	int directionY = y2 - y1 > 0 ? 1 : -1;

	if (x1 == x2) //Undefined slope, nudge position
	{
		x2 += 1;
	}

	float m = Math_GetSlope(x1, y1, x2, y2);
	float b = Math_GetIntercept(x1, y1, m);
	int distance = (int)(Math_GetLineDistance(x1, y1, x2, y2));
	float seg = (x2 - x1) / distance;
	for (int i = 0; i < distance; i += 1)
	{
		float x = x1 + (i * seg);
		float y = (m * x) + b;

		int collision = GetCollisionBitSafe(data, x, y, 0);
		if (collision == CollisionEngineSys_GetPlatformUp() && respectOneWays)
		{
			if (directionY == 1)
			{
				return false;
			}
		}
		else if (collision == CollisionEngineSys_GetPlatformRight() && respectOneWays)
		{
			if (directionX == -1)
			{
				return false;
			}
		}
		else if (collision == CollisionEngineSys_GetPlatformDown() && respectOneWays)
		{
			if (directionY == -1)
			{
				return false;
			}
		}
		else if (collision == CollisionEngineSys_GetPlatformLeft() && respectOneWays)
		{
			if (directionX == 1)
			{
				return false;
			}
		}
		else
		{
			if (collision != 0)
			{
				if (GameHelper_IsCollisionSolidForLineOfSight(collision))
				{
					return false;
				}
			}
		}

		if (draw)
		{
			OeDrawTool_DrawRectangle(spriteBatch, COLOR_RED, 100, Rectangle((int)x, (int)y, 2, 2), 0, true);
		}
	}

	return true;*/
}
int CollisionEngineSys_GetPlatformDown()
{
	return 0;
	//TODO C99return GameHelper_PLATFORM_DOWN;
}
int CollisionEngineSys_GetPlatformLeft()
{
	return 0;
	//TODO C99return GameHelper_PLATFORM_LEFT;
}
int CollisionEngineSys_GetPlatformRight()
{
	return 0;
	//TODO C99return GameHelper_PLATFORM_RIGHT;
}
int CollisionEngineSys_GetPlatformUp()
{
	return 0;
	//TODO C99return GameHelper_PLATFORM_UP;
}
Vector2 CollisionEngineSys_GetBestPathNode(CollisionEngine* data, bool returnPosition, bool disableDiagonals, float currentX, float currentY, float targetX, float targetY, int hardLimit)
{
	return Vector2_Zero;
	/*
	data.mLastNode = null;
	data.mOpenNodes.Clear();
	data.mClosedNodes.Clear();

	Point pathCurrent = GetCollisionGridPosition(currentX, currentY); //initial
	Point pathTarget = GetCollisionGridPosition(targetX, targetY); //target

	OePathNode initialNode = OePathNode.Obtain(null, pathCurrent.X, pathCurrent.Y, pathTarget.X, pathTarget.Y); //first node
	OePathNode targetNode = null;

	data.mOpenNodes.Add(initialNode); //add to open list

	int counter = 0;
	while (targetNode == null && counter <= hardLimit)
	{
		counter += 1;

		if (data.mOpenNodes.Count == 0) //out of space
		{
			break;
		}

		SortPathNodes(ref data, data.mOpenNodes); //sort by total distance

		OePathNode currentNode = OeListTools.RemoveAt(data.mOpenNodes, 0); //get least distance node

		data.mClosedNodes.Insert(0, currentNode); //add to closed list

		for (int i = 0; i < 8; i += 1) //setup booleans for valid corner checks, corners are not valid with adjacent collision
		{
			_mCornerChecks[i] = false;
		}

		for (int i = 0; i < 8; i += 1) //check 8 way
		{
			int addX = 0;
			int addY = 0;

			switch (i)
			{
			case 0:
				addY = -1;
				break;
			case 1:
				addX = 1;
				break;
			case 2:
				addY = 1;
				break;
			case 3:
				addX = -1;
				break;
			case 4:
				if (!_mCornerChecks[0] || !_mCornerChecks[1] || disableDiagonals)
				{
					continue;
				}
				addX = 1;
				addY = -1;
				break;
			case 5:
				if (!_mCornerChecks[1] || !_mCornerChecks[2] || disableDiagonals)
				{
					continue;
				}
				addX = 1;
				addY = 1;
				break;
			case 6:
				if (!_mCornerChecks[2] || !_mCornerChecks[3] || disableDiagonals)
				{
					continue;
				}
				addX = -1;
				addY = 1;
				break;
			case 7:
				if (!_mCornerChecks[3] || !_mCornerChecks[0] || disableDiagonals)
				{
					continue;
				}
				addX = -1;
				addY = -1;
				break;
			}

			int currentGridX = currentNode.mGridX;
			int currentGridY = currentNode.mGridY;
			int newGridX = currentNode.mGridX + addX;
			int newGridY = currentNode.mGridY + addY;
			int collision = GetCollisionBitSafeGrid(ref data, newGridX, newGridY, 1);
			if (!OeGame.GetHelper().IsCollisionSolidForPathFinding(collision, currentGridX, currentGridY, newGridX, newGridY)) //see if current adjacent square is valid
			{
				_mCornerChecks[i] = true; //if so corner check is good...

				OePathNode newNode = OePathNode.Obtain(currentNode, currentNode.mGridX + addX, currentNode.mGridY + addY, pathTarget.X, pathTarget.Y); //create node

				if (newNode.mGridX == pathTarget.X && newNode.mGridY == pathTarget.Y) //if we are at target stop
				{
					targetNode = newNode;
					data.mClosedNodes.Add(newNode);
					break;
				}

				if (GetIndexOfNode(newNode, data.mClosedNodes) != -1) //if its in the closed nodes for some reason stop
				{
					continue;
				}

				int index = GetIndexOfNode(newNode, data.mOpenNodes); //see if open nodes has this node..
				if (index != -1)
				{
					OePathNode problemNode = data.mOpenNodes[index]; //we have a problem
					if (problemNode.mPathDistance > problemNode.GetPathDistance(currentNode)) //if path distance is greater then set problem node parent to current
					{
						problemNode.mParent = currentNode;
					}
				}
				else
				{
					data.mOpenNodes.Add(newNode); //add otherwise
				}
			}
		}
	}

	Vector2 vec;
	if (targetNode != null)
	{
		OePathNode rootNode = targetNode.GetRoot();
		vec = new Vector2();
		if (returnPosition)
		{
			vec.X = rootNode.GetRealX();
			vec.Y = rootNode.GetRealY();
		}
		else
		{
			vec.X = rootNode.GetDirectionToHereX();
			vec.Y = rootNode.GetDirectionToHereY();
		}
	}
	else //failure
	{
		vec = OeVectors.MaxValue;
	}

#if EDITOR
	if (OeGlobals.DEBUG_SHOW_INGAME_COLLISION)
	{
		DebugDrawNodes(ref data);
	}
#endif

	return vec;
	*/
}
float CollisionEngineSys_GetCurrentDeceleration(float maxDecel, int framesInAir)
{
	float deceleration = framesInAir * GameHelper_GetGravityDeceleration();
	if (deceleration > maxDecel)
	{
		deceleration = maxDecel;
	}
	return deceleration;
}
void CollisionEngineSys_HandleDynamicGravityY(Body* body)
{
	if (body->mTouchedDown)
	{
		body->mFramesInAir = 0;
	}
	else
	{
		body->mFramesInAir += 1;
	}

	if (!body->mTouchedDown)
	{
		Body_Move(body, 0, CollisionEngineSys_GetCurrentDeceleration(body->mMaxDeceleration, body->mFramesInAir));
	}
	else
	{
		Body_Move(body, 0, 1);
	}
}
void CollisionEngineSys_HandleBodiesHousekeepingHelper(CollisionEngine* data, Body* body)
{
	FixedListEightInt_Clear(&body->mLastCollisionsTouched);
	FixedListEightInt_Clear(&body->mContact);
	Body_UpdateLastLogicalPositionToCurrent(body);
	Body_CommitOnNextUpdateMove(body);

	if (!body->mIsStatic)
	{
		if (!body->mIgnoreGravityX && data->mFixedGravity.X != 0)
		{
			Body_Move(body, data->mFixedGravity.X, 0);
		}
		if (!body->mIgnoreGravityY)
		{
			if (!body->mIgnoreFixedGravityY && data->mFixedGravity.Y != 0)
			{
				Body_Move(body, 0, data->mFixedGravity.Y);
			}
			if (!body->mUseOnlyFixedGravity && !_mIsDynamicGravityDisabled)
			{
				CollisionEngineSys_HandleDynamicGravityY(body);
			}
		}
		else
		{
			body->mFramesInAir = 0;
		}
	}

	body->mTouchedUp = false;
	body->mTouchedDown = false;
	body->mTouchedRight = false;
	body->mTouchedLeft = false;
	body->mTouchedBody = false;
	body->mTouchedCollision = false;
	body->mWasPushedByOneWayCollision = false;
	body->mHackTouchedWind = false;

	Body_UpdateLastDirection(body);

	if (body->mMovingPlatformEntityNumber != ENTITY_NOTHING) // Moving platform code. Body is tied to a platform basically.
	{
		Entity movingPlatform = Get_Entity(body->mMovingPlatformEntityNumber);
		if (movingPlatform != ENTITY_NOTHING)
		{
			Body* movingPlatformBody = Get_Body(movingPlatform);
			body->mPhysicsVelocity.X += movingPlatformBody->mPhysicsVelocity.X;
			body->mPhysicsPosition.Y = ((movingPlatformBody->mPhysicsPosition.Y + movingPlatformBody->mPhysicsVelocity.Y) - (movingPlatformBody->mPhysicsHeight / 2) - (body->mPhysicsHeight / 2) - 1);
		}
		body->mMovingPlatformEntityNumber = ENTITY_NOTHING;
	}
}
void CollisionEngineSys_Step(CollisionEngine* data, bool isVertical)
{
	ptrdiff_t bodiesLen = arrlen(_mDynamicBodies);
	for (int i = 0; i < bodiesLen; i += 1) // First move and test high priority bodies....
	{
		Body* body = ComponentPack_GetComponentAtIndex(_mBodyPack, _mDynamicBodies[i]);

		if (body->mIsHighPriorityBody)
		{
			CollisionEngineSys_ApplyBodyVelocity(data, body, isVertical);

			CollisionEngineSys_ResolveWithOtherBodies(data, body, isVertical);
		}
	}

	for (int i = 0; i < bodiesLen; i += 1) // Move for the step, do initial collision check with baked collision.
	{
		Body* body = ComponentPack_GetComponentAtIndex(_mBodyPack, _mDynamicBodies[i]);

		if (!body->mIsHighPriorityBody)
		{
			CollisionEngineSys_ApplyBodyVelocity(data, body, isVertical);
		}

		CollisionEngineSys_ResolveWithBakedCollision(data, body, isVertical);
	}

	for (int i = 0; i < bodiesLen; i += 1) // After collision... now test normal thing rectangles.
	{
		CollisionEngineSys_ResolveWithOtherBodies(data, ComponentPack_GetComponentAtIndex(_mBodyPack, _mDynamicBodies[i]), isVertical);
	}
}
void CollisionEngineSys_ResolveWithBakedCollision(CollisionEngine* data, Body* body, bool vertical)
{
	if (body->mIgnoreAllCollision || body->mIsDisabled || body->mIgnoreBakedCollision || body->mCollideWithBulletsOnly || body->mIgnoreEverythingExceptPlayer || body->mIsStatic
		|| !IsBodyUnderResolveLimit(body))
	{
		return;
	}

	body->mInternalResolverCounter += 1;

	int directionX = vertical ? 0 : body->mLastDirection.X;
	int directionY = vertical ? body->mLastDirection.Y : 0;

	Rectangle rect = Body_GetRect(body);

	int top = Rectangle_Top(&rect);
	int right = Rectangle_Right(&rect);
	int bottom = Rectangle_Bottom(&rect);
	int left = Rectangle_Left(&rect);
	int centerX = Rectangle_Center(&rect).X;
	int centerY = Rectangle_Center(&rect).Y;

	if (CollisionEngineSys_CheckPoint(data, centerX, top, directionX, directionY, body, vertical)) // TOP
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, right, top, directionX, directionY, body, vertical)) // TOP RIGHT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, left, top, directionX, directionY, body, vertical)) // TOP LEFT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, right, centerY, directionX, directionY, body, vertical)) // RIGHT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, left, centerY, directionX, directionY, body, vertical)) // LEFT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, right, bottom, directionX, directionY, body, vertical)) // BOTTOM RIGHT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, left, bottom, directionX, directionY, body, vertical)) // BOTTOM LEFT
	{
		return;
	}
	else if (CollisionEngineSys_CheckPoint(data, centerX, bottom, directionX, directionY, body, vertical)) // BOTTOM
	{
		return;
	}

	return;
}
void CollisionEngineSys_ApplyBodyVelocity(CollisionEngine* data, Body* body, bool isVertical)
{
	body->mInternalResolverCounter = 0;

	if (isVertical)
	{
		if (body->mPhysicsVelocity.Y != 0)
		{
			body->mPhysicsPosition.Y += body->mPhysicsVelocity.Y;
		}
	}
	else
	{
		if (body->mPhysicsVelocity.X != 0)
		{
			body->mPhysicsPosition.X += body->mPhysicsVelocity.X;
		}
	}
}
void CollisionEngineSys_InitRoutine(Entity owner, CollisionEngine* data)
{
	//data.mTempArray =  std_vector<Body>();
	//TODO C99data->mTempNodes = std_vector<std_shared_ptr<OePathNode>>();
	//TODO C99data->mOpenNodes = std_vector<std_shared_ptr<OePathNode>>();
	//TODO C99data->mClosedNodes = std_vector<std_shared_ptr<OePathNode>>();
	//data.mDebugArrayBodiesToDraw =  std_vector<Body>();
	//TODO C99data->mDebugNodeRectangles = std_vector<OeDrawRectangle>();
	//TODO C99data->mDebugManyRectangles = std_vector<OeDrawRectangle>();
	//

	//data.mTempArray.clear();
	//TODO C99data->mTempNodes.clear();
	//TODO C99data->mOpenNodes.clear();
	//TODO C99data->mClosedNodes.clear();
	//data.mDebugArrayBodiesToDraw.clear();
	//TODO C99data->mDebugManyRectangles.clear();
}
void CollisionEngineSys_DrawRoutine(Entity owner, CollisionEngine* data, SpriteBatch* spriteBatch)
{
	//TODO C99spriteBatch->DrawManyRectangle(100, data->mDebugManyRectangles);
}
void CollisionEngineSys_DrawTiles(GameState* scene)
{

}
#if EDITOR
void CollisionEngineSys_DebugGenerateDebugRectangles(CollisionEngine* data)
{
	if (!OeGlobals_DEBUG_SHOW_INGAME_COLLISION || OeGlobals_DEBUG_IS_EDITOR_MODE)
	{
		return;
	}

	for (int i = 0; i < _mBodies.size(); i += 1)
	{
		Body* body = &_mBodyPack->Components[_mBodies[i]];
		data->mDebugManyRectangles.push_back(OeDrawRectangle(body->mTouchedBody ? mDebugColorActive : mDebugColorTouched, Body_GetRect(body)));
	}

	for (int i = 0; i < data->mDebugNodeRectangles.size(); i += 1)
	{
		//mDebugManyRectangles.Add(mDebugNodeRectangles[i]); //Show node info
	}

	//Draw Tiles
	OeLevelData* levelData = Get_LevelData();
	OeComCamera* camera = Get_Camera();
	int x1 = OeComCamera_GetX1(camera);
	int x2 = OeComCamera_GetX2(camera, levelData->GetGridSizeX());
	int y1 = OeComCamera_GetY1(camera);
	int y2 = OeComCamera_GetY2(camera, levelData->GetGridSizeY());
	for (int i = x1; i < x2; i += 1)
	{
		for (int j = y1; j < y2; j += 1)
		{
			int type = data->mCollisionGrid[GetTilePos1D(i, j, data)];
			if (type == ObjectTypes_NOTHING)
			{
				continue;
			}

			Color color = OeUtils_GetCollisionColor(type);

			int rectX = i * TILE_SIZE;
			int rectY = j * TILE_SIZE;
			int rectWidth = TILE_SIZE;
			int rectHeight = TILE_SIZE;

			int halfTile = TILE_SIZE / 2;

			int platformDown = GetPlatformDown();
			if (type == GetPlatformUp() || type == platformDown)
			{
				rectHeight /= 2;
				if (type == platformDown)
				{
					rectY += halfTile;
				}
			}
			int platformRight = GetPlatformDown();
			if (type == GetPlatformLeft() || type == platformRight)
			{
				rectWidth /= 2;
				if (type == platformRight)
				{
					rectX += halfTile;
				}
			}

			data->mDebugManyRectangles.push_back(OeDrawRectangle(color, Rectangle(rectX, rectY, rectWidth, rectHeight)));
		}
	}
	//End Draw Tiles
}
#endif