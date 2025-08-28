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
	FixedChar260 _mPath;
	DatInfo* _mDynamicDatInfo;
	FixedChar260* _mDynamicLastStrings;
	BufferReader* _mReader;
} DatReader;

static DatInfo* GetCurrentDatInfo(DatReader* dr)
{
	DatInfo* info = &dr->_mDynamicDatInfo[dr->_mCurrent];
	return info;
}

FixedByteBuffer* DatReader_GetMemoryStream(DatReader* dr, int64_t length)
{

}

bool DatReader_HasInit(const DatReader* dr)
{
	return dr->_mHasInit;
}
bool DatReader_HasNext(const DatReader* dr)
{
	return (dr->_mCurrent < dr->_mCount);
}
void DatReader_NextFilePath(DatReader* dr, FixedChar260* dst)
{
	int32_t length = BufferReader_ReadI32(dr->_mReader);
	arrsetlen(dr->_mDynamicLastStrings, 0);
	for (int32_t i = 0; i < length; i += 1)
	{
		FixedChar260 temp = { 0 };
		BufferReader_ReadString(dr->_mReader, temp.mValue, FIXED_CHAR_260_LENGTH);
		arrput(dr->_mDynamicLastStrings, temp);
	}

	memset(dst, 0, sizeof(FixedChar260));
	int32_t len = arrlen(dr->_mDynamicLastStrings);
	for (int i = 0; i < len; i += 1)
	{
		FixedChar260* currentString = &dr->_mDynamicLastStrings[i].mValue;
		if (i == 0)
		{
			Utils_strlcpy(dst, currentString, FIXED_CHAR_260_LENGTH);
		}
		else
		{
			Utils_strlcat(dst, currentString, FIXED_CHAR_260_LENGTH);
		}
		if (i < (len - 1))
		{
			File_AppendPathSeparator(dst);
		}
	}

	DatInfo* currentInfo = GetCurrentDatInfo(dr);
	Utils_strlcpy(&currentInfo->mPath, dst, FIXED_CHAR_260_LENGTH);
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

	DatReader* dr = Utils_malloc(sizeof(DatReader));
	Utils_memset(dr, 0, sizeof(DatReader));

	dr->_mReader = BufferReader_CreateFromPath(path);
	Utils_strlcpy(dr->_mPath.mValue, path, FIXED_CHAR_260_LENGTH);
	
	int version = BufferReader_ReadI32(dr->_mReader);
	dr->_mCount = BufferReader_ReadI32(dr->_mReader);
	for (int i = 0; i < dr->_mCount; i += 1)
	{
		DatInfo temp = { 0 };
		arrput(dr->_mDynamicDatInfo, temp);
	}

	int32_t len = arrlen(dr->_mDynamicDatInfo);

	dr->_mHasInit = true;

	return dr;
}
void DatReader_Dispose(DatReader* dr)
{
	_mRefs -= 1;

	BufferReader_Dispose(dr->_mReader, false);

	Utils_free(dr);
}