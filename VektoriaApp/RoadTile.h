#pragma once
#include "Vektoria\Root.h"
#include <string.h>
#include "PrefabRoad.h"

using namespace Vektoria;

class RoadTile
{
public:

	RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement);
	~RoadTile(void);

	void addToScene(PrefabRoad *tmp_myPrefabRoad);
	void removefromScene();

private:


	CGeo* RoadModel;
	PrefabRoad* myPrefabRoad;
	CPlacement* myRoadPlacement;
	CPlacement myHitboxPlacement;
	CPlacement myItemSpawns[2];
	


};

