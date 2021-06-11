#pragma once
#include "Vektoria\Root.h"
#include <string.h>
#include "PrefabRoad.h"

using namespace Vektoria;

class RoadTile
{
public:

	RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_DrivingScenePlacement, int tmp_roadTilewidth, int tmp_roadTilelength, int tmp_roadTileheight, int tmp_RoadTileBoundingBox, CGeoTerrains* tmp_roadTilesGravityPlanes, CGeoQuad* tmp_groundplane);
	~RoadTile(void);

	void addToScene(PrefabRoad *tmp_myPrefabRoad);
	void removefromScene();
	void move(float tmp_lane, float tmp_slope, float tmp_moveZ);
	float getZPos();
	void addItem(CPlacement *tmp_itemPlacement);
	void removeItem();
	void addTerrain(CGeoTerrain* tmp_terrain);
	void removeTerrain();

private:

	CGeo* RoadModel;
	PrefabRoad* myPrefabRoad;
	CPlacement* myDrivingScenePlacement;
	CPlacement myBasePlacement;
	CPlacement myGroundPlacement;
	CPlacement myRoadPlacement;
	CPlacement myHitboxGroundPlacement;
	CPlacement myHitboxFrontalPlacement;
	CPlacement myTerrainPlacementL;
	CPlacement myTerrainPlacementR;

	//Terrain für Gravity
	CPlacement myGravityPlacement;
	CGeoTerrain GravityPlane;
	CMaterial GravityMaterial;

	CGeoTerrain *myTerrainPointerL;
	CGeoTerrain *myTerrainPointerR;

	CPlacement myItemSpawn;
	CPlacement *myItem;
	CHVector myItemSpawnVector;
	


};

