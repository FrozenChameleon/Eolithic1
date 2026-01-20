#include "GlobalSysUpdateManagers.h"

#include "../leveldata/AnimTile.h"
#include "../leveldata/Prop.h"
#include "../resources/ResourceManagerList.h"

/*
static void UpdateProps()
{

}
*/

static void Update(void* givenData)
{
	{
		ResourceManager* animTileMan = ResourceManagerList_AnimTile();
		int64_t len = ResourceManager_Length(animTileMan);
		for (int32_t i = 0; i < len; i += 1)
		{
			AnimTile_UpdateResource(ResourceManager_GetResourceDataByIndex(animTileMan, i));
		}
	}

	{
		ResourceManager* propMan = ResourceManagerList_Prop();
		int64_t len = ResourceManager_Length(propMan);
		for (int32_t i = 0; i < len; i += 1)
		{
			Prop_UpdateResource(ResourceManager_GetResourceDataByIndex(propMan, i));
		}
	}
	//WILLNOTDO 06262023 (EDITOR_MODE) 2023
	/*
#ifdef EDITOR_MODE
	List<IResourceManager> managers = OeResourceManagers.GetManagers();
	for (int32_t i = 0; i < managers.Count; i += 1)
	{
		managers[i].RefreshAssets();
	}
#endif
*/

	//TODO C99
	/*
	std::unordered_map<std::string, OeResource<OeProp*>*>& propMap = OeResourceManagers::PropManager.GetMap();
	for (auto propIt = propMap.begin(); propIt != propMap.end(); propIt++)
	{
		propIt->second->GetData()->UpdateResource();
	}

	std::unordered_map<std::string, OeResource<OeAnimTile*>*>& animMap = OeResourceManagers::AnimTileManager.GetMap();
	for (auto animIt = animMap.begin(); animIt != animMap.end(); animIt++)
	{
		animIt->second->GetData()->UpdateResource();
	}*/
}

System* GlobalSysUpdateManagers_CreateSystem()
{
	System* sys = System_Create();
	sys->_mUpdate = Update;
	return sys;
}
