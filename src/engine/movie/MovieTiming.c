#include "MovieTiming.h"

#include "../io/File.h"
#include "../utils/Utils.h"

/*
static const std::string TIMING_EXTENSION = ".txt";
static const std::vector<std::string> TIMING_DIRECTORIES = { OeFile::Combine("data", "timings") };

OeMovieTiming* OeMovieTiming::FromStream(OeMovieTiming* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream)
{
}

const std::string& OeMovieTiming::GetExtension()
{
	return TIMING_EXTENSION;
}
const std::vector<std::string>& OeMovieTiming::GetDirectories()
{
	return TIMING_DIRECTORIES;
}
*/

MovieTiming* MovieTiming_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	MovieTiming* mt = Utils_calloc(1, sizeof(MovieTiming));
	MString* bigString = File_ReadAllToBigString(br);
	IStringArray* lotsOfStrings = IStringArray_Create();
	Utils_SplitString(MString_GetText(bigString), MString_GetCapacity(bigString), ',', lotsOfStrings);
	int32_t len = (int32_t)IStringArray_Length(lotsOfStrings);
	mt->timings = Utils_calloc(len, sizeof(int32_t));
	mt->len = len;
	for (int i = 0; i < len; i += 1)
	{
		int32_t theTiming = Utils_ParseInt(IStringArray_Get(lotsOfStrings, i));
		mt->timings[i] = theTiming;
	}
	MString_Dispose(&bigString);
	IStringArray_Dispose(lotsOfStrings);
	return mt;
}
void MovieTiming_Dispose(MovieTiming* mt)
{
	Utils_free(mt->timings);
	Utils_free(mt);
}
