#pragma once

#include "stdint.h"

typedef struct BufferReader BufferReader;

typedef struct MovieTiming
{
	int32_t len;
	int32_t* timings;
} MovieTiming;

MovieTiming* MovieTiming_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void MovieTiming_Dispose(MovieTiming* mt);

/*
static OeMovieTiming* FromStream(OeMovieTiming* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream);
static const std::string& GetExtension();
static const std::vector<std::string>& GetDirectories();
*/