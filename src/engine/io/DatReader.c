/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "DatReader.h"

#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "File.h"
#include "../utils/Exception.h"
#include "limits.h"

static uint64_t _mRefs;

typedef struct DatReader
{
	int _mCurrent;
	int _mCount;
	bool _mHasInit;
	MString* _mPath;
	DatInfo* arr_dat_info;
	MString** arr_last_strings;
	BufferReader* _mReader;
} DatReader;

static DatInfo* GetCurrentDatInfo(DatReader* dr)
{
	DatInfo* info = &dr->arr_dat_info[dr->_mCurrent];
	return info;
}

FixedByteBuffer* DatReader_GetMemoryStream(DatReader* dr, int64_t length)
{
	return NULL;
}

bool DatReader_HasInit(const DatReader* dr)
{
	return dr->_mHasInit;
}
bool DatReader_HasNext(const DatReader* dr)
{
	return (dr->_mCurrent < dr->_mCount);
}
MString* DatReader_NextFilePath(DatReader* dr)
{
	for (int32_t i = 0; i < arrlen(dr->arr_last_strings); i += 1)
	{
		MString_Dispose(dr->arr_last_strings[i]);
	}
	arrsetlen(dr->arr_last_strings, 0);

	int32_t length = BufferReader_ReadI32(dr->_mReader);
	for (int32_t i = 0; i < length; i += 1)
	{
		MString* temp = BufferReader_ReadStringToMString(dr->_mReader);
		arrput(dr->arr_last_strings, temp);
	}

	MString* strToReturn = MString_Create("");
	int64_t len = arrlen(dr->arr_last_strings);
	for (int i = 0; i < len; i += 1)
	{
		MString_AddAssignString(&strToReturn, dr->arr_last_strings[i]->str);
		if (i < (len - 1))
		{
			File_AppendPathSeparator(&strToReturn);
		}
	}

	DatInfo* currentInfo = GetCurrentDatInfo(dr);
	currentInfo->mPath = MString_Create(strToReturn->str);
	return strToReturn;
}
BufferReader* DatReader_NextStream(DatReader* dr, bool doNotReturnStream)
{
	int64_t length = BufferReader_ReadI64(dr->_mReader);
	int64_t currentActualPosition = BufferReader_Position(dr->_mReader);
	DatInfo* currentInfo = GetCurrentDatInfo(dr);
	currentInfo->mLength = length;
	currentInfo->mPosition = currentActualPosition;
	if (doNotReturnStream)
	{
		BufferReader_Seek(dr->_mReader, length, BUFFER_READER_SEEK_FROM_CURRENT);
		dr->_mCurrent += 1;
		return NULL;
	}
	else
	{
		if ((length < 0) || (length > INT_MAX))
		{
			Exception_Run("Invalid file size in dat!", false);
		}
		FixedByteBuffer* buffer = BufferReader_ReadBytes(dr->_mReader, length);
		BufferReader* bufferToReturn = BufferReader_Create(buffer);
		/*if (OeGlobals.IsDebugFileMode())
		{
			if (OeCvars.GetAsBool(OeCvars.ENGINE_DECOMPRESS_DATS))
			{
				Decompress(length, stream);
				stream.Position = 0;
			}
		}*/
		dr->_mCurrent += 1;
		return bufferToReturn;
	}
}
//std::shared_ptr<OeStream> DatReader_Find(const std::string& path);
DatReader* DatReader_Create(const char* path)
{
	_mRefs += 1;

	DatReader* dr = Utils_calloc(1, sizeof(DatReader));

	dr->_mReader = BufferReader_CreateFromPath(path);
	dr->_mPath = MString_Create(path);
	
	int version = BufferReader_ReadI32(dr->_mReader);
	dr->_mCount = BufferReader_ReadI32(dr->_mReader);
	for (int i = 0; i < dr->_mCount; i += 1)
	{
		DatInfo temp = { 0 };
		arrput(dr->arr_dat_info, temp);
	}

	dr->_mHasInit = true;

	return dr;
}
void DatReader_Dispose(DatReader* dr)
{
	_mRefs -= 1;

	BufferReader_Dispose(dr->_mReader, false);

	Utils_free(dr);
}