#include "RoadTile.h"



RoadTile::RoadTile(PrefabRoad* tmp_myPrefabRoad, CPlacement* tmp_roadPlacement)
{
	this->myRoadPlacement = tmp_roadPlacement;
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myRoadPlacement->AddPlacement(&myItemSpawns[0]);
	this->myRoadPlacement->AddPlacement(&myItemSpawns[1]);
}

RoadTile::~RoadTile(void)
{
}

void RoadTile::addToScene(PrefabRoad* tmp_myPrefabRoad)
{
	this->myPrefabRoad = tmp_myPrefabRoad;
	this->myPrefabRoad->addtoScene(myRoadPlacement);
}

void RoadTile::removefromScene()
{
	this->myPrefabRoad->subfromScene(myRoadPlacement);
}
