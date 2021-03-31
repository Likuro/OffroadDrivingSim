#pragma once
#include "Vektoria\Root.h"
#include  "RoadTile.h"
#include "PrefabRoad.h"

using namespace Vektoria;

class RoadManager
{
public:

	void init(CPlacement *tmp_scene);
	void updateRoad();

private:

	int activeSpawn;
	int timesSpawned;
	char prefabModelLoadPath[_MAX_PATH];
	char prefabHitboxLoadPath[_MAX_PATH];

	CPlacement *myPlacement;
	CPlacement placementRoad[10];
	CGeo* modelRoad[10];
	CGeo* prefabRoad[5];
	CFileWavefront m_modelfile[5];

	//Für die RoadTiles
	RoadTile* RoadSector[10];

	//Für die PrefabRoads
	PrefabRoad* PrefabRoads[5];

	// Kollisionsobjektmenge der RoadTiles
	CGeos roadTilesHitbox;
};

