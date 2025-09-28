#include "OeState.h"

/*
static bool _mHasInit = false;

const static std::string STR_DEFAULT = "DEFAULT";
static std::vector<std::string> DRAW_STATE_ARRAY;
static std::unordered_map<std::string, int> DRAW_STATE_MAP;

const std::vector<std::string>& OeState::GetDrawStateArray()
{
	return DRAW_STATE_ARRAY;
}
std::unordered_map<std::string, int>& OeState::GetDrawStateMap()
{
	return DRAW_STATE_MAP;
}
const std::string& OeState::GetDefaultState()
{
	return STR_DEFAULT;
}
void OeState::Init()
{
	if (_mHasInit)
	{
		return;
	}

	DRAW_STATE_MAP[STR_DEFAULT] = DEFAULT;
	DRAW_STATE_MAP["HEAD"] = HEAD;
	DRAW_STATE_MAP["SHOOT"] = SHOOT;
	DRAW_STATE_MAP["NEW"] = NEW;
	DRAW_STATE_MAP["TAGS"] = TAGS;
	DRAW_STATE_MAP["WHEELS"] = WHEELS;
	DRAW_STATE_MAP["WHEELFX"] = WHEELFX;
	DRAW_STATE_MAP["MUZZLE"] = MUZZLE;
	DRAW_STATE_MAP["STEP1"] = STEP1;
	DRAW_STATE_MAP["STEP2"] = STEP2;
	DRAW_STATE_MAP["STEP3"] = STEP3;
	DRAW_STATE_MAP["STEP4"] = STEP4;
	DRAW_STATE_MAP["STEP5"] = STEP5;
	DRAW_STATE_MAP["STEP6"] = STEP6;
	DRAW_STATE_MAP["STEP7"] = STEP7;
	DRAW_STATE_MAP["STEP8"] = STEP8;
	DRAW_STATE_MAP["STEP9"] = STEP9;

	DRAW_STATE_ARRAY = std::vector<std::string>();
	for (auto it = DRAW_STATE_MAP.begin(); it != DRAW_STATE_MAP.end(); it++)
	{
		std::string stateString = it->first;
		DRAW_STATE_ARRAY.push_back(stateString);
	}
	//Note here that the intent is for these to be sorted alphabetically.

	_mHasInit = true;
}*/