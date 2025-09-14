#include "TextureOffset.h"

#include "../utils/Utils.h"

TextureOffset* TextureOffset_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	TextureOffset* textureOffset = Utils_malloc(sizeof(TextureOffset));
	Utils_memset(textureOffset, 0, sizeof(TextureOffset));

	/*
	std::vector<std::string> strTextures = {};
	OeFile::ReadFileToStrings(stream, strTextures);

	for (int i = 0; i < strTextures.size(); i++)
	{
		std::vector<std::string> strSplits = {};
		OeUtils::StringSplit(' ', strTextures[i], strSplits);
		if (strSplits.size() != 6)
		{
			continue;
		}

		Rectangle rect;
		rect.X = OeUtils::ParseInt(strSplits[2]);
		rect.Y = OeUtils::ParseInt(strSplits[3]);
		rect.Width = OeUtils::ParseInt(strSplits[4]);
		rect.Height = OeUtils::ParseInt(strSplits[5]);

		OeTextureOffsetInfo info = OeTextureOffsetInfo();
		info.mRect = rect;
		info.mPath = path;
		info.mVirtualName = strSplits[0];

		textureOffset->_mOffsets.push_back(info);
	}
	*/

	return textureOffset;
}
void TextureOffset_Dispose(TextureOffset* to)
{

}
