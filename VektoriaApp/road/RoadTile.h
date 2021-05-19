#pragma once
#include "Vektoria\Root.h"
#include <string.h>
#include "PrefabRoad.h"

using namespace Vektoria;

class RoadTile
{
public:

	RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement, int tmp_roadTilewidth, int tmp_roadTilelength, CGeoTerrains* tmp_roadTilesGravityPlanes);
	~RoadTile(void);

	void addToScene(PrefabRoad *tmp_myPrefabRoad);
	void removefromScene();
	void addItem(CPlacement *tmp_itemPlacement);
	void removeItem();

private:

	CGeo* RoadModel;
	PrefabRoad* myPrefabRoad;
	CPlacement* myRoadPlacement;
	CPlacement myHitboxGroundPlacement;
	CPlacement myHitboxFrontalPlacement;

	//Terrain für Gravity
	CPlacement myGravityPlacement;
	CGeoTerrain GravityPlane;
	CMaterial GravityMaterial;

	CPlacement myItemSpawn;
	CPlacement *myItem;
	CHVector myItemSpawnVector;
	


};

