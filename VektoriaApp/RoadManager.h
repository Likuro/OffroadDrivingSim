#pragma once
#include "Vektoria\Root.h"
#include  "RoadTile.h"
#include "PrefabRoad.h"
#include "ItemManager.h"

#define  anzahlPrefabRoads 5
#define anzahlRoadTiles 10

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene, ItemManager *tmp_myItemManager);
	void updateRoad();

private:

	int activeSpawn;
	int timesSpawned;
	int lastTile;
	int nextTile;
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxGroundLoadPath[_MAX_PATH];
	char prefabHitboxFrontalLoadPath[_MAX_PATH];

	CPlacement *myPlacement;
	CPlacement placementRoad[10];

	//Für die RoadTiles
	RoadTile* RoadSector[anzahlRoadTiles];

	//Für die PrefabRoads
	PrefabRoad* PrefabRoads[anzahlPrefabRoads];

	// Kollisionsobjektmenge der RoadTiles
	CGeos roadTilesHitboxGround;
	CGeos roadTilesHitboxFrontal;

	//ItemManager
	ItemManager* myItemManager;
};

