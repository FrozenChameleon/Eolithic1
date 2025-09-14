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
	sheet->mRectangle = Rectangle_Empty();
	sheet->mTextureResource = NULL;
}

Sheet* Sheet_GetDefaultSheet()
{
	Init();

	return _mDummy;
}
Sheet* Sheet_GetSheet()
{
	Init();

	return _mDummy;
}
void Sheet_BuildSheets()
{
	arrsetlen(_mDynamicSheetList, 0);
	shfree(_mStringHashMap);

	Init();

	int len = TextureManager_Length();
	for (int i = 0; i < len; i += 1)
	{
		Resource* resource = TextureManager_GetResourceByIndex(i);
		if (resource->mData == NULL)
		{
			continue;
		}

		Sheet* sheet = Utils_malloc(sizeof(Sheet));
		InitSheet(sheet);
		sheet->mTextureResource = resource->mData;
		sheet->mSheetName = &resource->mPath.mValue;
		arrput(_mDynamicSheetList, sheet);
		shput(_mStringHashMap, &resource->mPath, sheet);
	}

	/*
	if (!OeGlobals::IsDebugFileMode() || OeGlobals::DEBUG_ENGINE_FORCE_LOAD_DATS)
	{
		const std::vector<std::string>& listOfTextureOffsetNames = OeResourceManagers::TextureOffsetManager.GetKeyList();
		for (int i = 0; i < listOfTextureOffsetNames.size(); i += 1)
		{
			const std::vector<OeTextureOffsetInfo>& offsets = OeResourceManagers::TextureOffsetManager.GetResourceData(listOfTextureOffsetNames[i])->GetTextureOffsets();
			for (int j = 0; j < offsets.size(); j += 1)
			{
				const OeTextureOffsetInfo* info = &offsets[j];
				OeSheet* sheet = new OeSheet(info->mPath, info->mVirtualName, info->mRect);
				_mSheetList.push_back(sheet);
				_mSheets[sheet->mSheetName] = sheet;
			}
		}
	}
	*/
}
bool Sheet_HasSheet(const char* name)
{
	Init();

	return shgeti(_mStringHashMap, name);
}