#include "GlobalSysUpdateManagers.h"

//#include "../resources/OeResourceManagers.h"

/*
static void UpdateProps()
{

}
*/

static void Update(System* sys)
{
	//WILLNOTDO 06262023 (EDITOR) 2023
	/*
#if EDITOR
	List<IResourceManager> managers = OeResourceManagers.GetManagers();
	for (int i = 0; i < managers.Count; i++)
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
