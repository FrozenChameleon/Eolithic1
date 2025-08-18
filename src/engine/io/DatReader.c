/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "DatReader.h"

#include "../utils/Utils.h"
#include "../third_party/stb_ds.h"
#include "File.h"

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
FixedChar260 DatReader_NextFilePath(DatReader* dr)
{
	int32_t length = BufferReader_ReadI32(dr->_mReader);
	arrfree(dr->_mDynamicLastStrings);
	dr->_mDynamicLastStrings = NULL;
	for (int32_t i = 0; i < length; i += 1)
	{
		FixedChar260 charTemp;
		BufferReader_ReadString(dr->_mReader, charTemp.mValue, FIXED_CHAR_260_LENGTH);
		arrput(dr->_mDynamicLastStrings, charTemp);
	}
	FixedChar260 temp = { 0 };
	int32_t len = arrlen(dr->_mDynamicLastStrings);
	for (int i = 0; i < len; i += 1)
	{
		if (i == 0)
		{
			Utils_strlcpy(temp.mValue, dr->_mDynamicLastStrings[i].mValue, FIXED_CHAR_260_LENGTH);
		}
		else
		{
			Utils_strlcat(temp.mValue, dr->_mDynamicLastStrings[i].mValue, FIXED_CHAR_260_LENGTH);
		}
		if (i < (len - 1))
		{
			File_AppendPathSeparator(temp.mValue, FIXED_CHAR_260_LENGTH);
		}
	}
	dr->_mDynamicDatInfo[dr->_mCurrent].mPath = temp;
	return temp;
}
BufferReader* DatReader_NextStream(DatReader* dr, bool doNotReturnStream)
{

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