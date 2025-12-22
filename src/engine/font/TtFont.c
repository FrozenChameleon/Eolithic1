#include "TtFont.h"

#include "../render/RenderTtFont.h"
#include "../io/File.h"
#include "../utils/Utils.h"
#include "../io/BufferReader.h"

/*
static const std::string TTFONT_EXTENSION = ".ttf";
static const std::vector<std::string> TTFONT_DIRECTORIES = { OeFile::Combine("data", "ttfonts") };

const std::string& OeTTFont::GetExtension()
{
	return TTFONT_EXTENSION;
}
const std::vector<std::string>& OeTTFont::GetDirectories()
{
	return TTFONT_DIRECTORIES;
}
OeTTFont* OeTTFont::FromStream(OeTTFont* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream)
{

}
*/

TTFont* TTFont_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	RenderTtFont_Create(filenameWithoutExtension, BufferReader_GetBuffer(br));
	TTFont* ttf = Utils_calloc(1, sizeof(TTFont));
	return ttf;
}

void TTFont_Dispose(TTFont* ttf)
{
	Utils_free(ttf);
}
