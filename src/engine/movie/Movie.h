#pragma once

typedef struct IStringArray IStringArray;
typedef struct BufferReader BufferReader;

typedef struct Movie
{
	IStringArray* mMovieData;
} Movie;

Movie* Movie_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void Movie_Dispose(Movie* movie);

/*
static OeMovie* FromStream(OeMovie* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream);
static const std::string GetExtension();
static const std::vector<std::string> GetDirectories();*/