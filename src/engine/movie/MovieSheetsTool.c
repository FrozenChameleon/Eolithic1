#include "OeMovieSheetsTool.h"

#include <string>
#include <unordered_map>
#include "../render/OeSheet.h"
#include "../resources/OeResourceManagers.h"

static std::unordered_map<std::string, OeSheet*> _mSheets = {};
static std::vector<OeSheet*> _mSheetList = {};

static bool _mHasInit;

void OeMovieSheetsTool::Init()
{
	if (_mHasInit)
	{
		return;
	}

	const std::vector<std::string>& listOfSheetNames = OeResourceManagers::MovieTextureManager.GetKeyList();
	for (int i = 0; i < listOfSheetNames.size(); i++)
	{
		const std::string& sheetName = listOfSheetNames[i];
		OeResource<OeTexture*>* resource = OeResourceManagers::MovieTextureManager.GetResource(sheetName);
		OeSheet* sheet = new OeSheet(resource);
		sheet->mSheetName = sheetName;
		sheet->mUnderlyingTextureName = sheetName;
		_mSheetList.push_back(sheet);
		_mSheets[sheet->mSheetName] = sheet;
	}

	_mHasInit = true;
}
OeSheet* OeMovieSheetsTool::GetSheet(const std::string& path)
{
	Init();

	if (_mSheets.count(path))
	{
		return _mSheets[path];
	}
	else
	{
		return OeSheet::GetDefaultSheet();
	}
}
