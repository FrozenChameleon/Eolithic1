//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!

#include "GameStateDataHelper.h"
#include "ComponentType.h"

#include "../../game/components/CrComBossData.h"
#include "../../game/CrComCameraData.h"
#include "../../game/components/CrComChallengeMode.h"
#include "../../game/components/CrComDoomTimer.h"
#include "../../game/components/CrComEnemyKitData.h"
#include "../../game/components/CrComGameOver.h"
#include "../../game/components/CrComIsGameFrozen.h"
#include "../../game/components/CrComIsStarted.h"
#include "../../game/components/CrComPersistence.h"
#include "../../game/components/CrComPostBrightness.h"
#include "../../game/components/CrComResetLevel.h"
#include "../../game/components/CrComSharedData.h"
#include "../../game/components/CrComShowLevelName.h"
#include "../../game/CrEffectBloodData.h"
#include "../../game/CrEffectFloodData.h"
#include "../../game/CrEffectWindData.h"
#include "../../game/CrModePlayMovieData.h"
#include "../../game/CrModePressStartMuteData.h"
#include "../../game/thing/CrThingObjectFlameData.h"
#include "../../game/components/CrTagIsJellyfishShield.h"
#include "../../game/thing/CrThingEnemyAnchorManData.h"
#include "../../game/thing/CrThingEnemyBoneMummyData.h"
#include "../../game/thing/CrThingEnemyCrabData.h"
#include "../../game/thing/CrThingEnemyDeathBallData.h"
#include "../../game/thing/CrThingEnemyFastDogData.h"
#include "../../game/thing/CrThingEnemyFishData.h"
#include "../../game/thing/CrThingEnemyHatMummyData.h"
#include "../../game/thing/CrThingEnemyHookManData.h"
#include "../../game/thing/CrThingEnemyMagicianData.h"
#include "../../game/thing/CrThingEnemyNewBossDemonData.h"
#include "../../game/thing/CrThingEnemyNewBossEyeData.h"
#include "../../game/thing/CrThingEnemyNewBossFinalData.h"
#include "../../game/thing/CrThingEnemyNewBossJellyData.h"
#include "../../game/thing/CrThingEnemyNewBossMonsterData.h"
#include "../../game/thing/CrThingEnemyNewBossMonsterTwoData.h"
#include "../../game/thing/CrThingEnemyNewBossMothData.h"
#include "../../game/thing/CrThingEnemyNewBossShipData.h"
#include "../../game/thing/CrThingEnemyNewBossShipLaserData.h"
#include "../../game/thing/CrThingEnemyNewBossSquidData.h"
#include "../../game/thing/CrThingEnemySinewaveData.h"
#include "../../game/thing/CrThingEnemyStarfishData.h"
#include "../../game/thing/CrThingObjectAnchorData.h"
#include "../../game/thing/CrThingObjectArrowData.h"
#include "../../game/thing/CrThingObjectArrowShooterData.h"
#include "../../game/thing/CrThingObjectBubbleData.h"
#include "../../game/thing/CrThingObjectBubbleSpawnerData.h"
#include "../../game/thing/CrThingObjectCatStatueData.h"
#include "../../game/thing/CrThingObjectCoinData.h"
#include "../../game/thing/CrThingObjectCrumblePlatformData.h"
#include "../../game/thing/CrThingObjectDemonData.h"
#include "../../game/thing/CrThingObjectDemonHeartData.h"
#include "../../game/thing/CrThingObjectEelData.h"
#include "../../game/thing/CrThingObjectEelSpawnerData.h"
#include "../../game/thing/CrThingObjectEventWindowData.h"
#include "../../game/thing/CrThingObjectFallingBlockData.h"
#include "../../game/thing/CrThingObjectFallingSpikeData.h"
#include "../../game/thing/CrThingObjectFlameData.h"
#include "../../game/thing/CrThingObjectFlamethrowerData.h"
#include "../../game/thing/CrThingObjectHookData.h"
#include "../../game/thing/CrThingObjectJellyColumnData.h"
#include "../../game/thing/CrThingObjectKeyButtonData.h"
#include "../../game/thing/CrThingObjectKeyDoorData.h"
#include "../../game/thing/CrThingObjectMagicianBallData.h"
#include "../../game/thing/CrThingObjectMonsterElevatorData.h"
#include "../../game/thing/CrThingObjectMonsterPlatformData.h"
#include "../../game/thing/CrThingObjectMovingPlatformData.h"
#include "../../game/thing/CrThingObjectRuinPlatformData.h"
#include "../../game/thing/CrThingObjectSignData.h"
#include "../../game/thing/CrThingObjectSpikeBallData.h"
#include "../../game/thing/CrThingObjectSpikesData.h"
#include "../../game/thing/CrThingObjectSpinnerData.h"
#include "../../game/thing/CrThingObjectTrainingDummyData.h"
#include "../../game/thing/CrThingObjectWarpData.h"
#include "../../game/thing/CrThingPaintingData.h"
#include "../../game/thing/CrThingParticleSpawnerData.h"
#include "../../game/thing/CrThingPlayerMuteData.h"
#include "../../game/thing/CrThingPlayerMuteMeleeData.h"
#include "../../game/thing/CrThingTriggerBroadcastData.h"
#include "../../game/thing/CrThingTriggerCheckpointData.h"
#include "../../game/thing/CrThingTriggerGravityData.h"
#include "../../game/thing/CrThingTriggerLevelCompleteData.h"
#include "../../game/thing/CrThingTriggerPlaySoundData.h"
#include "../../game/thing/CrThingTriggerSinwaveData.h"
#include "../../game/CrWipeCircleData.h"
#include "../../game/CrWipeLinearData.h"
#include "../collision/Body.h"
#include "../collision/CollisionEngine.h"
#include "../components/BounceData.h"
#include "../components/Camera.h"
#include "../components/CollisionImprintData.h"
#include "../components/DrawActor.h"
#include "../components/FakePosition.h"
#include "../components/FloatyMovementData.h"
#include "../components/FreezeEntityTillOnScreen.h"
#include "../components/GridPosition.h"
#include "../components/IdleCircleData.h"
#include "../components/InitialPosition.h"
#include "../components/LevelDataStub.h"
#include "../components/LevelFrameCounter.h"
#include "../components/Name.h"
#include "../components/Nodes.h"
#include "../components/ParentNumber.h"
#include "../components/PlayerNumber.h"
#include "../components/ShakeCamera.h"
#include "../components/SpecialMcDeathEffect.h"
#include "../components/SpecialMcFinalBossEffect.h"
#include "../components/Step.h"
#include "../components/StepCounter.h"
#include "../components/StepTimer.h"
#include "../components/StringSettings.h"
#include "../render/DrawRenderInfo.h"
#include "../render/DrawStateInfo.h"
#include "../leveldata/ParticleInstance.h"
#include "../components/TagIsActor.h"
#include "../components/TagIsComplete.h"
#include "../components/TagIsDrawDisabled.h"
#include "../components/TagIsInPlay.h"
#include "../components/TagIsPlayer.h"
#include "../components/TagIsUpdateDisabled.h"

#define GSD_INITIAL_SIZE 1

void GameStateDataHelper_InitAllComponentPacks(GameStateData* gsd)
{
    ComponentPack_Init(C_CrComBossData, &gsd->mComponentPacks[C_CrComBossData], sizeof(CrComBossData), 32);
    ComponentPack_Init(C_CrComCameraData, &gsd->mComponentPacks[C_CrComCameraData], sizeof(CrComCameraData), 1);
    ComponentPack_Init(C_CrComChallengeMode, &gsd->mComponentPacks[C_CrComChallengeMode], sizeof(CrComChallengeMode), 1);
    ComponentPack_Init(C_CrComDoomTimer, &gsd->mComponentPacks[C_CrComDoomTimer], sizeof(CrComDoomTimer), 1);
    ComponentPack_Init(C_CrComEnemyKitData, &gsd->mComponentPacks[C_CrComEnemyKitData], sizeof(CrComEnemyKitData), 64);
    ComponentPack_Init(C_CrComGameOver, &gsd->mComponentPacks[C_CrComGameOver], sizeof(CrComGameOver), 1);
    ComponentPack_Init(C_CrComIsGameFrozen, &gsd->mComponentPacks[C_CrComIsGameFrozen], sizeof(CrComIsGameFrozen), 1);
    ComponentPack_Init(C_CrComIsStarted, &gsd->mComponentPacks[C_CrComIsStarted], sizeof(CrComIsStarted), 32);
    ComponentPack_Init(C_CrComPersistence, &gsd->mComponentPacks[C_CrComPersistence], sizeof(CrComPersistence), 256);
    ComponentPack_Init(C_CrComPostBrightness, &gsd->mComponentPacks[C_CrComPostBrightness], sizeof(CrComPostBrightness), 1);
    ComponentPack_Init(C_CrComResetLevel, &gsd->mComponentPacks[C_CrComResetLevel], sizeof(CrComResetLevel), 1);
    ComponentPack_Init(C_CrComSharedData, &gsd->mComponentPacks[C_CrComSharedData], sizeof(CrComSharedData), 1);
    ComponentPack_Init(C_CrComShowLevelName, &gsd->mComponentPacks[C_CrComShowLevelName], sizeof(CrComShowLevelName), 1);
    ComponentPack_Init(C_CrEffectBloodData, &gsd->mComponentPacks[C_CrEffectBloodData], sizeof(CrEffectBloodData), 4096);
    ComponentPack_Init(C_CrEffectFloodData, &gsd->mComponentPacks[C_CrEffectFloodData], sizeof(CrEffectFloodData), 1);
    ComponentPack_Init(C_CrEffectWindData, &gsd->mComponentPacks[C_CrEffectWindData], sizeof(CrEffectWindData), 1);
    ComponentPack_Init(C_CrModePlayMovieData, &gsd->mComponentPacks[C_CrModePlayMovieData], sizeof(CrModePlayMovieData), 1);
    ComponentPack_Init(C_CrModePressStartMuteData, &gsd->mComponentPacks[C_CrModePressStartMuteData], sizeof(CrModePressStartMuteData), 1);
    ComponentPack_Init(C_CrSharedFlameData, &gsd->mComponentPacks[C_CrSharedFlameData], sizeof(CrSharedFlameData), 1);
    ComponentPack_Init(C_CrTagIsJellyfishShield, &gsd->mComponentPacks[C_CrTagIsJellyfishShield], sizeof(CrTagIsJellyfishShield), 16);
    ComponentPack_Init(C_CrThingEnemyAnchorManData, &gsd->mComponentPacks[C_CrThingEnemyAnchorManData], sizeof(CrThingEnemyAnchorManData), 8);
    ComponentPack_Init(C_CrThingEnemyBoneMummyData, &gsd->mComponentPacks[C_CrThingEnemyBoneMummyData], sizeof(CrThingEnemyBoneMummyData), 16);
    ComponentPack_Init(C_CrThingEnemyCrabData, &gsd->mComponentPacks[C_CrThingEnemyCrabData], sizeof(CrThingEnemyCrabData), 8);
    ComponentPack_Init(C_CrThingEnemyDeathBallData, &gsd->mComponentPacks[C_CrThingEnemyDeathBallData], sizeof(CrThingEnemyDeathBallData), 16);
    ComponentPack_Init(C_CrThingEnemyFastDogData, &gsd->mComponentPacks[C_CrThingEnemyFastDogData], sizeof(CrThingEnemyFastDogData), 4);
    ComponentPack_Init(C_CrThingEnemyFishData, &gsd->mComponentPacks[C_CrThingEnemyFishData], sizeof(CrThingEnemyFishData), 4);
    ComponentPack_Init(C_CrThingEnemyHatMummyData, &gsd->mComponentPacks[C_CrThingEnemyHatMummyData], sizeof(CrThingEnemyHatMummyData), 16);
    ComponentPack_Init(C_CrThingEnemyHookManData, &gsd->mComponentPacks[C_CrThingEnemyHookManData], sizeof(CrThingEnemyHookManData), 8);
    ComponentPack_Init(C_CrThingEnemyMagicianData, &gsd->mComponentPacks[C_CrThingEnemyMagicianData], sizeof(CrThingEnemyMagicianData), 64);
    ComponentPack_Init(C_CrThingEnemyNewBossDemonData, &gsd->mComponentPacks[C_CrThingEnemyNewBossDemonData], sizeof(CrThingEnemyNewBossDemonData), 32);
    ComponentPack_Init(C_CrThingEnemyNewBossEyeData, &gsd->mComponentPacks[C_CrThingEnemyNewBossEyeData], sizeof(CrThingEnemyNewBossEyeData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossFinalData, &gsd->mComponentPacks[C_CrThingEnemyNewBossFinalData], sizeof(CrThingEnemyNewBossFinalData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossJellyData, &gsd->mComponentPacks[C_CrThingEnemyNewBossJellyData], sizeof(CrThingEnemyNewBossJellyData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossMonsterData, &gsd->mComponentPacks[C_CrThingEnemyNewBossMonsterData], sizeof(CrThingEnemyNewBossMonsterData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossMonsterTwoData, &gsd->mComponentPacks[C_CrThingEnemyNewBossMonsterTwoData], sizeof(CrThingEnemyNewBossMonsterTwoData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossMothData, &gsd->mComponentPacks[C_CrThingEnemyNewBossMothData], sizeof(CrThingEnemyNewBossMothData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossShipData, &gsd->mComponentPacks[C_CrThingEnemyNewBossShipData], sizeof(CrThingEnemyNewBossShipData), 1);
    ComponentPack_Init(C_CrThingEnemyNewBossShipLaserData, &gsd->mComponentPacks[C_CrThingEnemyNewBossShipLaserData], sizeof(CrThingEnemyNewBossShipLaserData), 4);
    ComponentPack_Init(C_CrThingEnemyNewBossSquidData, &gsd->mComponentPacks[C_CrThingEnemyNewBossSquidData], sizeof(CrThingEnemyNewBossSquidData), 1);
    ComponentPack_Init(C_CrThingEnemySinewaveData, &gsd->mComponentPacks[C_CrThingEnemySinewaveData], sizeof(CrThingEnemySinewaveData), 1);
    ComponentPack_Init(C_CrThingEnemyStarfishData, &gsd->mComponentPacks[C_CrThingEnemyStarfishData], sizeof(CrThingEnemyStarfishData), 64);
    ComponentPack_Init(C_CrThingObjectAnchorData, &gsd->mComponentPacks[C_CrThingObjectAnchorData], sizeof(CrThingObjectAnchorData), 4);
    ComponentPack_Init(C_CrThingObjectArrowData, &gsd->mComponentPacks[C_CrThingObjectArrowData], sizeof(CrThingObjectArrowData), 32);
    ComponentPack_Init(C_CrThingObjectArrowShooterData, &gsd->mComponentPacks[C_CrThingObjectArrowShooterData], sizeof(CrThingObjectArrowShooterData), 64);
    ComponentPack_Init(C_CrThingObjectBubbleData, &gsd->mComponentPacks[C_CrThingObjectBubbleData], sizeof(CrThingObjectBubbleData), 64);
    ComponentPack_Init(C_CrThingObjectBubbleSpawnerData, &gsd->mComponentPacks[C_CrThingObjectBubbleSpawnerData], sizeof(CrThingObjectBubbleSpawnerData), 16);
    ComponentPack_Init(C_CrThingObjectCatStatueData, &gsd->mComponentPacks[C_CrThingObjectCatStatueData], sizeof(CrThingObjectCatStatueData), 1);
    ComponentPack_Init(C_CrThingObjectCoinData, &gsd->mComponentPacks[C_CrThingObjectCoinData], sizeof(CrThingObjectCoinData), 256);
    ComponentPack_Init(C_CrThingObjectCrumblePlatformData, &gsd->mComponentPacks[C_CrThingObjectCrumblePlatformData], sizeof(CrThingObjectCrumblePlatformData), 256);
    ComponentPack_Init(C_CrThingObjectDemonData, &gsd->mComponentPacks[C_CrThingObjectDemonData], sizeof(CrThingObjectDemonData), 1);
    ComponentPack_Init(C_CrThingObjectDemonHeartData, &gsd->mComponentPacks[C_CrThingObjectDemonHeartData], sizeof(CrThingObjectDemonHeartData), 4);
    ComponentPack_Init(C_CrThingObjectEelData, &gsd->mComponentPacks[C_CrThingObjectEelData], sizeof(CrThingObjectEelData), 16);
    ComponentPack_Init(C_CrThingObjectEelSpawnerData, &gsd->mComponentPacks[C_CrThingObjectEelSpawnerData], sizeof(CrThingObjectEelSpawnerData), 8);
    ComponentPack_Init(C_CrThingObjectEventWindowData, &gsd->mComponentPacks[C_CrThingObjectEventWindowData], sizeof(CrThingObjectEventWindowData), 4);
    ComponentPack_Init(C_CrThingObjectFallingBlockData, &gsd->mComponentPacks[C_CrThingObjectFallingBlockData], sizeof(CrThingObjectFallingBlockData), 32);
    ComponentPack_Init(C_CrThingObjectFallingSpikeData, &gsd->mComponentPacks[C_CrThingObjectFallingSpikeData], sizeof(CrThingObjectFallingSpikeData), 256);
    ComponentPack_Init(C_CrThingObjectFlameData, &gsd->mComponentPacks[C_CrThingObjectFlameData], sizeof(CrThingObjectFlameData), 128);
    ComponentPack_Init(C_CrThingObjectFlamethrowerData, &gsd->mComponentPacks[C_CrThingObjectFlamethrowerData], sizeof(CrThingObjectFlamethrowerData), 128);
    ComponentPack_Init(C_CrThingObjectHookData, &gsd->mComponentPacks[C_CrThingObjectHookData], sizeof(CrThingObjectHookData), 4);
    ComponentPack_Init(C_CrThingObjectJellyColumnData, &gsd->mComponentPacks[C_CrThingObjectJellyColumnData], sizeof(CrThingObjectJellyColumnData), 1);
    ComponentPack_Init(C_CrThingObjectKeyButtonData, &gsd->mComponentPacks[C_CrThingObjectKeyButtonData], sizeof(CrThingObjectKeyButtonData), 128);
    ComponentPack_Init(C_CrThingObjectKeyDoorData, &gsd->mComponentPacks[C_CrThingObjectKeyDoorData], sizeof(CrThingObjectKeyDoorData), 16);
    ComponentPack_Init(C_CrThingObjectMagicianBallData, &gsd->mComponentPacks[C_CrThingObjectMagicianBallData], sizeof(CrThingObjectMagicianBallData), 64);
    ComponentPack_Init(C_CrThingObjectMonsterElevatorData, &gsd->mComponentPacks[C_CrThingObjectMonsterElevatorData], sizeof(CrThingObjectMonsterElevatorData), 1);
    ComponentPack_Init(C_CrThingObjectMonsterPlatformData, &gsd->mComponentPacks[C_CrThingObjectMonsterPlatformData], sizeof(CrThingObjectMonsterPlatformData), 8);
    ComponentPack_Init(C_CrThingObjectMovingPlatformData, &gsd->mComponentPacks[C_CrThingObjectMovingPlatformData], sizeof(CrThingObjectMovingPlatformData), 32);
    ComponentPack_Init(C_CrThingObjectRuinPlatformData, &gsd->mComponentPacks[C_CrThingObjectRuinPlatformData], sizeof(CrThingObjectRuinPlatformData), 16);
    ComponentPack_Init(C_CrThingObjectSignData, &gsd->mComponentPacks[C_CrThingObjectSignData], sizeof(CrThingObjectSignData), 2);
    ComponentPack_Init(C_CrThingObjectSpikeBallData, &gsd->mComponentPacks[C_CrThingObjectSpikeBallData], sizeof(CrThingObjectSpikeBallData), 64);
    ComponentPack_Init(C_CrThingObjectSpikesData, &gsd->mComponentPacks[C_CrThingObjectSpikesData], sizeof(CrThingObjectSpikesData), 1024);
    ComponentPack_Init(C_CrThingObjectSpinnerData, &gsd->mComponentPacks[C_CrThingObjectSpinnerData], sizeof(CrThingObjectSpinnerData), 128);
    ComponentPack_Init(C_CrThingObjectTrainingDummyData, &gsd->mComponentPacks[C_CrThingObjectTrainingDummyData], sizeof(CrThingObjectTrainingDummyData), 2);
    ComponentPack_Init(C_CrThingObjectWarpData, &gsd->mComponentPacks[C_CrThingObjectWarpData], sizeof(CrThingObjectWarpData), 16);
    ComponentPack_Init(C_CrThingPaintingData, &gsd->mComponentPacks[C_CrThingPaintingData], sizeof(CrThingPaintingData), 16);
    ComponentPack_Init(C_CrThingParticleSpawnerData, &gsd->mComponentPacks[C_CrThingParticleSpawnerData], sizeof(CrThingParticleSpawnerData), 64);
    ComponentPack_Init(C_CrThingPlayerMuteData, &gsd->mComponentPacks[C_CrThingPlayerMuteData], sizeof(CrThingPlayerMuteData), 1);
    ComponentPack_Init(C_CrThingPlayerMuteMeleeData, &gsd->mComponentPacks[C_CrThingPlayerMuteMeleeData], sizeof(CrThingPlayerMuteMeleeData), 1);
    ComponentPack_Init(C_CrThingTriggerBroadcastData, &gsd->mComponentPacks[C_CrThingTriggerBroadcastData], sizeof(CrThingTriggerBroadcastData), 32);
    ComponentPack_Init(C_CrThingTriggerCheckpointData, &gsd->mComponentPacks[C_CrThingTriggerCheckpointData], sizeof(CrThingTriggerCheckpointData), 8);
    ComponentPack_Init(C_CrThingTriggerGravityData, &gsd->mComponentPacks[C_CrThingTriggerGravityData], sizeof(CrThingTriggerGravityData), 32);
    ComponentPack_Init(C_CrThingTriggerLevelCompleteData, &gsd->mComponentPacks[C_CrThingTriggerLevelCompleteData], sizeof(CrThingTriggerLevelCompleteData), 8);
    ComponentPack_Init(C_CrThingTriggerPlaySoundData, &gsd->mComponentPacks[C_CrThingTriggerPlaySoundData], sizeof(CrThingTriggerPlaySoundData), 1);
    ComponentPack_Init(C_CrThingTriggerSinwaveData, &gsd->mComponentPacks[C_CrThingTriggerSinwaveData], sizeof(CrThingTriggerSinwaveData), 4);
    ComponentPack_Init(C_CrWipeCircleData, &gsd->mComponentPacks[C_CrWipeCircleData], sizeof(CrWipeCircleData), 1);
    ComponentPack_Init(C_CrWipeLinearData, &gsd->mComponentPacks[C_CrWipeLinearData], sizeof(CrWipeLinearData), 2);
    ComponentPack_Init(C_Body, &gsd->mComponentPacks[C_Body], sizeof(Body), 1024);
    ComponentPack_Init(C_CollisionEngine, &gsd->mComponentPacks[C_CollisionEngine], sizeof(CollisionEngine), 1);
    ComponentPack_Init(C_BounceData, &gsd->mComponentPacks[C_BounceData], sizeof(BounceData), 1);
    ComponentPack_Init(C_Camera, &gsd->mComponentPacks[C_Camera], sizeof(Camera), 1);
    ComponentPack_Init(C_CollisionImprintData, &gsd->mComponentPacks[C_CollisionImprintData], sizeof(CollisionImprintData), 512);
    ComponentPack_Init(C_DrawActor, &gsd->mComponentPacks[C_DrawActor], sizeof(DrawActor), 256);
    ComponentPack_Init(C_FakePosition, &gsd->mComponentPacks[C_FakePosition], sizeof(FakePosition), 1024);
    ComponentPack_Init(C_FloatyMovementData, &gsd->mComponentPacks[C_FloatyMovementData], sizeof(FloatyMovementData), 4);
    ComponentPack_Init(C_FreezeEntityTillOnScreen, &gsd->mComponentPacks[C_FreezeEntityTillOnScreen], sizeof(FreezeEntityTillOnScreen), 256);
    ComponentPack_Init(C_GridPosition, &gsd->mComponentPacks[C_GridPosition], sizeof(GridPosition), 1024);
    ComponentPack_Init(C_IdleCircleData, &gsd->mComponentPacks[C_IdleCircleData], sizeof(IdleCircleData), 4);
    ComponentPack_Init(C_InitialPosition, &gsd->mComponentPacks[C_InitialPosition], sizeof(InitialPosition), 1024);
    ComponentPack_Init(C_LevelDataStub, &gsd->mComponentPacks[C_LevelDataStub], sizeof(LevelDataStub), 1);
    ComponentPack_Init(C_LevelFrameCounter, &gsd->mComponentPacks[C_LevelFrameCounter], sizeof(LevelFrameCounter), 1);
    ComponentPack_Init(C_Name, &gsd->mComponentPacks[C_Name], sizeof(Name), 1024);
    ComponentPack_Init(C_Nodes, &gsd->mComponentPacks[C_Nodes], sizeof(Nodes), 1024);
    ComponentPack_Init(C_ParentNumber, &gsd->mComponentPacks[C_ParentNumber], sizeof(ParentNumber), 1024);
    ComponentPack_Init(C_PlayerNumber, &gsd->mComponentPacks[C_PlayerNumber], sizeof(PlayerNumber), 1);
    ComponentPack_Init(C_ShakeCamera, &gsd->mComponentPacks[C_ShakeCamera], sizeof(ShakeCamera), 8);
    ComponentPack_Init(C_SpecialMcDeathEffect, &gsd->mComponentPacks[C_SpecialMcDeathEffect], sizeof(SpecialMcDeathEffect), 1);
    ComponentPack_Init(C_SpecialMcFinalBossEffect, &gsd->mComponentPacks[C_SpecialMcFinalBossEffect], sizeof(SpecialMcFinalBossEffect), 1);
    ComponentPack_Init(C_Step, &gsd->mComponentPacks[C_Step], sizeof(Step), 32);
    ComponentPack_Init(C_StepCounter, &gsd->mComponentPacks[C_StepCounter], sizeof(StepCounter), 32);
    ComponentPack_Init(C_StepTimer, &gsd->mComponentPacks[C_StepTimer], sizeof(StepTimer), 32);
    ComponentPack_Init(C_StringSettings, &gsd->mComponentPacks[C_StringSettings], sizeof(StringSettings), 1024);
    ComponentPack_Init(C_DrawRenderInfo, &gsd->mComponentPacks[C_DrawRenderInfo], sizeof(DrawRenderInfo), 2048);
    ComponentPack_Init(C_DrawStateInfo, &gsd->mComponentPacks[C_DrawStateInfo], sizeof(DrawStateInfo), 256);
    ComponentPack_Init(C_ParticleInstance, &gsd->mComponentPacks[C_ParticleInstance], sizeof(ParticleInstance), 4096);
    ComponentPack_Init(C_TagIsActor, &gsd->mComponentPacks[C_TagIsActor], sizeof(TagIsActor), 1024);
    ComponentPack_Init(C_TagIsComplete, &gsd->mComponentPacks[C_TagIsComplete], sizeof(TagIsComplete), 64);
    ComponentPack_Init(C_TagIsDrawDisabled, &gsd->mComponentPacks[C_TagIsDrawDisabled], sizeof(TagIsDrawDisabled), 128);
    ComponentPack_Init(C_TagIsInPlay, &gsd->mComponentPacks[C_TagIsInPlay], sizeof(TagIsInPlay), 1024);
    ComponentPack_Init(C_TagIsPlayer, &gsd->mComponentPacks[C_TagIsPlayer], sizeof(TagIsPlayer), 1);
    ComponentPack_Init(C_TagIsUpdateDisabled, &gsd->mComponentPacks[C_TagIsUpdateDisabled], sizeof(TagIsUpdateDisabled), 256);
}
