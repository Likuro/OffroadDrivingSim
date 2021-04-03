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
	void addItem(CPlacement *tmp_itemPlacement);

private:


	CGeo* RoadModel;
	PrefabRoad* myPrefabRoad;
	CPlacement* myRoadPlacement;
	CPlacement myHitboxGroundPlacement;
	CPlacement myHitboxFrontalPlacement;
	CPlacement myItemSpawn;
	CPlacement *myItem;
	CHVector myItemSpawnVector;
	


};

