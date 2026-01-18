#include "SysDebugDrawMenuAnchorNames.h"

#include "../render/SpriteBatch.h"

static void Draw(void* givenData, SpriteBatch* spriteBatch)
{
	/*
	OeLevelData levelData = Get_LevelData();
	OeTile[, ] tiles = levelData.mTileData;
	for (int32_t i = 0; i < tiles.GetLength(0); i += 1)
	{
		for (int32_t j = 0; j < tiles.GetLength(1); j++)
		{
			OeTile tile = tiles[i, j];
			List<OeThingInstance> instances = tile.mInstances;
			for (int32_t k = 0; k < instances.Count; k++)
			{
				OeThingInstance instance = instances[k];
				if (instance.mName.Equals("MENU_ANCHOR"))
				{
					OeStringPair pair = instance.GetSetting(OeComMenuWidgetAnchorSys.SETTINGS_STR_NAME);
					int32_t tileSize = OeUtils.GetTileSize();
					spriteBatch.DrawString("game", pair.mValue, OeColors.RED, 200, new Vector2(i * tileSize, j * tileSize));
				}
			}
		}
	}
	*/
}

System* SysDebugDrawMenuAnchorNames_CreateSystem()
{
	System* sys = System_Create();
	sys->_mDraw = Draw;
	return sys;
}
