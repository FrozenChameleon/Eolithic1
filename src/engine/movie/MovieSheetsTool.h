#pragma once

#include <string>
#include "../render/OeSheet.h"

namespace OeMovieSheetsTool
{
	void Init();
	OeSheet* GetSheet(const std::string& path);
};

