#include "GameState.h"

#include "GameStateManager.h"
#include "ReplayDataManager.h"
#include "DebugRewindTester.h"
#include "../utils/Utils.h"
#include "../utils/Cvars.h"
#include "../core/GameHelper.h"

void GameState_SaveComponentSizesHelper(bool isBinary)
{

}
void GameState_ClearReplayCache(GameState* gs)
{
	gs->_mCurrentReplayFrame = 0;
	if (!gs->_mReplayDataManager._mIsActive)
	{
		ReplayDataManager_Clear(&gs->_mReplayDataManager);
	}
	DebugRewindTester_Reset();
}

void GameState_Ctor(GameState* gs, const char* name, bool disableRewinding)
{
	Utils_memset(gs, 0, sizeof(GameState));

	if (Cvars_GetAsBool(CVARS_ENGINE_DISABLE_REPLAYS))
	{
		disableRewinding = true;
	}

	gs->_mCurrentReplayFrame = 0;
	gs->_mDisableRewindingPermanently = disableRewinding;
	gs->_mName = name;
	GameStateData_Ctor(&gs->_mData);
	GameStateData_Ctor(&gs->_mForGameState);
	if (!disableRewinding)
	{
		gs->_mReplayDataManager._mIsActive = true;
	}
#if EDITOR
	_mHasSavedDebugSaveState = false;
	_mDebugSaveState = OeGameHelper::CreateGameStateData(name);
	_mIsRewindLooping = false;
#endif
}

GameStateData* GameState_GetGameStateData(GameState* gs)
{
	return &gs->_mData;
}
const char* GameState_GetName(GameState* gs)
{
	return gs->_mName;
}
void GameState_SaveComponentSizes(GameState* gs)
{
	GameState_SaveComponentSizesHelper(true);
	GameState_SaveComponentSizesHelper(false);
}

ParticleInstance* GameState_GetParticleInstance(GameState* gs, const char* name, float x, float y)
{
	return NULL;
	//TODO C99
	/*
	Particle* particleData = OeResourceManagers::ParticleManager.GetResourceData(name);
	if (particleData == nullptr)
	{
		OeLogger::LogInformation("Particle missing " + name);
		return &OeParticleInstance::Dummy;
	}

	OeComponentPack<OeParticleInstance>* pack = OeFunc::Get_ComponentPack<OeParticleInstance>();
	pack->SetMaximumCapacity(GLOBAL_DEF_PARTICLE_LIMIT);
	if (pack->Length() >= GLOBAL_DEF_PARTICLE_LIMIT)
	{
		return pack->GetDummy();
	}
	OeEntity particleEntity = OeFunc::Get_DummyEntityUniqueToPack(pack, "Particle Instances");
	OeParticleInstance* particleInstance = pack->Set(particleEntity, true);
	OeParticleInstanceSys::Setup(particleInstance, name, particleData, x, y);
	return particleInstance;
	*/
}

void GameState_RemoveEntity(GameState* gs, Entity entity)
{
	GameStateData_RemoveEntity(&gs->_mData, entity);
}

Entity* GameState_GetEntitiesInPlay(GameState* gs)
{
	return NULL;
	//TODO C99
	/*
	_mEntitiesInPlay.clear();
	_mData->FillListWithEntitiesInPlay(_mEntitiesInPlay);
	return _mEntitiesInPlay;
	*/
}
void GameState_Do_SendBroadcast(GameState* gs, int type, int packet1, int packet2, int packet3)
{
	//TODO C99
	/*
	for (int i = 0; i < OeGameStateManager::StateSystems.size(); i++)
	{
		OeGameStateManager::StateSystems[i]->ReceiveBroadcast(type, packet1, packet2, packet3);
	}
	*/
}
Entity GameState_BuildNewEntity(GameState* gs)
{
	return GameStateData_BuildNewEntity(&gs->_mData);
}

void GameState_Update(GameState* gs)
{
	if (gs->_mClearReplayCacheNextFrame)
	{
		GameState_ClearReplayCache(gs);
		gs->_mClearReplayCacheNextFrame = false;
	}

	if (gs->_mDisableRewindingPermanently || gs->_mDisableRewindTemporarily)
	{
		GameHelper_UpdateStateSystems();
	}
	else
	{
		//TODO C99 bool isRewindingThisFrame = OeGameHelper::HandleRewindBeforeUpdatingStateSystems();
		bool isRewindingThisFrame = false;
		if (!isRewindingThisFrame)
		{
			GameHelper_UpdateStateSystems();
			gs->_mCurrentReplayFrame += 1;
			if (gs->_mCurrentReplayFrame == 0) //Overflow check
			{
				GameState_ClearReplayCache(gs);
			}
		}
	}
}
void GameState_SetDisableRewindTemporarily(GameState* gs, bool value)
{
	gs->_mDisableRewindTemporarily = value;
}
void GameState_SetGameStateToNotRewinding(GameState* gs)
{
	gs->_mIsRewinding = false;
}
bool GameState_IsRewinding(GameState* gs)
{
	return gs->_mIsRewinding;
}
bool GameState_Rewind(GameState* gs)
{
	gs->_mIsRewinding = true;

	if (gs->_mCurrentReplayFrame == 0)
	{
		return false;
	}

	uint64_t lowestFrame = ReplayDataManager_GetLowestReplayFrame(&gs->_mReplayDataManager);
	if (gs->_mCurrentReplayFrame <= lowestFrame)
	{
		return false;
	}

	gs->_mCurrentReplayFrame -= 1;

	ReplayDataManager_RewindToSnapshot(&gs->_mReplayDataManager, gs->_mCurrentReplayFrame, &gs->_mData);

	GameStateManager_UpdateLastRenderPosition();

	return true;
}
void GameState_GiveReplayInput(GameState* gs, const GameStateInputData* inputData)
{
	if (!gs->_mReplayDataManager._mIsActive)
	{
		return;
	}

	ReplayDataManager_GiveReplayInput(&gs->_mReplayDataManager, gs->_mCurrentReplayFrame, inputData);
}
const GameStateInputData* GameState_GetReplayInput(GameState* gs)
{
	return ReplayDataManager_GetReplayInput(&gs->_mReplayDataManager);
}
void GameState_ClearReplayCacheNextFrame(GameState* gs)
{
	gs->_mClearReplayCacheNextFrame = true;
}
void GameState_Draw(GameState* gs, SpriteBatch* spriteBatch)
{
	//TODO C99 OeGameHelper::DrawStateSystems(spriteBatch);
}
void GameState_DrawHud(GameState* gs, SpriteBatch* spriteBatch)
{
	//TODO C99 	OeGameHelper::DrawHudStateSystems(spriteBatch);
}
void GameState_DrawDebugHud(GameState* gs, SpriteBatch* spriteBatch)
{
	//TODO C99 OeGameHelper::DrawDebugHudStateSystems(spriteBatch);
}

void GameState_Load(GameState* gs, const char* levelDataToLoad)
{
#if EDITOR
	_mIsRewindLooping = false;
#endif

	GameState_ClearReplayCache(gs);

	GameStateData_Reset(&gs->_mData);

	GameHelper_InitGameState(levelDataToLoad);
}
Entity GameState_GetEntityInPlay(GameState* gs, int entityNumber)
{
	return GameStateData_GetEntityInPlay(&gs->_mData, entityNumber);
}
void GameState_UpdateReplayFrame(GameState* gs)
{
	ReplayDataManager_Snapshot(&gs->_mReplayDataManager, gs->_mCurrentReplayFrame, &gs->_mData);
}
bool GameState_HasCreatedForGameSaveState(GameState* gs)
{
	return gs->_mHasSavedForGameSaveState;
}
void GameState_ClearForGameSaveState(GameState* gs)
{
	gs->_mHasSavedForGameSaveState = false;
}
void GameState_CreateForGameSaveState(GameState* gs)
{
	gs->_mHasSavedForGameSaveState = true;
	GameStateData_CopyTo(&gs->_mData, &gs->_mForGameState);
}
void GameState_UseForGameSaveState(GameState* gs)
{
	if (!gs->_mHasSavedForGameSaveState)
	{
		return;
	}

	GameStateData_CopyTo(&gs->_mForGameState, &gs->_mData);
}
int GameState_GetRemainingRewindTime(GameState* gs)
{
	return (int)(gs->_mCurrentReplayFrame - ReplayDataManager_GetLowestReplayFrame(&gs->_mReplayDataManager));
}
bool GameState_IsThereAnyRewindTimeRemaining(GameState* gs)
{
	return GameState_GetRemainingRewindTime(gs) > 0;
}
float GameState_GetPercentageOfRemainingRewindTime(GameState* gs)
{
	int current = GameState_GetRemainingRewindTime(gs);
	int max = REPLAY_DATA_MANAGER_REPLAY_BUFFER_SIZE;
	return ((float)current / max);
}
ComponentPack* GameState_GetComponentPack(GameState* gs, ComponentType ctype)
{
	return GameStateData_GetComponentPack(&gs->_mData, ctype);
}
bool GameState_HasComponent(GameState* gs, ComponentType ctype, Entity entity)
{
	return GameStateData_HasComponent(&gs->_mData, ctype, entity);
}
void* GameState_GetComponent(GameState* gs, ComponentType ctype, Entity entity) //Just another name for Set
{
	return GameStateData_Set(&gs->_mData, ctype, entity);
}
void* GameState_Set(GameState* gs, ComponentType ctype, Entity entity)
{
	return GameStateData_Set(&gs->_mData, ctype, entity);
}
void* GameState_SetAndInit(GameState* gs, ComponentType ctype, Entity entity)
{
	return GameStateData_SetAndInit(&gs->_mData, ctype, entity);
}
void GameState_Init(GameState* gs, ComponentType ctype, Entity entity)
{
	GameStateData_Init(&gs->_mData, ctype, entity);
}
void GameState_Unset(GameState* gs, ComponentType ctype, Entity entity)
{
	GameStateData_Unset(&gs->_mData, ctype, entity);
}
void GameState_UnsetAll(GameState* gs, ComponentType ctype)
{
	GameStateData_UnsetAll(&gs->_mData, ctype);
}
bool GameState_IsAnyEntityInPack(GameState* gs, ComponentType ctype)
{
	return GameStateData_IsAnyEntityInPack(&gs->_mData, ctype);
}
void* GameState_GetFirstSetComponent(GameState* gs, ComponentType ctype)
{
	return GameStateData_GetFirstSetComponent(&gs->_mData, ctype);
}
Entity GameState_GetFirstSetEntity(GameState* gs, ComponentType ctype)
{
	return GameStateData_GetFirstSetEntity(&gs->_mData, ctype);
}
void* GameState_TryGetComponent(GameState* gs, ComponentType ctype, Entity entity, bool* wasSuccessful)
{
	return GameStateData_TryGetComponent(&gs->_mData, ctype, entity, wasSuccessful);
}
void* GameState_TryGetFirstSetComponent(GameState* gs, ComponentType ctype, bool* wasSuccessful)
{
	return GameStateData_TryGetFirstSetComponent(&gs->_mData, ctype, wasSuccessful);
}