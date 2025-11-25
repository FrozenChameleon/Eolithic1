#include "BmFont.h"

//TODO C99 #include "OeFontMap.h"
//TODO C99 #include "../resources/ResourceManagers.h"
#include "../render/Texture.h"
//TODO C99 #include "../render/OeRenderTtFont.h"
#include "../render/Renderer.h"
#include "../resources/BmFontManager.h"
#include "../../third_party/stb_ds.h"
#include "../resources/TextureFontManager.h"

#define FONT_EXTENSION ".fnt"
//TODO C99 static const std_vector<std_string> FONT_DIRECTORY = { OeFile_Combine("data", "fonts") };

int BmFont_GetBaseHeight(BmFont* bmf)
{
	return bmf->_mFontData.mCommon.Base;
}
int BmFont_GetLineHeight(BmFont* bmf)
{
	return bmf->_mFontData.mCommon.LineHeight;
}
const char* BmFont_GetFontName(BmFont* bmf)
{
	return MString_GetText(bmf->_mFontName);
}
Texture* BmFont_GetFontTexture(BmFont* bmf)
{
	BmFont_UpdateFontTexture(bmf);

	return bmf->_mFontTexture;
}
bool BmFont_UpdateFontTexture(BmFont* bmf)
{
	if (bmf->_mFontTexture == NULL)
	{
		Texture* tex = TextureFontManager_GetResourceData(MString_GetText(bmf->_mFontName));
		if (tex == NULL)
		{
			bmf->_mFontTexture = NULL;
			return true;
		}
		bmf->_mFontTexture = tex;
	}
	return false;
}
void BmFont_Init(BmFont* bmf, BufferReader* br, const char* fontName)
{
	Utils_memset(bmf, 0, sizeof(BmFont));

	BmFontData_Init(&bmf->_mFontData, br);
	MString_Assign(&bmf->_mFontName, fontName);

	BmFontDataChar* chars = bmf->_mFontData.mChars;
	int64_t charsLen = arrlen(chars);
	for (int i = 0; i < charsLen; i += 1)
	{
		BmFontDataChar fontChar = chars[i];
		hmput(bmf->hm_font_char_map, fontChar.ID, fontChar);
	}
}
BmFont* BmFont_GetBmFont(BmFont* bmf, const char* font)
{
	return BmFontManager_GetResourceData(font);
}
/*const OeFontMapData* BmFont_GetReplacement()
{
	return OeFontMap_GetReplacement(_mFontName);
}*/

//#if !DISABLE_TT_FONT
//TODO C99 
// OeTTFont* BmFont_GetTTFont(const std_string& font)
//{
//	return OeResourceManagers_TTFontManager.GetResourceData(font);
//}
//#endif

Rectangle BmFont_GetBounds(BmFont* bmf, const char* text, bool doNotReplaceFont)
{
	//#if !DISABLE_TT_FONT
	//TODO C99
	/*
	const OeFontMapData* replacement = GetReplacement();
	if (replacement != nullptr && !doNotReplaceFont)
	{
		if (replacement->mIsBitmap)
		{
			return OeRenderer_RenderBmFont(false, GetBmFont(replacement->mFontName), text, Color_White, Vector2_Zero);
		}
		else
		{
			return OeRenderTtFont_GetBounds(replacement, text);
		}
	}*/
	//#endif
	return Renderer_RenderBmFont(false, bmf, text, COLOR_WHITE, Vector2_Zero);
}


/*
const char* BmFont_GetFontExtension()
{
	return FONT_EXTENSION;
}
const std_vector<std_string>& BmFont_GetFontDirectories()
{
	return FONT_DIRECTORY;
}
*/
BmFont* BmFont_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	BmFont* bmf = Utils_malloc(sizeof(BmFont));
	BmFont_Init(bmf, br, filenameWithoutExtension);
	return bmf;
}

void BmFont_Dispose(BmFont* bmf)
{

}