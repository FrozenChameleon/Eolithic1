#pragma once

#include "../utils/Macros.h"
//#include "../io/OeFixedByteBuffer.h"
//#include "../../game/CrGameSaveData.h"

//class OeIniWriter;
//class OeIniReader;

void* GameSaveManager_GetCurrentSaveData();
void GameSaveManager_ResetSaveData();
void GameSaveManager_Save();
void GameSaveManager_Load();
bool GameSaveManager_HasLoaded();
//TODO C99 void GameSaveManager_WriteAllForRecording(std::shared_ptr<OeIniWriter> writer);
//TODO C99 void GameSaveManager_ResetSaveDataAndReadAllForRecording(std::shared_ptr<OeIniReader> reader);
void GameSaveManager_ResetWasSaveDataJustLoaded();
bool GameSaveManager_WasSaveDataJustLoaded();
