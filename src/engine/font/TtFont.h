#pragma once

#include "../utils/Macros.h"

typedef struct BufferReader BufferReader;

typedef struct TTFont
{
	uint8_t dummy;
} TTFont;

TTFont* TTFont_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void TTFont_Dispose(TTFont* ttf);

/*
public:
	static const std::string& GetExtension();
	static const std::vector<std::string>& GetDirectories();
	static OeTTFont* FromStream(OeTTFont* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream);*/