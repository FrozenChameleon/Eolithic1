#include "Movie.h"

#include "../io/File.h"
#include "../utils/Utils.h"

/*
static const std::string MOVIE_EXTENSION = ".txt";
static const std::vector<std::string> MOVIE_DIRECTORIES = { OeFile::Combine("data", "movies") };

OeMovie* OeMovie::FromStream(OeMovie* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream)
{

}

const std::string OeMovie::GetExtension()
{
	return MOVIE_EXTENSION;
}
const std::vector<std::string> OeMovie::GetDirectories()
{
	return MOVIE_DIRECTORIES;
}
*/

Movie* Movie_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br)
{
	Movie* movie = Utils_calloc(1, sizeof(Movie));
	movie->mMovieData = File_ReadAllToStrings(br);
	return movie;
}
void Movie_Dispose(Movie* movie)
{
	Utils_free(movie);
}
