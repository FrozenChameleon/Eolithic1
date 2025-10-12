#include "GameSaveManager.h"

#include "../core/GameHelper.h"
#include "../core/Game.h"
#include "../utils/Logger.h"
#include "../utils/Cvars.h"
#include "../utils/Utils.h"
#include "../service/Service.h"
#include "../globals/Globals.h"
#include "../../GlobalDefs.h"

#define SAVE_FILE_NAME "mcdcsave.bin"
#define CONTAINER_DISPLAY_NAME "GameSave"
#define CONTAINER_NAME "GameSaveContainer"

static void* _mData;
static bool _mWasDataJustLoaded;
static bool _mHasLoaded;

//private
/*
static std_shared_ptr<OeFixedByteBuffer> CreateBufferFromSaveData()
{
	std_shared_ptr<OeIniWriter> writer = OeIniWriter_CreateNewOeIniWriter();
	_mData.Write(writer);
	return writer->ToFixedByteBuffer();
}
*/
void* GameSaveManager_GetCurrentSaveData()
{
	return &_mData;
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
	//TODO C99
	/*
	Utils_JustSaved();

	if (OeGlobals_IsSavingUserDataDisabled())
	{
		return;
	}

	Service_SaveBuffer(true, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, SAVE_FILE_NAME, CreateBufferFromSaveData());

	Logger_LogInformation("Save file saved to save0.bin");
	*/
}
void GameSaveManager_Load()
{
	//TODO C99
	/*
	_mWasDataJustLoaded = false;

	if (OeGlobals_IsLoadingUserDataDisabled())
	{
		_mHasLoaded = true;
		OeLogger_LogInformation("Loading disabled");
		return;
	}

	OeBufferRequest request = OeService_AskToRetrieveBuffer(true, CONTAINER_DISPLAY_NAME, CONTAINER_NAME, SAVE_FILE_NAME);
	if (request.mIsBufferReady)
	{
		_mHasLoaded = true;
		if (request.mBuffer == nullptr)
		{
			OeLogger_LogInformation("Nothing to load");
			return;
		}
		else
		{
			ResetSaveData();
			std_shared_ptr<OeIniReader> reader = OeIniReader_CreateNewOeIniReader(true, OeStream_CreateNewStream(request.mBuffer));
			_mData.Read(reader);
			_mWasDataJustLoaded = true;
			OeLogger_LogInformation("Read save data");
			return;
		}
	}
	*/
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
