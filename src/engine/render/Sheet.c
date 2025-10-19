/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

#include "Sheet.h"

#include "../utils/Macros.h"
#include "../utils/Utils.h"
#include "../../third_party/stb_ds.h"
#include "../resources/TextureManager.h"
#include "../resources/TextureOffsetManager.h"
#include "../globals/Globals.h"

#define DEBUG_SHEET_NAME "DEBUG_ERROR_777"

static Sheet* _mDummy;
static struct { const char* key; Sheet* value; } *_mStringHashMap;
static Sheet** _mDynamicSheetList;
static bool _mHasInit;

static void Init()
{
	if (_mHasInit)
	{
		return;
	}

	sh_new_arena(_mStringHashMap);

	_mHasInit = true;
}
static void InitSheet(Sheet* sheet)
{
	Utils_memset(sheet, 0, sizeof(Sheet));

	sheet->mSheetName = EE_STR_NOTHING;
	sheet->mUnderlyingTextureName = EE_STR_NOTHING;
	sheet->mRectangle = Rectangle_Empty;
	sheet->mTextureResource = NULL;
}

Sheet* Sheet_GetDefaultSheet()
{
	Init();

	return _mDummy;
}
Sheet* Sheet_GetSheet(const char* name)
{
	Init();

	return shget(_mStringHashMap, name);
}
void Sheet_BuildSheets()
{
	arrsetlen(_mDynamicSheetList, 0);
	shfree(_mStringHashMap);

	Init();

	int textureManLen = TextureManager_Length();
	for (int i = 0; i < textureManLen; i += 1)
	{
		Resource* resource = TextureManager_GetResourceByIndex(i);
		if (resource->mData == NULL)
		{
			continue;
		}

		Sheet* sheet = Utils_malloc(sizeof(Sheet));
		InitSheet(sheet);
		sheet->mUnderlyingTextureName = resource->mFileNameWithoutExtension;
		sheet->mSheetName = sheet->mUnderlyingTextureName;
		sheet->mTextureResource = resource->mData;
		sheet->mRectangle = ((Texture*)sheet->mTextureResource)->mBounds;
		arrput(_mDynamicSheetList, sheet);
		shput(_mStringHashMap, resource->mPath, sheet);
	}

	if (!Globals_IsDebugFileMode() || GLOBALS_DEBUG_ENGINE_FORCE_LOAD_DATS)
	{
		int textureOffsetLen = TextureOffsetManager_Length();
		for (int i = 0; i < textureOffsetLen; i += 1)
		{
			Resource* resource = TextureOffsetManager_GetResourceByIndex(i);
			if (resource->mData == NULL)
			{
				continue;
			}

			TextureOffset* texOffset = (TextureOffset*)resource->mData;
			int infoLen = arrlen(texOffset->_mDynamicOffsets);
			for (int i = 0; i < infoLen; i += 1)
			{
				TextureOffsetInfo* info = &texOffset->_mDynamicOffsets[i];
				Sheet* sheet = Utils_malloc(sizeof(Sheet));
				InitSheet(sheet);
				sheet->mSheetName = info->mVirtualName;
				sheet->mUnderlyingTextureName = info->mFilenameWithoutExtension;
				sheet->mRectangle = info->mRect;
				sheet->mTextureResource = TextureManager_GetResource(info->mFilenameWithoutExtension);
				arrput(_mDynamicSheetList, sheet);
				shput(_mStringHashMap, sheet->mSheetName, sheet);
			}

		}
	}
}
bool Sheet_HasSheet(const char* name)
{
	Init();

	ptrdiff_t index = shgeti(_mStringHashMap, name);
	if (index < 0)
	{
		return false;
	}
	return true;
}
IStringArray* Sheet_CreateListOfSheetNames()
{
	IStringArray* sa = IStringArray_Create();
	ptrdiff_t len = shlen(_mStringHashMap);
	for (int i = 0; i < len; i += 1)
	{
		const char* sheetName = _mStringHashMap[i].value->mSheetName;
		IStringArray_Add(sa, sheetName);
	}
	return sa;
}
