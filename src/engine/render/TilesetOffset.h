#pragma once

#include "stdint.h"

//#include "../resources/ResourceData.h"
//#include "../io/OeStream.h"

typedef struct DrawTile DrawTile;
typedef struct BufferReader BufferReader;

typedef struct TilesetOffset
{
	uint8_t mDummy;
} TilesetOffset;

TilesetOffset* TilesetOffset_FromStream(const char* path, const char* filenameWithoutExtension, BufferReader* br);
void TilesetOffset_Dispose(TilesetOffset* to);
void TilesetOffset_LoadOffsetPoint(DrawTile* drawTile, const char* tilesetName);
/*
	static OeTilesetOffset* FromStream(OeTilesetOffset* (*createNew)(), bool loadedFromDat, const std::string& path, std::shared_ptr<OeStream> stream);
	static void LoadOffsetPoint(OeDrawTile* drawTile, const std::string& tilesetName);
	static const std::string& GetTilesetExtension();
	static const std::vector<std::string>& GetDirectories();*/