#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement)
{
	this->myRoadPlacement = tmp_roadPlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myRoadPlacement->AddPlacement(&myItemSpawns[0]);
	this->myRoadPlacement->AddPlacement(&myItemSpawns[1]);
	this->myRoadPlacement->AddPlacement(&myHitboxPlacement);
	this->myHitboxPlacement.SetDrawingOff();
}

RoadTile::~RoadTile(void)
{
}

void RoadTile::addToScene(PrefabRoad* tmp_myPrefabRoad)
{
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myPrefabRoad->addtoScene(myRoadPlacement, &myHitboxPlacement);
}

void RoadTile::removefromScene()
{
	this->myPrefabRoad->subfromScene(myRoadPlacement, &myHitboxPlacement);
}
