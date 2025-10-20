#include "TextureOffset.h"

#include "../../third_party/stb_ds.h"
#include "../utils/Utils.h"
#include "../io/File.h"
#include "../utils/IStrings.h"

TextureOffset* TextureOffset_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	TextureOffset* textureOffset = Utils_malloc(sizeof(TextureOffset));
	Utils_memset(textureOffset, 0, sizeof(TextureOffset));

	IStringArray* lines = File_ReadAllToStrings(br);
	size_t linesLen = IStringArray_Length(lines);

	for (int i = 0; i < linesLen; i += 1)
	{
		const char* line = IStringArray_Get(lines, i);
		IStringArray* spaceSplit = Utils_SplitString(line, Utils_strlen(line), ' ');
		size_t spaceSplitLen = IStringArray_Length(spaceSplit);
		if (spaceSplitLen != 6)
		{
			IStringArray_Dispose(spaceSplit);
			continue;
		}

		Rectangle rect;
		rect.X = Utils_ParseInt(IStringArray_Get(spaceSplit, 2));
		rect.Y = Utils_ParseInt(IStringArray_Get(spaceSplit, 3));
		rect.Width = Utils_ParseInt(IStringArray_Get(spaceSplit, 4));
		rect.Height = Utils_ParseInt(IStringArray_Get(spaceSplit, 5));

		TextureOffsetInfo info = { 0 };
		info.mRect = rect;
		info.mPath = path;
		info.mVirtualName = IStrings_GlobalGet(IStringArray_Get(spaceSplit, 0));
		info.mFilenameWithoutExtension = filenameWithoutExtension;

		arrput(textureOffset->arr_offsets, info);
		IStringArray_Dispose(spaceSplit);
	}

	IStringArray_Dispose(lines);

	return textureOffset;
}
void TextureOffset_Dispose(TextureOffset* to)
{

}
