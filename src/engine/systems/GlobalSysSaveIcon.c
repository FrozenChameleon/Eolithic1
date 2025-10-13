#include "GlobalSysSaveIcon.h"

#include "../render/Animation.h"
#include "../render/SpriteBatch.h"
#include "../utils/Utils.h"
#include "../utils/Cvars.h"
#include "../render/Color.h"
#include "../render/Sheet.h"

static Animation _mSaveIcon;

static bool HasInit()
{
	return true;
	//TODO C99;
	//return (_mSaveIcon.GetSheets().size() != 0);
}
static void InitAnimation()
{
	//TODO C99
	/*
	std::string spriteSheet = OeCvars::Get(OeCvars::ENGINE_SAVE_ICON);
	int flipTimer = OeCvars::GetAsInt(OeCvars::ENGINE_SAVE_ICON_FLIP_SPEED);
	OeAnimation::Init(&_mSaveIcon, spriteSheet, flipTimer);*/
}

static void Update()
{
	if (!HasInit())
	{
		InitAnimation();
		return;
	}

	//TODO C99
	/*if (Utils_CheckSave(true))
	{
		Animation_Update(&_mSaveIcon);
	}
	else
	{
		Animation_ResetAnimation(&_mSaveIcon);
	}*/
}
static void DrawHud(SpriteBatch* spriteBatch)
{
	if (!HasInit())
	{
		InitAnimation();
		return;
	}

	//TODO C99
	/*if (Utils_CheckSave(false))
	{
		int scale = OeCvars::GetAsInt(OeCvars::ENGINE_SAVE_ICON_SCALE);
		int offsetX = OeCvars::GetAsInt(OeCvars::ENGINE_SAVE_ICON_OFFSET_X);
		int offsetY = OeCvars::GetAsInt(OeCvars::ENGINE_SAVE_ICON_OFFSET_Y);
		OeSheet* sheet = OeAnimation::GetCurrentSheet(&_mSaveIcon);
		Rectangle rect = sheet->mRectangle;
		rect.Width *= scale;
		rect.Height *= scale;
		OeSheet::Draw(sheet, spriteBatch, OeColors::WHITE, 100, false, false,
			nullptr, Vector2(OeCvars::GetAsInt(OeCvars::ENGINE_INTERNAL_RENDER_WIDTH) - rect.Width + offsetX, offsetY),
			Vector2(scale, scale), 0, false, false, Vector2::Zero);
	}*/
}

System* GlobalSysSaveIcon_CreateSystem()
{

}
