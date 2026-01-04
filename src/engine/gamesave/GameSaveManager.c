#include "GameSaveManager.h"

#include "../core/GameHelper.h"
#include "../core/Game.h"
#include "../utils/Logger.h"
#include "../utils/Cvars.h"
#include "../utils/Utils.h"
#include "../service/Service.h"
#include "../globals/Globals.h"
#include "../../GlobalDefs.h"
#include "../io/FixedByteBuffer.h"
#include "../io/DynamicByteBuffer.h"
#include "../io/BufferReader.h"

#define SAVE_FILE_NAME "mcdcsave.bin"
#define CONTAINER_DISPLAY_NAME "GameSave"
#define CONTAINER_NAME "GameSaveContainer"

static void* _mData;
static bool _mWasDataJustLoaded;
static bool _mHasLoaded;
static bool _mHasInit;

void GameSaveManager_Init()
{
	if (_mHasInit)
	{
		return;
	}

	_mData = GameHelper_CreateGameSaveData();

	_mHasInit = true;
}

bool GameSaveManager_HasInit()
{
	return _mHasInit;
}

static FixedByteBuffer* CreateBufferFromSaveData()
{
	DynamicByteBuffer* dbb = DynamicByteBuffer_Create();
	GameHelper_WriteGameSaveData(_mData, dbb);
	FixedByteBuffer* fbb = DynamicByteBuffer_ConvertToFixedByteBufferAndDispose(dbb);
	return fbb;
}

void* GameSaveManager_GetCurrentSaveData()
{
	return _mData;
}
void GameSaveManager_ResetSaveData()
{
	if (_mData != NULL)
	{
		Utils_free(_mData);
		_mData = NULL;
	}

	_mData = GameHelper_CreateGameSaveData();
}
void GameSaveManager_Save()
{
	if (Globals_IsSavingUserDataDisabled())
	{
		return;
	}

	Utils_JustSaved();

	FixedByteBuffer* fbb = CreateBufferFromSaveData();
	Service_SaveBuffer(true, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, SAVE_FILE_NAME, fbb);
	FixedByteBuffer_Dispose(fbb);

	Logger_LogInformation("Save file saved to save0.bin");
}
void GameSaveManager_Load()
{
	_mWasDataJustLoaded = false;

	if (Globals_IsLoadingUserDataDisabled())
	{
		_mHasLoaded = true;
		Logger_LogInformation("Loading game save data is disabled");
		return;
	}

	BufferRequest request = Service_AskToRetrieveBuffer(true, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, SAVE_FILE_NAME);
	if (request.mIsBufferReady)
	{
		_mHasLoaded = true;
		if (request.mBuffer == NULL)
		{
			Logger_LogInformation("No game save data to load...");
			return;
		}
		else
		{
			GameSaveManager_ResetSaveData();
			BufferReader* reader = BufferReader_Create(request.mBuffer);
			GameHelper_ReadGameSaveData(_mData, reader);
			BufferReader_Dispose(reader, false);
			_mWasDataJustLoaded = true;
			Logger_LogInformation("Loaded game save data successfully!");
			return;
		}
	}
}
bool GameSaveManager_HasLoaded()
{
	return _mHasLoaded;
}
/*
void GameSaveManager_WriteAllForRecording(std_shared_ptr<OeIniWriter> writer)
{
	writer->WriteInt32(0); //Was currentSaveSlot, now unused.
	_mData.Write(writer);
}
void GameSaveManager_ResetSaveDataAndReadAllForRecording(std_shared_ptr<OeIniReader> reader)
{
	ResetSaveData();
	reader->ReadInt32(); //Was currentSaveSlot, now unused.
	_mData.Read(reader);
}
*/
void GameSaveManager_ResetWasSaveDataJustLoaded()
{
	_mWasDataJustLoaded = false;
}
bool GameSaveManager_WasSaveDataJustLoaded()
{
	return _mWasDataJustLoaded;
}
