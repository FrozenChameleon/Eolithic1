#include "ResourceManagerList.h"

#include "../utils/Utils.h"

#include "../leveldata/AnimTile.h"
#include "../leveldata/Prop.h"
#include "../render/Texture.h"
#include "../audio/SoundEffect.h"
#include "../audio/Music.h"
#include "../leveldata/LevelData.h"
#include "../render/TilesetOffset.h"
#include "../render/TextureOffset.h"
#include "../font/BmFont.h"
#include "../leveldata/Particle.h"
#include "../movie/MovieTiming.h"
#include "../movie/Movie.h"
#include "../font/TtFont.h"
#include "../leveldata/ThingSettings.h"

#define MANAGERS_LEN 50

#define MANAGERS_INDEX_ANIM_TILE 0
#define MANAGERS_INDEX_PROP 1
#define MANAGERS_INDEX_TEXTURE 2
#define MANAGERS_INDEX_FONT_TEXTURE 3
#define MANAGERS_INDEX_MOVIE_TEXTURE 4
#define MANAGERS_INDEX_SOUND_EFFECT 5
#define MANAGERS_INDEX_MUSIC 6
#define MANAGERS_INDEX_TILESET_OFFSET 7
#define MANAGERS_INDEX_LEVEL_DATA 8
#define MANAGERS_INDEX_TEXTURE_OFFSET 9
#define MANAGERS_INDEX_FONT 10
#define MANAGERS_INDEX_PARTICLE 11
#define MANAGERS_INDEX_MOVIE_TIMING 12
#define MANAGERS_INDEX_MOVIE 13
#define MANAGERS_INDEX_TTFONT 14
#define MANAGERS_INDEX_THING_SETTINGS 15

static bool _mHasInit;
static ResourceManager _mManagers[MANAGERS_LEN];

void ResourceManagerList_Init(void)
{
	if (_mHasInit)
	{
		return;
	}

	{
		ResourceManager* animTileMan = ResourceManagerList_AnimTile();
		ResourceManager_Init(animTileMan);
		Utils_strlcpy(animTileMan->_mResourceType, "AnimTile", EE_FILENAME_MAX);
		Utils_strlcpy(animTileMan->_mDatFileName, "animtile.dat", EE_FILENAME_MAX);
		animTileMan->_mFromStream = AnimTile_FromStream;
		animTileMan->_mDispose = AnimTile_Dispose;
	}

	{
		ResourceManager* propMan = ResourceManagerList_Prop();
		ResourceManager_Init(propMan);
		Utils_strlcpy(propMan->_mResourceType, "Prop", EE_FILENAME_MAX);
		Utils_strlcpy(propMan->_mDatFileName, "props.dat", EE_FILENAME_MAX);
		propMan->_mFromStream = Prop_FromStream;
		propMan->_mDispose = Prop_Dispose;
	}

	{
		ResourceManager* textureMan = ResourceManagerList_Texture();
		ResourceManager_Init(textureMan);
		Utils_strlcpy(textureMan->_mResourceType, "Texture", EE_FILENAME_MAX);
		Utils_strlcpy(textureMan->_mDatFileName, "gfx.dat", EE_FILENAME_MAX);
		textureMan->_mFromStream = Texture_FromStream;
		textureMan->_mDispose = Texture_Dispose;
	}

	{
		ResourceManager* fontTextureMan = ResourceManagerList_FontTexture();
		ResourceManager_Init(fontTextureMan);
		Utils_strlcpy(fontTextureMan->_mResourceType, "Font Texture", EE_FILENAME_MAX);
		Utils_strlcpy(fontTextureMan->_mDatFileName, "fontsgfx.dat", EE_FILENAME_MAX);
		fontTextureMan->_mFromStream = Texture_FromStream;
		fontTextureMan->_mDispose = Texture_Dispose;
	}

	{
		ResourceManager* movieTextureMan = ResourceManagerList_MovieTexture();
		ResourceManager_Init(movieTextureMan);
		Utils_strlcpy(movieTextureMan->_mResourceType, "Movie Texture", EE_FILENAME_MAX);
		Utils_strlcpy(movieTextureMan->_mDatFileName, "moviegfx.dat", EE_FILENAME_MAX);
		movieTextureMan->_mFromStream = Texture_FromStream;
		movieTextureMan->_mDispose = Texture_Dispose;
	}

	{
		ResourceManager* soundEffectMan = ResourceManagerList_SoundEffect();
		ResourceManager_Init(soundEffectMan);
		Utils_strlcpy(soundEffectMan->_mResourceType, "Sound Effect", EE_FILENAME_MAX);
		Utils_strlcpy(soundEffectMan->_mDatFileName, "sfx.dat", EE_FILENAME_MAX);
		soundEffectMan->_mFromStream = SoundEffect_FromStream;
		soundEffectMan->_mDispose = SoundEffect_Dispose;
	}

	{
		ResourceManager* musicMan = ResourceManagerList_Music();
		ResourceManager_Init(musicMan);
		Utils_strlcpy(musicMan->_mResourceType, "Music", EE_FILENAME_MAX);
		Utils_strlcpy(musicMan->_mDatFileName, "music.dat", EE_FILENAME_MAX);
		musicMan->_mFromStream = Music_FromStream;
		musicMan->_mDispose = Music_Dispose;
	}

	{
		ResourceManager* levelDataMan = ResourceManagerList_LevelData();
		ResourceManager_Init(levelDataMan);
		Utils_strlcpy(levelDataMan->_mResourceType, "Level Data", EE_FILENAME_MAX);
		Utils_strlcpy(levelDataMan->_mDatFileName, "lvl.dat", EE_FILENAME_MAX);
		levelDataMan->_mFromStream = LevelData_FromStream;
		levelDataMan->_mDispose = LevelData_Dispose;
	}

	{
		ResourceManager* tilesetOffsetMan = ResourceManagerList_TilesetOffset();
		ResourceManager_Init(tilesetOffsetMan);
		Utils_strlcpy(tilesetOffsetMan->_mResourceType, "Tileset Offset", EE_FILENAME_MAX);
		Utils_strlcpy(tilesetOffsetMan->_mDatFileName, "offsetstile.dat", EE_FILENAME_MAX);
		tilesetOffsetMan->_mFromStream = TilesetOffset_FromStream;
		tilesetOffsetMan->_mDispose = TilesetOffset_Dispose;
	}

	{
		ResourceManager* textureOffsetMan = ResourceManagerList_TextureOffset();
		ResourceManager_Init(textureOffsetMan);
		Utils_strlcpy(textureOffsetMan->_mResourceType, "Texture Offset", EE_FILENAME_MAX);
		Utils_strlcpy(textureOffsetMan->_mDatFileName, "offsetstex.dat", EE_FILENAME_MAX);
		textureOffsetMan->_mFromStream = TextureOffset_FromStream;
		textureOffsetMan->_mDispose = TextureOffset_Dispose;
	}

	{
		ResourceManager* fontMan = ResourceManagerList_Font();
		ResourceManager_Init(fontMan);
		Utils_strlcpy(fontMan->_mResourceType, "Font", EE_FILENAME_MAX);
		Utils_strlcpy(fontMan->_mDatFileName, "fonts.dat", EE_FILENAME_MAX);
		fontMan->_mFromStream = BmFont_FromStream;
		fontMan->_mDispose = BmFont_Dispose;
	}

	{
		ResourceManager* particleMan = ResourceManagerList_Particle();
		ResourceManager_Init(particleMan);
		Utils_strlcpy(particleMan->_mResourceType, "Particle", EE_FILENAME_MAX);
		Utils_strlcpy(particleMan->_mDatFileName, "particles.dat", EE_FILENAME_MAX);
		particleMan->_mFromStream = Particle_FromStream;
		particleMan->_mDispose = Particle_Dispose;
	}

	{
		ResourceManager* movieTimingMan = ResourceManagerList_MovieTiming();
		ResourceManager_Init(movieTimingMan);
		Utils_strlcpy(movieTimingMan->_mResourceType, "Movie Timings", EE_FILENAME_MAX);
		Utils_strlcpy(movieTimingMan->_mDatFileName, "timings.dat", EE_FILENAME_MAX);
		movieTimingMan->_mFromStream = MovieTiming_FromStream;
		movieTimingMan->_mDispose = MovieTiming_Dispose;
	}

	{
		ResourceManager* movieMan = ResourceManagerList_Movie();
		ResourceManager_Init(movieMan);
		Utils_strlcpy(movieMan->_mResourceType, "Movies", EE_FILENAME_MAX);
		Utils_strlcpy(movieMan->_mDatFileName, "movies.dat", EE_FILENAME_MAX);
		movieMan->_mFromStream = Movie_FromStream;
		movieMan->_mDispose = Movie_Dispose;
	}

	{
		ResourceManager* ttFontMan = ResourceManagerList_TTFont();
		ResourceManager_Init(ttFontMan);
		Utils_strlcpy(ttFontMan->_mResourceType, "TTFont", EE_FILENAME_MAX);
		Utils_strlcpy(ttFontMan->_mDatFileName, "ttfonts.dat", EE_FILENAME_MAX);
		ttFontMan->_mFromStream = TTFont_FromStream;
		ttFontMan->_mDispose = TTFont_Dispose;
	}

	{
		ResourceManager* thingSettingsMan = ResourceManagerList_ThingSettings();
		ResourceManager_Init(thingSettingsMan);
		Utils_strlcpy(thingSettingsMan->_mResourceType, "Thing Settings", EE_FILENAME_MAX);
		Utils_strlcpy(thingSettingsMan->_mDatFileName, "things.dat", EE_FILENAME_MAX);
		thingSettingsMan->_mFromStream = ThingSettings_FromStream;
		thingSettingsMan->_mDispose = ThingSettings_Dispose;
	}

	_mHasInit = true;
}
void ResourceManagerList_LoadAllFromDat()
{
	for (int32_t i = 0; i < MANAGERS_LEN; i += 1)
	{
		if (_mManagers[i]._mHasInit)
		{
			ResourceManager_LoadAllFromDat(&_mManagers[i]);
		}
	}
}
ResourceManager* ResourceManagerList_AnimTile()
{
	return &_mManagers[MANAGERS_INDEX_ANIM_TILE];
}
ResourceManager* ResourceManagerList_Prop()
{
	return &_mManagers[MANAGERS_INDEX_PROP];
}
ResourceManager* ResourceManagerList_Texture()
{
	return &_mManagers[MANAGERS_INDEX_TEXTURE];
}
ResourceManager* ResourceManagerList_FontTexture()
{
	return &_mManagers[MANAGERS_INDEX_FONT_TEXTURE];
}
ResourceManager* ResourceManagerList_MovieTexture()
{
	return &_mManagers[MANAGERS_INDEX_MOVIE_TEXTURE];
}
ResourceManager* ResourceManagerList_SoundEffect()
{
	return &_mManagers[MANAGERS_INDEX_SOUND_EFFECT];
}
ResourceManager* ResourceManagerList_Music()
{
	return &_mManagers[MANAGERS_INDEX_MUSIC];
}
ResourceManager* ResourceManagerList_LevelData()
{
	return &_mManagers[MANAGERS_INDEX_LEVEL_DATA];
}
ResourceManager* ResourceManagerList_TilesetOffset()
{
	return &_mManagers[MANAGERS_INDEX_TILESET_OFFSET];
}
ResourceManager* ResourceManagerList_TextureOffset()
{
	return &_mManagers[MANAGERS_INDEX_TEXTURE_OFFSET];
}
ResourceManager* ResourceManagerList_Font()
{
	return &_mManagers[MANAGERS_INDEX_FONT];
}
ResourceManager* ResourceManagerList_Particle()
{
	return &_mManagers[MANAGERS_INDEX_PARTICLE];
}
ResourceManager* ResourceManagerList_MovieTiming()
{
	return &_mManagers[MANAGERS_INDEX_MOVIE_TIMING];
}
ResourceManager* ResourceManagerList_Movie()
{
	return &_mManagers[MANAGERS_INDEX_MOVIE];
}
ResourceManager* ResourceManagerList_TTFont()
{
	return &_mManagers[MANAGERS_INDEX_TTFONT];
}
ResourceManager* ResourceManagerList_ThingSettings()
{
	return &_mManagers[MANAGERS_INDEX_THING_SETTINGS];
}
