#pragma once

#include "Resource.h"
#include "ResourceManager.h"

void ResourceManagerList_Init(void);
void ResourceManagerList_LoadAllFromDat();
ResourceManager* ResourceManagerList_AnimTile();
ResourceManager* ResourceManagerList_Prop();
ResourceManager* ResourceManagerList_Texture();
ResourceManager* ResourceManagerList_FontTexture();
ResourceManager* ResourceManagerList_MovieTexture();
ResourceManager* ResourceManagerList_SoundEffect();
ResourceManager* ResourceManagerList_Music();
ResourceManager* ResourceManagerList_LevelData();
ResourceManager* ResourceManagerList_TilesetOffset();
ResourceManager* ResourceManagerList_TextureOffset();
ResourceManager* ResourceManagerList_Font();
ResourceManager* ResourceManagerList_Particle();
ResourceManager* ResourceManagerList_MovieTiming();
ResourceManager* ResourceManagerList_Movie();
ResourceManager* ResourceManagerList_TTFont();
ResourceManager* ResourceManagerList_ThingSettings();