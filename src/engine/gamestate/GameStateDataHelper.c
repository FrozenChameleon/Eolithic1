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
#include "../../game/thing/CrThingObjectFlameData.h"
#include "../../game/components/CrTagIsJellyfishShield.h"
#include "../../game/thing/CrThingEnemyAnchorManData.h"
#include "../../game/thing/CrThingEnemyCrabData.h"
#include "../../game/thing/CrThingEnemyDeathBallData.h"
#include "../../game/thing/CrThingEnemyFastDogData.h"
#include "../../game/thing/CrThingEnemyFishData.h"
#include "../../game/thing/CrThingEnemyHatMummyData.h"
#include "../../game/thing/CrThingEnemyHookManData.h"
#include "../../game/thing/CrThingEnemyMagicianData.h"
#include "../../game/thing/CrThingEnemyNewBossDemonData.h"
#include "../../game/thing/CrThingEnemyNewBossFinalData.h"
#include "../../game/thing/CrThingEnemyNewBossJellyData.h"
#include "../../game/thing/CrThingEnemyNewBossMonsterData.h"
#include "../../game/thing/CrThingEnemyNewBossMonsterTwoData.h"
#include "../../game/thing/CrThingEnemyNewBossMothData.h"
#include "../../game/thing/CrThingEnemyNewBossShipData.h"
#include "../../game/thing/CrThingEnemyNewBossShipLaserData.h"
#include "../../game/thing/CrThingEnemyNewBossSquidData.h"
#include "../../game/thing/CrThingEnemySinewaveData.h"
#include "../../game/thing/CrThingObjectAnchorData.h"
#include "../../game/thing/CrThingObjectArrowData.h"
#include "../../game/thing/CrThingObjectBubbleData.h"
#include "../../game/thing/CrThingObjectBubbleSpawnerData.h"
#include "../../game/thing/CrThingObjectCatStatueData.h"
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
#include "../../game/thing/CrThingTriggerPlaySoundData.h"
#include "../../game/thing/CrThingTriggerSinwaveData.h"
#include "../../game/CrWipeCircleData.h"
#include "../../game/CrWipeLinearData.h"
#include "../collision/Body.h"
#include "../components/BounceData.h"
#include "../components/Camera.h"
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
#include "../components/ParentNumber.h"
#include "../components/PlayerNumber.h"
#include "../components/ShakeCamera.h"
#include "../components/SpecialMcDeathEffect.h"
#include "../components/SpecialMcFinalBossEffect.h"
#include "../components/Step.h"
#include "../components/StepCounter.h"
#include "../components/StepTimer.h"
#include "../components/StringSettings.h"
#include "../leveldata/ParticleInstance.h"
#include "../components/TagIsActor.h"
#include "../components/TagIsComplete.h"
#include "../components/TagIsDrawDisabled.h"
#include "../components/TagIsInPlay.h"
#include "../components/TagIsPlayer.h"
#include "../components/TagIsUpdateDisabled.h"
#include "../components/SceneCameraData.h"
#include "../components/TagIsBlockingLineOfSight.h"
#include "../components/MoveGetter.h"
#include "../components/NodeMovingKit.h"
#include "../components/HitFlashKit.h"
#include "../components/MirrorEffect.h"
#include "../components/Move.h"
#include "../components/TagIsIgnoringTransitions.h"
#include "../components/TagIsExtraBody.h"
#include "../components/TagIsEnemy.h"
#include "../components/StunFrames.h"
#include "../math/Random32.h"
#include "../components/IntTag.h"

#define GSD_INITIAL_SIZE 4

void GameStateDataHelper_InitAllComponentPacks(GameStateData* gsd)
{
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComBossData], sizeof(CrComBossData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComCameraData], sizeof(CrComCameraData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComChallengeMode], sizeof(CrComChallengeMode), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComDoomTimer], sizeof(CrComDoomTimer), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComEnemyKitData], sizeof(CrComEnemyKitData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComGameOver], sizeof(CrComGameOver), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComIsGameFrozen], sizeof(CrComIsGameFrozen), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComIsStarted], sizeof(CrComIsStarted), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComPersistence], sizeof(CrComPersistence), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComPostBrightness], sizeof(CrComPostBrightness), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComResetLevel], sizeof(CrComResetLevel), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComSharedData], sizeof(CrComSharedData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrComShowLevelName], sizeof(CrComShowLevelName), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrEffectBloodData], sizeof(CrEffectBloodData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrEffectFloodData], sizeof(CrEffectFloodData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrEffectWindData], sizeof(CrEffectWindData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrModePlayMovieData], sizeof(CrModePlayMovieData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrSharedFlameData], sizeof(CrSharedFlameData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrTagIsJellyfishShield], sizeof(CrTagIsJellyfishShield), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyAnchorManData], sizeof(CrThingEnemyAnchorManData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyCrabData], sizeof(CrThingEnemyCrabData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyDeathBallData], sizeof(CrThingEnemyDeathBallData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyFastDogData], sizeof(CrThingEnemyFastDogData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyFishData], sizeof(CrThingEnemyFishData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyHatMummyData], sizeof(CrThingEnemyHatMummyData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyHookManData], sizeof(CrThingEnemyHookManData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyMagicianData], sizeof(CrThingEnemyMagicianData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossDemonData], sizeof(CrThingEnemyNewBossDemonData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossFinalData], sizeof(CrThingEnemyNewBossFinalData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossJellyData], sizeof(CrThingEnemyNewBossJellyData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossMonsterData], sizeof(CrThingEnemyNewBossMonsterData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossMonsterTwoData], sizeof(CrThingEnemyNewBossMonsterTwoData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossMothData], sizeof(CrThingEnemyNewBossMothData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossShipData], sizeof(CrThingEnemyNewBossShipData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossShipLaserData], sizeof(CrThingEnemyNewBossShipLaserData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemyNewBossSquidData], sizeof(CrThingEnemyNewBossSquidData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingEnemySinewaveData], sizeof(CrThingEnemySinewaveData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectAnchorData], sizeof(CrThingObjectAnchorData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectArrowData], sizeof(CrThingObjectArrowData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectBubbleData], sizeof(CrThingObjectBubbleData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectBubbleSpawnerData], sizeof(CrThingObjectBubbleSpawnerData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectCatStatueData], sizeof(CrThingObjectCatStatueData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectCrumblePlatformData], sizeof(CrThingObjectCrumblePlatformData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectDemonData], sizeof(CrThingObjectDemonData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectDemonHeartData], sizeof(CrThingObjectDemonHeartData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectEelData], sizeof(CrThingObjectEelData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectEelSpawnerData], sizeof(CrThingObjectEelSpawnerData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectEventWindowData], sizeof(CrThingObjectEventWindowData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectFallingBlockData], sizeof(CrThingObjectFallingBlockData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectFallingSpikeData], sizeof(CrThingObjectFallingSpikeData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectFlameData], sizeof(CrThingObjectFlameData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectFlamethrowerData], sizeof(CrThingObjectFlamethrowerData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectHookData], sizeof(CrThingObjectHookData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectJellyColumnData], sizeof(CrThingObjectJellyColumnData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectKeyButtonData], sizeof(CrThingObjectKeyButtonData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectKeyDoorData], sizeof(CrThingObjectKeyDoorData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectMagicianBallData], sizeof(CrThingObjectMagicianBallData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectMonsterElevatorData], sizeof(CrThingObjectMonsterElevatorData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectMonsterPlatformData], sizeof(CrThingObjectMonsterPlatformData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectMovingPlatformData], sizeof(CrThingObjectMovingPlatformData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectRuinPlatformData], sizeof(CrThingObjectRuinPlatformData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectSignData], sizeof(CrThingObjectSignData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectSpikeBallData], sizeof(CrThingObjectSpikeBallData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectSpikesData], sizeof(CrThingObjectSpikesData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectSpinnerData], sizeof(CrThingObjectSpinnerData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectTrainingDummyData], sizeof(CrThingObjectTrainingDummyData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingObjectWarpData], sizeof(CrThingObjectWarpData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingPaintingData], sizeof(CrThingPaintingData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingParticleSpawnerData], sizeof(CrThingParticleSpawnerData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingPlayerMuteData], sizeof(CrThingPlayerMuteData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingPlayerMuteMeleeData], sizeof(CrThingPlayerMuteMeleeData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingTriggerBroadcastData], sizeof(CrThingTriggerBroadcastData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingTriggerCheckpointData], sizeof(CrThingTriggerCheckpointData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingTriggerPlaySoundData], sizeof(CrThingTriggerPlaySoundData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrThingTriggerSinwaveData], sizeof(CrThingTriggerSinwaveData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrWipeCircleData], sizeof(CrWipeCircleData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_CrWipeLinearData], sizeof(CrWipeLinearData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Body], sizeof(Body), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_BounceData], sizeof(BounceData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Camera], sizeof(Camera), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_DrawActor], sizeof(DrawActor), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_FakePosition], sizeof(FakePosition), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_FloatyMovementData], sizeof(FloatyMovementData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_FreezeEntityTillOnScreen], sizeof(FreezeEntityTillOnScreen), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_GridPosition], sizeof(GridPosition), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_IdleCircleData], sizeof(IdleCircleData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_InitialPosition], sizeof(InitialPosition), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_LevelDataStub], sizeof(LevelDataStub), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_LevelFrameCounter], sizeof(LevelFrameCounter), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Name], sizeof(Name), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_ParentNumber], sizeof(ParentNumber), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_PlayerNumber], sizeof(PlayerNumber), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_ShakeCamera], sizeof(ShakeCamera), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_SpecialMcDeathEffect], sizeof(SpecialMcDeathEffect), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_SpecialMcFinalBossEffect], sizeof(SpecialMcFinalBossEffect), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Step], sizeof(Step), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_StepCounter], sizeof(StepCounter), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_StepTimer], sizeof(StepTimer), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_StringSettings], sizeof(StringSettings), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_ParticleInstance], sizeof(ParticleInstance), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsActor], sizeof(TagIsActor), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsComplete], sizeof(TagIsComplete), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsDrawDisabled], sizeof(TagIsDrawDisabled), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsInPlay], sizeof(TagIsInPlay), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsPlayer], sizeof(TagIsPlayer), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsUpdateDisabled], sizeof(TagIsUpdateDisabled), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_SceneCameraData], sizeof(SceneCameraData), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsBlockingLineOfSight], sizeof(TagIsBlockingLineOfSight), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_MoveGetter], sizeof(MoveGetter), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_NodeMovingKit], sizeof(NodeMovingKit), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_HitFlashKit], sizeof(HitFlashKit), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_MirrorEffect], sizeof(MirrorEffect), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Move], sizeof(Move), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsIgnoringTransitions], sizeof(TagIsIgnoringTransitions), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsExtraBody], sizeof(TagIsExtraBody), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_TagIsEnemy], sizeof(TagIsEnemy), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_StunFrames], sizeof(StunFrames), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_Random32], sizeof(Random32), GSD_INITIAL_SIZE);
    ComponentPack_Init(&gsd->mComponentPacks[C_IntTag], sizeof(IntTag), GSD_INITIAL_SIZE);
}
